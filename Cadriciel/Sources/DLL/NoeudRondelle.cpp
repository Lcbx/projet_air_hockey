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
	///debug
	///connaitre le temps d'animation
	///std::cout << "temps animation " << temps << "\n";
	///obtient la facade
	///auto facade = FacadeModele::obtenirInstance();

	//on a besoin d'annimer que si la vitesse est non nulle
	if (glm::length(vitesse_) != 0) {

		//obtient les coefficients
		auto coeff = FacadeModele::obtenirInstance()->getCoefficient();

		//actualisation de la position par rapport a la vitesse
		assignerPositionRelative(obtenirPositionRelative() + vitesse_* temps);

		//application de la friction
		//vitesse_ -= glm::normalize(vitesse_) * (float)coeff.friction * temps;

		//remet la vitessse a 0 si elle en est proshe (evite des oscillations)
		if (glm::round(vitesse_.x) == 0 && glm::round(vitesse_.y) == 0) vitesse_ = glm::vec3(0, 0, 0);

		///debug
		///std::cout << "vitesse " << vitesse_.x << " " << vitesse_.y << "\n";

		//verificateur de collision
		VisiteurCollision v(this);
		auto resultat = v.calculerCollision();
		// si il y a collision on s'arrete
		if (resultat.details.type != aidecollision::COLLISION_AUCUNE) {
			vitesse_ = glm::vec3(0, 0, 0);
			std::cout << "collision " << resultat.details.type  << "\n";
		}
		
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
