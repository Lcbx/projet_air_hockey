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
	//notre position actuelle qui sera modifiee et reassignee
	auto positionActuelle = obtenirPositionRelative();
	//evite unpetit bug
	if (positionFuture_ == glm::vec3(0, 0, 0)) positionFuture_ = positionActuelle;
	glm::vec3	deplacement = positionFuture_ - positionActuelle;
	float		rayon = obtenirRayon();
	//permet une acceleration (10m/s) evite d'aller trop vite
	float		deplacementMax = (module_vitesse_ + module_acceleration_) * temps;
	float		distance = glm::clamp(glm::length(deplacement), 0.f, deplacementMax);
	glm::vec3	direction = glm::normalize(deplacement);


	InfoCollision resultat;
	VisiteurCollision v;
	//pour eviter de sauter des objets
	for (float i = 0.1f; i < distance / rayon + 0.5f; i += 0.5f)
	{
		glm::vec3 positionIntermediaire = positionActuelle + glm::clamp(i * rayon, 0.f, distance) * direction;
		bool estDanslaBonneZone = estDeuxiemeJoueur ?
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->mailletDansZone1(positionIntermediaire, rayon) :
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->mailletDansZone2(positionIntermediaire, rayon);
		positionIntermediaire = estDanslaBonneZone ? positionIntermediaire : positionActuelle;
		resultat = v.calculerCollision(positionIntermediaire, rayon, false);
		///std::cout << "test " << i << " result " << resultat.type << "\n";
		if (resultat.type != InfoCollision::AUCUNE && resultat.type != InfoCollision::BONUS && resultat.type != InfoCollision::PORTAIL || i >= distance / rayon) {
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
			normale = glm::normalize(positionActuelle - resultat.objet->obtenirPositionRelative());
			((NoeudRondelle*)resultat.objet)->collisionMailletExterne(vitesse_, normale);
			break;
		}
		default: break;
		}
	}

	//on assigne la nouvelle position
	assignerPositionRelative(positionActuelle);
	//determine la vitesse
	vitesse_ = (dernierePosition_ - positionActuelle) / temps;
	module_vitesse_ = glm::length(vitesse_);
	//pour la vitesse future
	dernierePosition_ = positionActuelle;
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
	positionFuture_ = pos;
}