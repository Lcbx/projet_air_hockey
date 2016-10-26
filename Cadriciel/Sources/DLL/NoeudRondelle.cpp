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
		if (noeud->obtenirType() == "portail") portails_[ (NoeudPortail*) noeud ] = true;
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

	//obtient les coefficients
	auto coeff = FacadeModele::obtenirInstance()->getCoefficient();

	//actualisation de la position par rapport a la vitesse
	glm::vec3 deplacement = (vitesse_)* temps;

	//verifie si le deplacement est dans la table
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(obtenirPositionRelative() + deplacement)) {
		assignerPositionRelative(obtenirPositionRelative() + deplacement);
		push_position();
	}
	else {
		//TODO: verifier s'il s'agit d'un but

		//recuperer des situations bizarres
		pop_position();
	}

	//verificateur de collision
	VisiteurCollision v(this);
	InfoCollision resultat = v.calculerCollision();

	//pour l'affichage de Debug
	std::string typeObjetDebug;

	//gerer la collision
	if (resultat.type != InfoCollision::AUCUNE) {
		//la normale rencontree
		glm::vec3 normale = glm::normalize(resultat.details.direction);
		//la position qui annulle la collision
		glm::vec3 positionHorsCollision = obtenirPositionRelative() + normale * (float)resultat.details.enfoncement;
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
										+ positionHorsCollision
										- noeud->obtenirPositionRelative() );
			vitesse_ *= -1;
			portails_[ frere ] = false;
			break;
		}
		case InfoCollision::MAILLET: {
			typeObjetDebug = "maillet";
			assignerPositionRelative(positionHorsCollision);
			float facteurRebond = glm::clamp(max(glm::dot(-vitesse_, normale), glm::dot(vitesse_, normale)) / glm::length(vitesse_), (float) 0.5, (float) 1.);
			vitesse_ = glm::reflect(vitesse_, normale) * facteurRebond;
			break;
		}
		default: break;
		}
	}

	//attraction des portails
	for (auto it = portails_.begin(); it != portails_.end(); it++) {
		double distance = glm::distance(it->first->obtenirPositionRelative(), obtenirPositionRelative());
		double rayon_attraction = 3 * it->first->obtenirRayon();
		if (it->second) {
			if (distance < rayon_attraction) {
				vitesse_ = vitesse_ + (float)glm::pow(rayon_attraction - distance, 0.7) * glm::normalize(it->first->obtenirPositionRelative() - obtenirPositionRelative());
			}
		}
		else if (distance > rayon_attraction) it->second = true;
	}

	//application de la friction
	float module_vitesse = glm::length(vitesse_);
#define VITESSE_MAX 200.
	vitesse_ *= glm::clamp(module_vitesse - coeff.friction * temps, 0.005, VITESSE_MAX) / module_vitesse;
	module_vitesse = glm::length(vitesse_);

	//affichages de Debug
	if (Debug::obtenirInstance().afficherCollision && resultat.type != InfoCollision::AUCUNE) Debug::obtenirInstance().afficher("Collision : " + typeObjetDebug);
	if (Debug::obtenirInstance().afficherVitesse && resultat.type != InfoCollision::AUCUNE) Debug::obtenirInstance().afficher("Vitesse : " + std::to_string(module_vitesse).substr(0,3));
}


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
