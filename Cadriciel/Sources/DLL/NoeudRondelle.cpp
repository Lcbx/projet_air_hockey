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
/// et donner des valeurs par d�faut aux variables membres.
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
/// Ce destructeur d�sallouee la liste d'affichage du cube.
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
///					transformer le mod�le � sa position voulue.
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::afficherConcret(const glm::mat4& vueProjection) const
{
	// Affichage du mod�le.
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

	//on a besoin d'animer que si la vitesse est non nulle
	double module_vitesse = glm::length(vitesse_);
	if (module_vitesse != 0) {

		//obtient les coefficients
		auto coeff = FacadeModele::obtenirInstance()->getCoefficient();

		//attraction des portails
		for (auto it = portails_.begin(); it != portails_.end(); it++) {
			double distance = glm::distance(it->first->obtenirPositionRelative(), obtenirPositionRelative());
			double rayon_attraction = 3 * it->first->obtenirRayon();
			if (it->second) {
				if (distance < rayon_attraction){
					vitesse_  = vitesse_ + (float) glm::pow(rayon_attraction - distance, 1) * glm::normalize(it->first->obtenirPositionRelative() - obtenirPositionRelative());
				}
			}
			else if (distance > rayon_attraction) it->second = true;
		}

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

		//gerer la collision
		if (resultat.type != InfoCollision::AUCUNE) {
			std::string typeObjetDebug;
			//en fonction du type de collision
			switch (resultat.type) {
			case InfoCollision::MUR: {
				typeObjetDebug = "mur";
				assignerPositionRelative(obtenirPositionRelative() + (glm::vec3) resultat.details.direction * (glm::vec3) resultat.details.enfoncement);
				vitesse_ = glm::reflect(glm::dvec3(vitesse_), glm::normalize(resultat.details.direction)) * coeff.rebond;
				break;
			}
			case InfoCollision::BONUS: {
				typeObjetDebug = "bonus";
				glm::vec3 direction = glm::normalize(-((NoeudBonus*)resultat.objet)->obtenirDroiteDirectrice().lireVecteur());
				vitesse_ += direction * (float) glm::pow(coeff.acceleration, 1.5);
				break;
			}
			case InfoCollision::PORTAIL: {
				typeObjetDebug = "portail";
				auto noeud = (NoeudPortail*)resultat.objet;
				auto frere = (NoeudPortail*)noeud->getFrere();
				assignerPositionRelative(obtenirPositionRelative() + glm::vec3(resultat.details.direction * resultat.details.enfoncement));
				assignerPositionRelative(frere->obtenirPositionRelative() + noeud->obtenirPositionRelative() - obtenirPositionRelative());
				vitesse_ = glm::reflect(glm::dvec3(vitesse_), glm::normalize(resultat.details.direction));
				portails_[ frere ] = false;
			}
			case InfoCollision::MAILLET: {
				typeObjetDebug = "maillet";
				assignerPositionRelative(obtenirPositionRelative() + glm::vec3(resultat.details.direction * resultat.details.enfoncement));
				vitesse_ = glm::reflect(glm::dvec3(vitesse_), glm::normalize(resultat.details.direction));
			}
			default: break;
			}
			if (Debug::obtenirInstance().afficherCollision) Debug::obtenirInstance().afficher("Collision : " + typeObjetDebug);
			if (Debug::obtenirInstance().afficherVitesse) Debug::obtenirInstance().afficher("Vitesse : " + std::to_string(glm::length(vitesse_)));
		}


		//application de la friction
#define VITESSE_MAX 200.
		vitesse_ *= glm::clamp(module_vitesse - coeff.friction * temps, 0., VITESSE_MAX) / module_vitesse;
	}
	
	
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
