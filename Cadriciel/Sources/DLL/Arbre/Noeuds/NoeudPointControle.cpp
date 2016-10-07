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
	/*
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);

	//position du point de controle
	glm::vec3 coord3 = obtenirPositionRelative();
	
	//multiplication
#define PROJvec(arg)	glm::value_ptr(	glm::vec3(vueProjection * glm::vec4(arg, 1)))


	glm::vec3 p0{ coord3.x - delta_ / 2, coord3.y + delta_ / 2, coord3.z };
	glm::vec3 p1{ coord3.x - delta_ / 2, coord3.y - delta_ / 2, coord3.z };
	glm::vec3 p2{ coord3.x + delta_ / 2, coord3.y - delta_ / 2, coord3.z };
	glm::vec3 p3{ coord3.x + delta_ / 2, coord3.y + delta_ / 2, coord3.z };

	glColor4fv(glm::value_ptr(couleur_));
	glBegin(GL_QUADS);
	{
		glVertex3fv(PROJvec(p0));
		glVertex3fv(PROJvec(p1));
		glVertex3fv(PROJvec(p2));
		glVertex3fv(PROJvec(p3));
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
	*/
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
/// 
/// @fn NoeudPointControle::accepter(Visiteur* v)
///
/// permet de visiter le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////
void NoeudPointControle::accepter(Visiteur* v)
{
	//on ne veut pas faire de traitement sur les points de controle
	//v->visiter(this);
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

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPointControle::setDelta(glm::vec4 & couleur)
///
/// Cette fonction permet de changer la taille du carré du point de controle
///  @param[in] 
///		delta : la valeur de delta
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudPointControle::setDelta(double delta) {
	delta_ = delta;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPointControle::getCouleur(glm::vec4 & couleur)
///
/// Cette fonction permet d'obtenir la taille du carré du point de controle
///  @param[in] 
///		delta : la valeur de delta
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudPointControle::getDelta(double& delta) {
	delta = delta_;
	return true;
}