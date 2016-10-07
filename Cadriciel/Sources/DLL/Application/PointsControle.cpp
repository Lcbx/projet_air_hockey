///////////////////////////////////////////////////////////////////////////////
/// @file Rotation.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


#include "FacadeModele.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/Couleurs.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "PointsControle.h"
#include "../Vue/Vue.h"
#include "../VisiteurDansLaTable.h"



////////////////////////////////////////////////////////////////////////
///
/// @fn PointsControle::PointsControle()
///
/// initialise l'outil point de controle en deselectionnant tous les noeuds
///
/// @return Aucun (constructeur).
///
/////////////////////////////////////////////////////////////////////////
PointsControle::PointsControle() {
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->deselectionnerTout();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn PointsControle::p(int i)
///
/// recupere le point de controle numeroté "i"
///
/// @return NoeudPointControle*
///
/////////////////////////////////////////////////////////////////////////
NoeudPointControle* PointsControle::p(int i) {
	return	static_cast<NoeudPointControle*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->chercher(i));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn PointsControle::pos(int i)
///
/// recupere la position du point de controle numeroté "i"
///
/// @return glm::vec3
///
/////////////////////////////////////////////////////////////////////////
glm::vec3 PointsControle::pos(int i) {
	return p(i)->obtenirPositionRelative();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn PointsControle::start(int x, int y)
///
/// teste si un point de controle est selectionne par le click
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void PointsControle::start(int x, int y) {
	//conversion en coordonnees comme utilisees
	glm::dvec3 pointClick(x, y, 0);  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, pointClick);
	//on itere a travers les points de controle
	for (int i = 0; i < 8; i++) {
		//le delta // du point de controle
		double delta; p(i)->getDelta(delta);
		//sa position
		glm::dvec3 pos = p(i)->obtenirPositionRelative();
		// si on est à la bonne distance, est selectionne
		double distance = glm::distance(pointClick, pos);
		if (distance < delta) {
			noeud_ = i;
		}
	}
	if (noeud_ != PASDENOEUD) p(noeud_)->setCouleur(glm::vec4(VERT));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn PointsControle::current(int x, int y)
///
/// applique s'il y a lieu un déplacement sur le point selectionne
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void PointsControle::current(int x, int y) {
	/*
	p0----------p2----------p4
	|						 |
	|						 |
	p6			p8			p7
	|						 |
	|						 |
	p1----------p3----------p5
	*/
	//point de la souris
	glm::dvec3 pointClick(x, y, 0);  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, pointClick);
	//permet de revenir en arriere
	glm::vec3 nosPoints[8];
#define SAVE(arg) nosPoints[arg] = pos(arg)
	SAVE(0);
	SAVE(1);
	SAVE(2);
	SAVE(3);
	SAVE(4);
	SAVE(5);
	SAVE(6);
	SAVE(7);
#undef SAVE

	if(noeud_!= PASDENOEUD){
		switch (noeud_) {
		case 0: {
			if (pos(6).y > pointClick.y) pointClick.y = pos(6).y;
			if (pos(2).x < pointClick.x) pointClick.x = pos(2).x;
			p(0)->assignerPositionRelative(pointClick);
			pointClick.x = -pointClick.x;
			p(4)->assignerPositionRelative(pointClick);
			break;
		}
		case 1: {
			if (pos(6).y < pointClick.y) pointClick.y = pos(6).y;
			if (pos(3).x < pointClick.x) pointClick.x = pos(3).x;
			p(1)->assignerPositionRelative(pointClick);
			pointClick.x = -pointClick.x;
			p(5)->assignerPositionRelative(pointClick);
			break;
		}
		case 2: {
			if (pointClick.y < pos(6).y) pointClick.y = pos(6).y;
			pointClick.x = pos(2).x;
			p(2)->assignerPositionRelative(pointClick);
			pointClick.y = -pointClick.y;
			p(3)->assignerPositionRelative(pointClick);
			break;
		}
		case 3: {
			if (pointClick.y > pos(7).y) pointClick.y = pos(7).y;
			pointClick.x = pos(3).x;
			p(3)->assignerPositionRelative(pointClick);
			pointClick.y = -pointClick.y;
			p(2)->assignerPositionRelative(pointClick);
			break;
		}
		case 4: {
			if (pos(7).y > pointClick.y) pointClick.y = pos(7).y;
			if (pos(2).x > pointClick.x) pointClick.x = pos(2).x;
			p(4)->assignerPositionRelative(pointClick);
			pointClick.x = -pointClick.x;
			p(0)->assignerPositionRelative(pointClick);
			break;
		}
		case 5: {
			if (pos(7).y < pointClick.y) pointClick.y = pos(7).y;
			if (pos(3).x > pointClick.x) pointClick.x = pos(3).x;
			p(5)->assignerPositionRelative(pointClick);
			pointClick.x = -pointClick.x;
			p(1)->assignerPositionRelative(pointClick);
			break;
		}
		case 6: {
			pointClick.y = pos(6).y;
			if (pointClick.x > pos(3).x) pointClick.x = pos(3).x;
			p(6)->assignerPositionRelative(pointClick);
			pointClick.x = -pointClick.x;
			p(7)->assignerPositionRelative(pointClick);
			break;
		}
		case 7: {
			pointClick.y = 0;
			if (pointClick.x < pos(2).x) pointClick.x = pos(2).x;
			p(7)->assignerPositionRelative(pointClick);
			pointClick.x = -pointClick.x;
			p(6)->assignerPositionRelative(pointClick);
			break;
		}
		default: {
			break;
		}
		}
		bool legal = true;
		VisiteurDansLaTable v(legal);
		if (!legal) {
#define LOAD(arg) p(arg)->assignerPositionRelative(nosPoints[arg])
			LOAD(0);
			LOAD(1);
			LOAD(2);
			LOAD(3);
			LOAD(4);
			LOAD(5);
			LOAD(6);
			LOAD(7);
#undef LOAD
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn PointsControle::end(int x, int y)
///
/// finit l'opération en déselectionnant le noeud
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void PointsControle::end(int x, int y) {
	//la table
	auto table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable();
	//evite de selectionner quelque chose qui ne l'est pas
	if (noeud_ != PASDENOEUD) {
		static_cast<NoeudPointControle*>(table->chercher(noeud_))->setCouleur(glm::vec4(BLEU));
		noeud_ = PASDENOEUD;
	}
}

void PointsControle::operationShortClick() {
	//DO something
}
void PointsControle::operationDragClick() {
	//DO something
}