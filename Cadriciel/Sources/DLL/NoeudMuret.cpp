///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMuret.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMuret.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "Utilitaire.h"

#include <../Visiteur.h>
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMuret::NoeudMuret(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMuret::NoeudMuret(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMuret::~NoeudMuret()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMuret::~NoeudMuret()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMuret::afficherConcret() const
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMuret::afficherConcret(const glm::mat4& vueProjection) const
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
void NoeudMuret::animer(float temps)
{
	/*// Le cube effectue un tour à toutes les 7 secondes sur l'axe des X.
	angleX_ = fmod(angleX_ + temps / 7.0f * 2 * (float)utilitaire::PI, 2 * (float)utilitaire::PI);
	// Le cube effectue un tour à toutes les 3 secondes sur l'axe des Y.
	angleY_ = fmod(angleY_ + temps / 3.0f * 2 * (float)utilitaire::PI, 2 * (float)utilitaire::PI);
	// Le cube effectue une révolution à toutes les 15 secondes.
	angleRotation_ = fmod(angleRotation_ + temps / 15.0f * 2 * (float)utilitaire::PI, 2 * (float)utilitaire::PI);
	*/
}


////////////////////////////////////////////////////////////////////////
///
/// @fn BoiteCollision obtenirBoiteCollision()
///
/// Cette fonction permet d'obtenir la boîte de collision du muret
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
/*BoiteCollision NoeudMuret::obtenirBoiteCollision() {
	utilitaire::BoiteEnglobante boudingBox = utilitaire::calculerBoiteEnglobante(*modele_);

	// Initialisation des différents points
	glm::dvec3 scale = this->getScale();
	glm::dvec3 topLeft { - boudingBox.coinMin.x * scale.x, boudingBox.coinMax.y * scale.y, 0 };
	glm::dvec3 bottomLeft { - boudingBox.coinMin.x * scale.x, - boudingBox.coinMin.y * scale.y, 0 };
	glm::dvec3 topRight { boudingBox.coinMax.x * scale.x, boudingBox.coinMax.y * scale.y, 0 };
	glm::dvec3 bottomRight { boudingBox.coinMax.x * scale.x, - boudingBox.coinMin.y * scale.y, 0};

	// Points tournés
	double angle = this->getAngle();
	topLeft = utilitaire::rotater(topLeft, angle);
	bottomLeft = utilitaire::rotater(bottomLeft, angle);
	topRight = utilitaire::rotater(topRight, angle);
	bottomRight = utilitaire::rotater(bottomRight, angle);

	// Repositionnement absolu
	topLeft += this->obtenirPositionRelative() - glm::vec3(-10, 0, 0); // -10x pour la translation de correction
	bottomLeft += this->obtenirPositionRelative() - glm::vec3(-10, 0, 0);
	topRight += this->obtenirPositionRelative() - glm::vec3(-10, 0, 0);
	bottomRight += this->obtenirPositionRelative() - glm::vec3(-10, 0, 0);

	math::Droite3D left(bottomLeft, topLeft);
	math::Droite3D top(topLeft, topRight);
	math::Droite3D right(topRight, bottomRight);
	math::Droite3D bottom(bottomRight, bottomLeft);
	std::vector<math::Droite3D> segments({ left, top, right, bottom });
	BoiteCollision collidingBox(segments);

	return collidingBox;
}*/

////////////////////////////////////////////////////////////////////////
/// @fn math::Droite3D obtenirDroiteDirectrice()
/// Permet d'obtenir la droite directrice du muret
/// @return La droite directrice du muret
////////////////////////////////////////////////////////////////////////
math::Droite3D NoeudMuret::obtenirDroiteDirectrice() {
	utilitaire::BoiteEnglobante box = utilitaire::calculerBoiteEnglobante(*this->modele_);
	double rayon = max(abs(box.coinMax.x - box.coinMin.x), abs(box.coinMin.y - box.coinMax.y)) / 2;

	glm::dvec3 scale = this->getScale();
	glm::dvec3 left { -(rayon + scale.x) + rayon, 0, 0 }; // + rayon pour corriger boite selection
	glm::dvec3 right{ (rayon + scale.x) - rayon, 0, 0 };  // - rayon ... idem

	double angle = this->getAngle();

	glm::dvec3 pos = this->obtenirPositionRelative();
	left = utilitaire::rotater(left, angle) + pos;
	right = utilitaire::rotater(right, angle) + pos;

	math::Droite3D droite{ left, right};
	return droite;
}


////////////////////////////////////////////////////////////////////////
/// @fn double obtenirRayonModele()
/// Permet d'obtenir le rayon minimal du modèle
/// @return Le rayon du modèle
////////////////////////////////////////////////////////////////////////
double NoeudMuret::obtenirRayonModele() {
	utilitaire::BoiteEnglobante a = utilitaire::calculerBoiteEnglobante(*modele_);
	return min(abs(a.coinMax.x - a.coinMin.x), abs(a.coinMax.y - a.coinMin.y)) / 2;
}

////////////////////////////////////////////////
/// @} VISITEUR
////////////////////////////////////////////////

void NoeudMuret::accepter(Visiteur* v)
{
	v->visiter(this);
}


