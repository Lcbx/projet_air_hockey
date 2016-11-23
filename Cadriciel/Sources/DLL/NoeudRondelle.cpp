///////////////////////////////////////////////////////////////////////////////
/// @file NoeudRondelle.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "NoeudRondelle.h"
#include "GL/glew.h"
#include <cmath>
#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include "Utilitaire.h"
#include <../Visiteur.h>
#include "VisiteurCollision.h"
#include "Affichage_debuggage.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTable.h"
#include "../Application/JoueurVirtuel.h"
#include "Sons.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::NoeudRondelle(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres (comme les portails pour l'attraction)
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRondelle::NoeudRondelle(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	/*
	//ajoute tous les portails
	auto arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	for (int i = 0; i < arbre->obtenirNombreEnfants(); i++) {
		auto noeud = arbre->chercher(i);
		if (noeud->obtenirType() == "portail") portails_[ arbre->chercher(i) ] = true;
	}
	*/
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::~NoeudRondelle()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRondelle::~NoeudRondelle()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::afficherConcret() const
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::afficherConcret(const glm::mat4& vueProjection) const
{
	// Affichage du modèle.
	vbo_->dessiner(vueProjection);
	// on retrace pour que le rayon d'attraction soit correctement affiche'
	vbo_->dessiner(vueProjection);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::animer(float temps)
{
	
	//pour la lisibilite
	auto facade = FacadeModele::obtenirInstance();
	auto arbre = facade->obtenirArbreRenduINF2990();
	auto table = arbre->getTable();

	// Ali
	// la rondelle ne bouge pas si on est en mode pause
	if (!facade->estEnPauseRondelle()) {

		// le joueur virtuel suit la rondelle quand il est active'
		if (facade->getjoueurVirtuel())
		{
			double vitesse = facade->getVitesseVirtuel();
			double prob = facade->getProbabiliteVirtuel();
			facade->ActiverJoueurVirtuel(vitesse, prob);
		}

		//obtient les coefficients
		auto coeff = facade->getCoefficient();

		//actualisation de la position par rapport a la vitesse
		glm::vec3	positionActuelle = obtenirPositionRelative();
		glm::vec3	direction		 = glm::normalize(vitesse_);
		float		distance		 = glm::length(vitesse_) * temps;
		float		rayon			 = obtenirRayon();

		//verificateur de collision
		InfoCollision resultat;
		VisiteurCollision v;
		//pour eviter de sauter des objets
		for (float i = 0.1f; i < distance / rayon + 0.5f; i += 0.5f)
		{
			glm::vec3 positionIntermediaire = positionActuelle + glm::clamp(i * rayon, 0.f, distance) * direction;
			resultat = v.calculerCollision(positionIntermediaire, obtenirRayon(), true);
			///std::cout << "test " << i << " result " << resultat.type << "\n";

			//pour l'aplication des bonus
			if (!affecteParBonus_ && resultat.type == InfoCollision::BONUS) affecteParBonus_ = true;
			else if (resultat.type == InfoCollision::BONUS) resultat.type = InfoCollision::AUCUNE;

			//arrete lors d'une collision importante
			if (resultat.type != InfoCollision::AUCUNE  || i >= distance / rayon ) {
					affecteParBonus_ = false;
					positionActuelle = positionIntermediaire;
					break;
			}
		}

		//verifie si le deplacement est dans la table
		if (!table->dansTable(positionActuelle)) {
			//recupere le but droit
			glm::vec3 haut, bas, milieu;
			table->getButs(1, haut, milieu, bas);
			//est-ce qu'on est dans la fenetre 
			// a corriger -- parfois ne detecte pas quand la table est deforme -- test si depasse chacun des 2 segments des buts a part

			if (positionActuelle.y > bas.y && positionActuelle.y < haut.y && positionActuelle.x > haut.x) {
				//std::cout << "but droit \n";
				facade->setButDroite(true);
				positionActuelle = { 0,0,0 };
				vitesse_ = {0.1,0,0};
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->player->jouerSon(6);

			}
			else {
				//recupere le but gauche
				table->getButs(2, haut, milieu, bas);
				if (positionActuelle.y > bas.y && positionActuelle.y < haut.y && positionActuelle.x < haut.x) {
					//std::cout << "but gauche \n"; 
					facade->setButGauche(true);
					positionActuelle = { 0,0,0 };
					vitesse_ = { 0.1,0,0 };
					FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->player->jouerSon(6);
				}
				///else
					///gere les situations bizarres
					///pop_position();
			}
		}
		///else push_position();

		//pour l'affichage de Debug
		std::string typeObjetDebug;

		//gerer la collision
		if (resultat.type != InfoCollision::AUCUNE) {
			//la normale rencontree
			glm::vec3 normale = glm::normalize(resultat.details.direction);
			//la position qui annulle la collision
			glm::vec3 positionHorsCollision = positionActuelle + normale * (float)resultat.details.enfoncement;
			
			//en fonction du type de collision
			switch (resultat.type) {
			case InfoCollision::MUR: {
				typeObjetDebug = "mur";
				positionActuelle = positionHorsCollision;
				vitesse_ = glm::reflect(vitesse_, normale) * (float)coeff.rebond;
				
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->player->jouerSon(1);
				//player->jouerSon();
				break;
			}
			case InfoCollision::BONUS: {
				typeObjetDebug = "bonus";
				glm::vec3 direction = glm::normalize(-((NoeudBonus*)resultat.objet)->obtenirDroiteDirectrice().lireVecteur());
				vitesse_ += direction * (float)glm::pow(coeff.acceleration, 1);
				affecteParBonus_ = true;

				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->player->jouerSon(4);

				break;
			}
			case InfoCollision::PORTAIL: {
				typeObjetDebug = "portail";
				auto noeud = resultat.objet;
				auto frere = noeud->getFrere();
				positionActuelle = frere->obtenirPositionRelative()
					- ((float)frere->obtenirRayon() * 0.8f + rayon)
					* glm::normalize(positionHorsCollision - noeud->obtenirPositionRelative());
				//desactive l'attraction du frere
				((NoeudPortail*)frere)->attracte_ = false;
				///std::cout << "portail " << frere->obtenirRayon() << " desactive " << ((NoeudPortail*)frere)->attracte_  << "\n";
				
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->player->jouerSon(2);
				break;
			}
			case InfoCollision::MAILLET: {
				typeObjetDebug = "maillet";
				positionActuelle = positionHorsCollision;

				normale = glm::normalize(positionActuelle - resultat.objet->obtenirPositionRelative());
				auto vitesseMaillet = ((NoeudMaillet*)resultat.objet)->getVitesse();
				vitesse_ = glm::reflect(vitesse_, normale) + normale * glm::dot(vitesseMaillet, -normale);
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->player->jouerSon(5);
				break;
			}
			default: break;
			}
		}

		//on assigne la nouvelle position
		assignerPositionRelative(positionActuelle);


		//attraction des portails
		for (int i = 0; i < arbre->obtenirNombreEnfants(); i++) {
			auto noeud = arbre->chercher(i);
			if (noeud->obtenirType() == "portail") {
				auto		portail = (NoeudPortail*) noeud;
				glm::vec3	vecteur_distance = portail->obtenirPositionRelative() - positionActuelle;
				float		distance = glm::length(vecteur_distance);
				float		rayon_attraction = 3.f * portail->obtenirRayon();
				//si on est dans le rayon d'attraction
				if (distance < rayon_attraction) {
					//et qu'on ne sort pas de ce portail, on a le droit d'attracter
					if (portail->attracte_) vitesse_ += 5.f * rayon_attraction / distance  * glm::normalize(vecteur_distance);
				}
				//sinon on pourra de nouveau etre attracte dans le futur
				else portail->attracte_ = true;
				///std::cout << "portail " << i << " attracte " << portail->attracte_ <<  " distance " << distance  << " rayon attraction " << rayon_attraction << "\n";
			}
		}
		///std::cout << "\n";

		//application de la friction
		float moduleVitesse = glm::length(vitesse_);
		vitesse_ *= glm::clamp(moduleVitesse - coeff.friction * temps, 0.005, 300.) / moduleVitesse;
		moduleVitesse = glm::length(vitesse_);

		//affichages de Debug
		if (Debug::obtenirInstance().afficherCollision && resultat.type != InfoCollision::AUCUNE) Debug::obtenirInstance().afficher("Collision : " + typeObjetDebug);
		if (Debug::obtenirInstance().afficherVitesse && resultat.type != InfoCollision::AUCUNE) Debug::obtenirInstance().afficher("Vitesse : " + std::to_string(moduleVitesse).substr(0, 3));
	
	}// End - if mode pause 
	
		
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::collisionMailletExterne(glm::vec3 vitesseMaillet, glm::vec3 normale)
///
/// Cette fonction effectue l'animation du noeud pour un certaingere une collision provenant du deplacement du maillet
/// et non de celui de la rondelle (donc externe).
///
/// @param[in]	vitesseMaillet : Ia vitesse du maillet lors de la collision
///				normale : la normale de la collision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::collisionMailletExterne(glm::vec3 vitesseMaillet, glm::vec3 normale) {
	auto vitesseIntermediaire = -glm::reflect(vitesse_, normale) + normale * glm::dot(vitesseMaillet, -normale);
	float moduleVitesse = glm::clamp((float)glm::length(vitesseIntermediaire), 0.f, (float) 300.);
	vitesse_ = moduleVitesse * glm::normalize(vitesseIntermediaire);
	if (Debug::obtenirInstance().afficherCollision) Debug::obtenirInstance().afficher("Collision : maillet");
	if (Debug::obtenirInstance().afficherVitesse) Debug::obtenirInstance().afficher("Vitesse : " + std::to_string(moduleVitesse).substr(0, 3));
}


////////////////////////////////////////////////
/// 
/// @fn NoeudRondelle::accepter(Visiteur* v)
///
/// permet de visiter le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////
void NoeudRondelle::accepter(Visiteur* v)
{
	v->visiter(this);
}
