///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCollision.h
/// @author Luc Courbariaux
/// @date 2016-10-05
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Visiteur.h"
#include "AideCollision.h"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurCollision
/// @brief Cette classe permet de déterminer si il y a collision entre
///		l'objet circulaire passé en argument du constructeur et le reste des objets de l'arbre de rendu
///
/// @author Luc Courbariaux
/// @date 2016-09-25
//////////////////////////////////////////////////////////////////////////

namespace aidecollision {

	///le type d'obstacle rencontré
	enum typeObstacle { MUR, BONUS, PORTAIL, MAILLET };

	class InfoCollision {
		///type d'objet de l'obstacle
		typeObstacle type;
		///le pointeur a l'objet
		NoeudAbstrait* objet;
		///détails de la collision
		aidecollision::DetailsCollision details;
	};



	class VisiteurCollision : public Visiteur
	{
		///le resultat a rendre
		InfoCollision result_;
		///l'objet qui verifie ses collisions
		NoeudAbstrait* objet_;
		///le rayon de l'objet qui verifie ses collisions
		double rayon_;
		///la position de l'objet qui verifie ses collisions
		glm::vec3 position_;

		///donne la collision la plus pertinente avec une suite segments
		DetailsCollision collisionSegments(glm::vec3 ensemble[], int nombre);
		///collision avec un objet de forme ronde
		DetailsCollision visiterNoeudCercle(NoeudAbstrait* noeud);
		///collision avec un objet de forme rectangulaire
		DetailsCollision visiterNoeudQuadrilatere(NoeudAbstrait* noeud);

	public:

		VisiteurCollision(NoeudAbstrait* objet);
		InfoCollision calculerCollision();


		virtual void visiter(NoeudAbstrait* noeud);
		virtual void visiter(NoeudComposite *noeud);

		virtual void visiter(NoeudRondelle* noeud);
		virtual void visiter(NoeudMuret* noeud);
		virtual void visiter(NoeudBonus* noeud);
		virtual void visiter(NoeudMaillet* noeud);
		virtual void visiter(NoeudPortail* noeud);

	};

}