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
#include "VisiteurCollision.h";
#include "ArbreRenduINF2990.h"

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
	vitesse_ = (dernierePosition_ - obtenirPositionRelative())/temps;
	///std::cout << "vitesse maillet " << glm::length(vitesse_) << "\n";
	dernierePosition_ = obtenirPositionRelative();
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


////////////////////////////////////////////////
/// 
/// NoeudMaillet::deplacer(glm::vec3 pos)
///
/// le maillet va tenter de se rendre à la position pos
///
/// @return Aucune.
///
////////////////////////////////////////////////
void NoeudMaillet::deplacer(glm::vec3 pos) {
	//pour eviter de sauter des objets
	glm::vec3	positionActuelle	= obtenirPositionRelative();
	glm::vec3	deplacement			= pos - positionActuelle;
	float		rayon				= obtenirRayon();
	float		distance			= glm::clamp(glm::length(deplacement), 0.f, 0.5f * rayon);	//eviter d'aller trop vite
	glm::vec3	direction			= glm::normalize(deplacement);


	InfoCollision resultat;
	VisiteurCollision v;
	glm::vec3 positionIntermediaire = positionActuelle;
	for (float i = 0.1f; i < distance / rayon + 0.15f; i += 0.1f)
	{
		if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->mailletDansZone2(positionActuelle + glm::clamp(i * rayon, 0.f, distance) * direction, rayon))
			 positionIntermediaire = positionActuelle + glm::clamp(i * rayon, 0.f, distance) * direction;
		resultat = v.calculerCollision(positionIntermediaire, obtenirRayon(), false);
		///std::cout << "test " << i << " result " << resultat.type << "\n";
		if (resultat.type != InfoCollision::AUCUNE && resultat.type != InfoCollision::BONUS || i >= distance / rayon) {
			positionActuelle = positionIntermediaire;
			break;
		}
	}

	//gerer la collision
	if (resultat.type != InfoCollision::AUCUNE) {
		//la normale rencontree
		glm::vec3 normale = glm::normalize(resultat.details.direction);
		//la position qui annulle la collision
		glm::vec3 positionHorsCollision = positionActuelle + normale * (float)resultat.details.enfoncement;
		//en fonction du type de collision
		switch (resultat.type) {
		case InfoCollision::MUR: {
			positionActuelle = positionHorsCollision;
			break;
		}
		case InfoCollision::BONUS: {
			break;
		}
		case InfoCollision::PORTAIL: {
			break;
		}
		case InfoCollision::MAILLET: {
			std::cout << "maillet touche maillet ????\n";
			break;
		}
		case InfoCollision::RONDELLE: {
			positionActuelle = positionHorsCollision;
			auto vitesse_rebond = max(glm::dot(-vitesse_, normale), glm::dot(vitesse_, normale)) * glm::reflect(normale, direction);
			((NoeudRondelle*)resultat.objet)->collisionMailletExterne(vitesse_rebond);
			break;
		}
		default: break;
		}
	}

	//on assigne la nouvelle position
	assignerPositionRelative(positionActuelle);

}