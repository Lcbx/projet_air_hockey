///////////////////////////////////////////////////////////////////////////////
/// @file NoeudBonus.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudBonus.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "Utilitaire.h"

#include <../Visiteur.h>
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonus::NoeudBonus(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBonus::NoeudBonus(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonus::~NoeudBonus()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBonus::~NoeudBonus()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonus::afficherConcret() const
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonus::afficherConcret(const glm::mat4& vueProjection) const
{
	// Affichage du modèle.
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
void NoeudBonus::animer(float temps) { }

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
math::Droite3D NoeudBonus::obtenirDroiteDirectrice() {
	utilitaire::BoiteEnglobante box = utilitaire::calculerBoiteEnglobante(*this->modele_);
	double rayon = max(abs(box.coinMax.x - box.coinMin.x), abs(box.coinMin.y - box.coinMax.y)) / 2;

	glm::dvec3 scale = this->getScale();
	glm::dvec3 left{ -(rayon + scale.x), 0, 0 };
	glm::dvec3 right{ (rayon + scale.x), 0, 0 };

	double angle = this->getAngle();

	glm::dvec3 pos = this->obtenirPositionRelative();
	left = utilitaire::rotater(left, angle) + pos;
	right = utilitaire::rotater(right, angle) + pos;

	math::Droite3D droite{ left, right };
	return droite;
}


////////////////////////////////////////////////////////////////////////
/// @fn double obtenirRayonModele()
/// Permet d'obtenir le rayon minimal du modèle
/// @return Le rayon du modèle
////////////////////////////////////////////////////////////////////////
inline double NoeudBonus::obtenirRayonModele() const {
	utilitaire::BoiteEnglobante a = utilitaire::calculerBoiteEnglobante(*modele_);
	return min(abs(a.coinMax.x - a.coinMin.x), abs(a.coinMax.y - a.coinMin.y)) / 2;
}

////////////////////////////////////////////////
/// 
/// @fn NoeudBonus::accepter(Visiteur* v)
///
/// permet de visiter le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////
void NoeudBonus::accepter(Visiteur* v)
{
	v->visiter(this);
}

