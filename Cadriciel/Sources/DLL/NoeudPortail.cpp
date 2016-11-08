///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPortail.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "Utilitaire.h"

#include <../Visiteur.h>
#include "Affichage_debuggage.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::NoeudPortail(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::NoeudPortail(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail::~NoeudPortail()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::~NoeudPortail()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::afficherConcret() const
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::afficherConcret(const glm::mat4& vueProjection) const
{
	// Affichage du modèle.
	//vbo_->dessiner(vueProjection);
	glm::vec3 p = { obtenirPositionRelative().x ,obtenirPositionRelative().y,obtenirPositionRelative().z };
	glm::vec3 position = glm::vec3(vueProjection * glm::vec4(p, 1));
	if (Debug::obtenirInstance().afficherAttraction)
	{
		//tracerCercle(vueProjection, position.x, position.y,  2*obtenirRayon(), 50);
		tracerCercle(vueProjection, position.x, position.y, 3 * obtenirRayonModele(), 50);
	}

	vbo_->dessiner(vueProjection);
	vbo_->dessiner(vueProjection);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::tracerCercle(const glm::mat4& vueProjection,float cx, float cy, float r, int nb_segments) const
///
/// @param[in] 
///			 cx : x du centre du cercle
///			 cy : y du centre du cercle
///			 r : rayon du cercle
///			nb_segments : nombre des segments utilises pour tracer le cercle
/// Cette fonction trace un cercle de centre C (cx,cy) et de rayon r en utilisant un nombre de segments nb_segments
/// qui constituent le perimetre du cercle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPortail::tracerCercle(const glm::mat4& vueProjection, double cx, double cy, double r, int nb_segments) const
{
#define vecPROJvec(arg)	glm::value_ptr(glm::vec3(vueProjection * glm::vec4(arg, 1)))
	glColor3f(1, 0, 0);

	glDisable(GL_TEXTURE_2D);

	glBegin(GL_LINE_LOOP);
	for (float ii = 0; ii < nb_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * ii / (float) nb_segments; //l'angle courant
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glm::vec3 point{ x + cx, y + cy, 0 };
		glVertex3fv(vecPROJvec(point));
	}
	glEnd();
#undef vecProJvec
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
void NoeudPortail::animer(float temps)
{
	//// Le cube effectue un tour à toutes les 7 secondes sur l'axe des X.
	//angleX_ = fmod(angleX_ + temps / 7.0f * 2 * (float)utilitaire::PI, 2 * (float)utilitaire::PI);
	//// Le cube effectue un tour à toutes les 3 secondes sur l'axe des Y.
	//angleY_ = fmod(angleY_ + temps / 3.0f * 2 * (float)utilitaire::PI, 2 * (float)utilitaire::PI);
	//// Le cube effectue une révolution à toutes les 15 secondes.
	//angleRotation_ = fmod(angleRotation_ + temps / 15.0f * 2 * (float)utilitaire::PI, 2 * (float)utilitaire::PI);

}

////////////////////////////////////////////////
/// 
/// @fn NoeudPortail::accepter(Visiteur* v)
///
/// permet de visiter le noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////
void NoeudPortail::accepter(Visiteur* v)
{
	v->visiter(this);
}


