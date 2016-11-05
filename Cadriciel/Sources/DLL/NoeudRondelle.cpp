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

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::NoeudRondelle(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRondelle::NoeudRondelle(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	//ajoute tous les portails
	auto arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	for (int i = 0; i < arbre->obtenirNombreEnfants(); i++) {
		auto noeud = arbre->chercher(i);
		if (noeud->obtenirType() == "portail") portails_[ (NoeudPortail*)arbre->chercher(i) ] = true;
	}
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
/// @fn void NoeudCube::animer(float temps)
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
	auto table = facade->obtenirArbreRenduINF2990()->getTable();

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
			}
			else {
				//recupere le but gauche
				table->getButs(2, haut, milieu, bas);
				if (positionActuelle.y > bas.y && positionActuelle.y < haut.y && positionActuelle.x < haut.x) {
					//std::cout << "but gauche \n"; 
					facade->setButGauche(true);
					positionActuelle = { 0,0,0 };
					vitesse_ = { 0.1,0,0 };
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
				break;
			}
			case InfoCollision::BONUS: {
				typeObjetDebug = "bonus";
				glm::vec3 direction = glm::normalize(-((NoeudBonus*)resultat.objet)->obtenirDroiteDirectrice().lireVecteur());
				vitesse_ += direction * (float)glm::pow(coeff.acceleration, 1);
				affecteParBonus_ = true;
				break;
			}
			case InfoCollision::PORTAIL: {
				typeObjetDebug = "portail";
				auto noeud = (NoeudPortail*)resultat.objet;
				auto frere = (NoeudPortail*)noeud->getFrere();
				positionActuelle = frere->obtenirPositionRelative()
					+ (float)frere->obtenirRayon()
					* glm::normalize(positionHorsCollision - noeud->obtenirPositionRelative());
				vitesse_ *= -1.f;
				portails_[frere] = false;
				///std::cout << "portail " << frere->getScale().x << " desactive\n";
				break;
			}
			case InfoCollision::MAILLET: {
				typeObjetDebug = "maillet";
				positionActuelle = positionHorsCollision;
				auto vitesseMaillet = ((NoeudMaillet*)resultat.objet)->getVitesse();
				vitesse_ = - glm::reflect(vitesse_, normale) + glm::dot(vitesseMaillet, normale) * normale;
				break;
			}
			default: break;
			}
		}

		//on assigne la nouvelle position
		assignerPositionRelative(positionActuelle);


		//attraction des portails
#define CST_ASPIRATION 10.f
		for (auto it = portails_.begin(); it != portails_.end(); it++) {
			auto portail = it->first;
			glm::vec3 vecteur_distance = portail->obtenirPositionRelative() - positionActuelle;
			float distance = glm::length(vecteur_distance);
			float rayon_attraction = 3.f * portail->obtenirRayon();
			if (it->second) {
				if (distance < rayon_attraction) {
					///std::cout << "portail " << portail->getScale().x << " attracte\n";
					vitesse_ += CST_ASPIRATION * rayon_attraction / distance  * glm::normalize(vecteur_distance);
				}
			}
			else if (distance > rayon_attraction) {
				it->second = true;
				///std::cout << "portail " << portail->getScale().x << " active  : rayon " << rayon_attraction << ", distance " << distance << "\n";
			}
		}

		//application de la friction
		float moduleVitesse = glm::length(vitesse_);
#define VITESSE_MAX 300.
		vitesse_ *= glm::clamp(moduleVitesse - coeff.friction * temps, 0.005, VITESSE_MAX) / moduleVitesse;
		moduleVitesse = glm::length(vitesse_);

		//affichages de Debug
		if (Debug::obtenirInstance().afficherCollision && resultat.type != InfoCollision::AUCUNE) Debug::obtenirInstance().afficher("Collision : " + typeObjetDebug);
		if (Debug::obtenirInstance().afficherVitesse && resultat.type != InfoCollision::AUCUNE) Debug::obtenirInstance().afficher("Vitesse : " + std::to_string(moduleVitesse).substr(0, 3));
	
	}// End - if mode pause 
	
		
}

//ajoute une vitesse lors d'une collision par le maillet lors de son deplacement
void NoeudRondelle::collisionMailletExterne(glm::vec3 vitesseMaillet, glm::vec3 normale) {
	auto vitesseIntermediaire = glm::reflect(vitesse_, normale) - glm::dot(vitesseMaillet, normale) * normale;
	float moduleVitesse = glm::clamp((float)glm::length(vitesseIntermediaire), 0.f, (float) VITESSE_MAX);
	vitesse_ = moduleVitesse * glm::normalize(vitesseIntermediaire);
	if (Debug::obtenirInstance().afficherCollision) Debug::obtenirInstance().afficher("Collision : maillet");
	if (Debug::obtenirInstance().afficherVitesse) Debug::obtenirInstance().afficher("Vitesse : " + std::to_string(moduleVitesse).substr(0, 3));
}


/*
///ajoute une nouvelle position
void NoeudRondelle::push_position() {
	dernieresPositions_.push_front(obtenirPositionRelative());
	if (dernieresPositions_.size() > 5) dernieresPositions_.pop_back();
}
///charge une ancienne position
void NoeudRondelle::pop_position() {
	glm::vec3 positionIntermediaire = (dernieresPositions_.front());
	assignerPositionRelative(positionIntermediaire);
	if (dernieresPositions_.size() > 1) dernieresPositions_.pop_front();
}
*/

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
