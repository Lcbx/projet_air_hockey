///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPointControle.cpp
/// @author inf2990 groupe 10
/// @date 2016 september
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPointControle.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "Utilitaire.h"

#include <../Visiteur.h>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPointControle::NoeudPointControle(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPointControle::NoeudPointControle(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPointControle::~NoeudPointControle()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPointControle::~NoeudPointControle()
{
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPointControle::afficherConcret() const
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPointControle::afficherConcret(const glm::mat4& vueProjection) const
{
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);

	//position du point de controle
	glm::vec3 coord3 = obtenirPositionRelative();
		
	//transformation en vec4 pour la multiplication
	glm::vec4 coord4 = vueProjection * glm::vec4(coord3, 0);

	glm::vec3 p0{ coord4.x - delta_ / 2,coord4.y + delta_ / 2, coord4.z };
	glm::vec3 p1{ coord4.x - delta_ / 2,coord4.y - delta_ / 2, coord4.z };
	glm::vec3 p2{ coord4.x + delta_ / 2,coord4.y - delta_ / 2, coord4.z };
	glm::vec3 p3{ coord4.x + delta_ / 2,coord4.y + delta_ / 2, coord4.z };

	glColor4fv(glm::value_ptr(couleur_));
	glBegin(GL_QUADS);
	{
		glVertex3fv(glm::value_ptr(p0));
		glVertex3fv(glm::value_ptr(p1));
		glVertex3fv(glm::value_ptr(p2));
		glVertex3fv(glm::value_ptr(p3));
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPointControle::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPointControle::animer(float temps)
{

}
////////////////////////////////////////////////
/// @}
/// @}VISITEUR
////////////////////////////////////////////////
void NoeudPointControle::accepter(Visiteur* v)
{
	v->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPointControle::setCouleur(glm::vec4 couleur)
///
/// Cette fonction permet de modifier la couleur du point de controle
///  @param[in] 
///			couleur : la nouvelle couleur du point de controle
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudPointControle::setCouleur(glm::vec4 couleur)
{
	couleur_ = couleur;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPointControle::getCouleur(glm::vec4 & couleur)
///
/// Cette fonction permet d'obtenir la couleur du point de controle 
///  @param[in] 
///		couleur : la valeur de la couleur du  point de controle
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudPointControle::getCouleur(glm::vec4 & couleur)
{
	couleur = couleur_;
	return true;
}