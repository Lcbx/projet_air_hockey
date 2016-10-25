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

	//on a besoin d'animer que si la vitesse est non nulle
	if (glm::length(vitesse_) != 0) {

		//obtient les coefficients
		auto coeff = FacadeModele::obtenirInstance()->getCoefficient();

		//actualisation de la position par rapport a la vitesse
		glm::vec3 deplacement = vitesse_* temps;

		//recuperer des situations bizarres
		if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(obtenirPositionRelative() + deplacement)) {
			//TODO: verifier s'il s'agit d'un but
			assignerPositionRelative(obtenirPositionRelative() + deplacement);
			dernieresPositions_.push_front(obtenirPositionRelative());
			if (dernieresPositions_.size() > 5) dernieresPositions_.pop_back();
		}
		else {
			glm::vec3 positionIntermediaire = (dernieresPositions_.front() + obtenirPositionRelative())/(float)2.;
			assignerPositionRelative(positionIntermediaire);
			if (dernieresPositions_.size() > 1) dernieresPositions_.pop_front();
			//std::cout << "vitesse " << vitesse_.x << " " << vitesse_.y << "\n";
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
				vitesse_ += direction * (float)coeff.acceleration;
				break;
			}
			case InfoCollision::PORTAIL: {
				typeObjetDebug = "portail";
				auto noeud = (NoeudPortail*)resultat.objet;
				glm::vec3 position = noeud->getFrere()->obtenirPositionRelative();
				assignerPositionRelative(obtenirPositionRelative() + glm::vec3(resultat.details.direction * resultat.details.enfoncement));
				assignerPositionRelative(position + noeud->obtenirPositionRelative() - obtenirPositionRelative());
				vitesse_ = glm::reflect(glm::dvec3(vitesse_), glm::normalize(resultat.details.direction));
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
		double module_vitesse = glm::length(vitesse_);
#define VITESSE_MAX 100.
		vitesse_ *= glm::clamp(module_vitesse - coeff.friction * temps, 0., VITESSE_MAX) / module_vitesse;
	}
	
	
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
