///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMaillet.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMaillet.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "Utilitaire.h"
#include "../Visiteur.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMaillet::NoeudMaillet(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMaillet::NoeudMaillet(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMaillet::~NoeudMaillet()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMaillet::~NoeudMaillet()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMaillet::afficherConcret() const
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMaillet::afficherConcret(const glm::mat4& vueProjection) const
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
void NoeudMaillet::animer(float temps)
{
	vitesse_ = (dernierePoition_ - obtenirPositionRelative())/temps;
	///std::cout << "vitesse maillet " << glm::length(vitesse_) << "\n";
	dernierePoition_ = obtenirPositionRelative();
}


////////////////////////////////////////////////
/// 
/// NoeudMaillet::accepter(Visiteur* v)
///
/// permet de visiter le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////
void NoeudMaillet::accepter(Visiteur* v)
{
	v->visiter(this);
}
