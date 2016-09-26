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
	// Révolution autour du centre.
	auto modele = glm::rotate(transformationRelative_, angleRotation_, glm::vec3(0, 0, 1));
	// Translation.
	modele = glm::translate(modele, glm::vec3(10, 0, 0));
	// Rotation autour de l'axe des X.
	modele = glm::rotate(modele, angleX_, glm::vec3(1, 0, 0));
	// Rotation autour de l'axe des Y.
	modele = glm::rotate(modele, angleY_, glm::vec3(0, 1, 0));
	// Recentrage du cube.
	modele = glm::translate(modele, glm::vec3(0, 0, -10));
	
	//change la couleur selon si est selectionne
	if (estSelectionne()) {
		// On active le mode XOR.
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_XOR);
		// Affichage du modèle.
		vbo_->dessiner(vueProjection* modele);
		//on désactive le mode XOR
		glDisable(GL_COLOR_LOGIC_OP);
	}
	else vbo_->dessiner(vueProjection* modele);

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
void NoeudBonus::animer(float temps)
{

}

////////////////////////////////////////////////
/// @}
/// @}VISITEUR
////////////////////////////////////////////////

void NoeudBonus::accepter(Visiteur* v)
{
	v->visiter(this);
}

