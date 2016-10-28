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


	//obtient les coefficients
	auto coeff = facade->getCoefficient();
	glm::vec3 positionActuelle = obtenirPositionRelative();
	float rayon = obtenirRayon();

	//actualisation de la position par rapport a la vitesse
	glm::vec3 direction = glm::normalize(vitesse_);
	float deplacement = glm::length(vitesse_) * temps;

	//verificateur de collision
	InfoCollision resultat;
	VisiteurCollision v(this);
	//pour eviter de sauter des objets
	float nombreSauts = deplacement / rayon;
	if (nombreSauts < 1) {
		assignerPositionRelative(positionActuelle + deplacement * direction);
		resultat = v.calculerCollision();
	}
	else for (float i = 1; i < deplacement/rayon +1; i+=1.f) {
		if (i > deplacement/rayon) assignerPositionRelative(positionActuelle + deplacement * direction);
		else assignerPositionRelative(positionActuelle + i * rayon * direction);
		resultat = v.calculerCollision();
		///std::cout << "test " << i << " result " << resultat.type << "\n";
		if (resultat.type != InfoCollision::AUCUNE) break;
	}

	//verifie si le deplacement est dans la table
	if (!table->dansTable(positionActuelle)) {
		//recupere le but droit
		glm::vec3 haut, bas, milieu;
		table->getButs(1, haut, milieu, bas);
		//est-ce qu'on est dans la fenetre
		if(positionActuelle.y > bas.y && positionActuelle.y < haut.y && positionActuelle.x > haut.x) {
			std::cout << "but droit \n";
			//pour le fun
			assignerPositionRelative(positionActuelle);
		}
		else {
			//recupere le but gauche
			table->getButs(2, haut, milieu, bas);
			if (positionActuelle.y > bas.y && positionActuelle.y < haut.y && positionActuelle.x < haut.x) {
				std::cout << "but gauche \n"; 
				//pour le fun
				assignerPositionRelative(positionActuelle);
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
			assignerPositionRelative(positionHorsCollision);
			vitesse_ = glm::reflect(vitesse_, normale) * (float)coeff.rebond;
			break;
		}
		case InfoCollision::BONUS: {
			typeObjetDebug = "bonus";
			glm::vec3 direction = glm::normalize( -((NoeudBonus*)resultat.objet)->obtenirDroiteDirectrice().lireVecteur() );
			vitesse_ += direction * (float) glm::pow(coeff.acceleration, 1.5);
			break;
		}
		case InfoCollision::PORTAIL: {
			typeObjetDebug = "portail";
			auto noeud = (NoeudPortail*)resultat.objet;
			auto frere = (NoeudPortail*)noeud->getFrere();
			assignerPositionRelative(	frere->obtenirPositionRelative()
										+ (float)frere->obtenirRayon()
										* glm::normalize(positionHorsCollision - noeud->obtenirPositionRelative()) );
			vitesse_ *= -1.f;
			portails_[ frere ] = false;
			///std::cout << "portail " << frere->getScale().x << " desactive\n";
			break;
		}
		case InfoCollision::MAILLET: {
			typeObjetDebug = "maillet";
			assignerPositionRelative(positionHorsCollision);
			///float facteurRebond = glm::clamp(max(glm::dot(-vitesse_, normale), glm::dot(vitesse_, normale)) / glm::length(vitesse_), (float) 0.3, (float) 1.);
			vitesse_ = glm::reflect(vitesse_, normale) - ((NoeudMaillet*)resultat.objet)->getVitesse();
			break;
		}
		default: break;
		}
	}

	//attraction des portails
#define CST_ASPIRATION 10.f
	for (auto it = portails_.begin(); it != portails_.end(); it++) {
		auto portail = it->first;
		glm::vec3 vecteur_distance = portail->obtenirPositionRelative() - obtenirPositionRelative();
		double distance = glm::length(vecteur_distance);
		double rayon_attraction = 3.f * portail->obtenirRayon();
		if (it->second) {
			if (distance < rayon_attraction) {
				std::cout << "portail " << portail->getScale().x << " attracte\n";
				vitesse_ += CST_ASPIRATION * temps * vecteur_distance ;
			}
		}
		else if (distance > rayon_attraction) {
			it->second = true;
			///std::cout << "portail " << portail->getScale().x << " active  : rayon " << rayon_attraction << ", distance " << distance << "\n";
		}
	}

	//application de la friction
	float module_vitesse = glm::length(vitesse_);
#define VITESSE_MAX 999.
	vitesse_ *= glm::clamp(module_vitesse - coeff.friction * temps, 0.005, VITESSE_MAX) / module_vitesse;
	module_vitesse = glm::length(vitesse_);

	//affichages de Debug
	if (Debug::obtenirInstance().afficherCollision && resultat.type != InfoCollision::AUCUNE) Debug::obtenirInstance().afficher("Collision : " + typeObjetDebug);
	if (Debug::obtenirInstance().afficherVitesse && resultat.type != InfoCollision::AUCUNE) Debug::obtenirInstance().afficher("Vitesse : " + std::to_string(module_vitesse).substr(0,3));
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
