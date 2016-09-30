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
	// afficher le point de controle 
	afficherPointControle();

	/// Révolution autour du centre.
	//auto modele = glm::rotate(transformationRelative_, angleRotation_, glm::vec3(0, 0, 0));
	//// Translation.
	//modele = glm::translate(modele, glm::vec3(10, 0, 0));
	//// Rotation autour de l'axe des X.
	//modele = glm::rotate(modele, angleX_, glm::vec3(1, 0, 0));
	//// Rotation autour de l'axe des Y.
	//modele = glm::rotate(modele, angleY_, glm::vec3(0, 1, 0));
	//// Recentrage du cube.
	//modele = glm::translate(modele, glm::vec3(0, 0, -10));
	// Affichage du modèle.
	//vbo_->dessiner(vueProjection * modele);
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
/// @fn void NoeudPointControle::afficherPointControle() const
///
/// Cette fonction affiche le rendu openGL du point de controle
///
/// @param[in] aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPointControle::afficherPointControle() const
{
	//glMatrixMode(GL_MODELVIEW); 
	//glLoadIdentity(); // deja fait dans la table --garder en commentaire pour l'instant
	// deactiver les textures (la table ne prend plus la texture des autres noeuds)
	//glDisable(GL_TEXTURE_2D); // deja fait dans la table -- garder en commentaire pour l'instant
	// desactiver le test de profondeur
	//glDisable(GL_DEPTH_TEST);// deja fait dans la table -- garder en commentaire pour l'instant
	// activer l'anticrenelage
	//glEnable(GL_MULTISAMPLE);// deja fait dans la table -- garder en commentaire pour l'instant

	glm::vec3 p0{ coord_.x - delta_ / 2,coord_.y + delta_ / 2, coord_.z };
	glm::vec3 p1{ coord_.x - delta_ / 2,coord_.y - delta_ / 2, coord_.z };
	glm::vec3 p2{ coord_.x + delta_ / 2,coord_.y - delta_ / 2, coord_.z };
	glm::vec3 p3{ coord_.x + delta_ / 2,coord_.y + delta_ / 2, coord_.z };

	//afficher p0
	//std::cout << "x = " << p0.x << " y = " << p0.y << std::endl;

	glColor4f(couleur_[0], couleur_[1], couleur_[2], couleur_[3]);
	glBegin(GL_QUADS);
	{
		glVertex3f(p0.x, p0.y, p0.z);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
	}
	glEnd();

	// reactiver le test de profondeur
	//glEnable(GL_DEPTH_TEST);// deja fait dans la table -- garder en commentaire pour l'instant
	// desactiver l'ancrenelage
	//glDisable(GL_MULTISAMPLE);// deja fait dans la table -- garder en commentaire pour l'instant
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPointControle::getCoord(glm::vec3 & point)
///
/// Cette fonction permet d'obtenir les coordonnees du point de controle 
///  @param[in] 
///		point : la valeur du point de controle a recuperer
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudPointControle::getCoord(glm::vec3 & point)
{
	point = coord_;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPointControle::setCoord(glm::vec3 point)
///
/// Cette fonction permet de modifier les coordonnees du point de controle 
///  @param[in] 
///		point : la valeur du point de controle a modifier
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudPointControle::setCoord(glm::vec3 point)
{
	coord_ = point;
	return true;
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
/// @fn bool NoeudPointControle::getIndex(int & index)
///
/// Cette fonction permet d'obtenir la valeur de l'index (ID) du noeud
///  @param[in] 
///		index : la valeur de l'index du  point de controle
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudPointControle::getIndex(int & index)
{
	index = index_;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudPointControle::setIndex(int & index)
///
/// Cette fonction permet de modifier la valeur de l'index (ID) du noeud
///  @param[in] 
///		index : la nouvelle valeur de l'index du  point de controle
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudPointControle::setIndex(int index)
{
	index_ = index;
	return true;
}
