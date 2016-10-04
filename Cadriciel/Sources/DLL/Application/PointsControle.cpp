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


NoeudPointControle* PointsControle::p(int i) {
	return	static_cast<NoeudPointControle*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->chercher(i));
}

glm::vec3 PointsControle::pos(int i) {
	return p(i)->obtenirPositionRelative();
}

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
		if (distance < 1.2 * delta) {
			noeud_ = i;
		}
	}
	if (noeud_ != PASDENOEUD) p(noeud_)->setCouleur(glm::vec4(GRIS));
}

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
	if(noeud_!= PASDENOEUD)	switch (noeud_) {
	case 0: {
		if ( pos(6).y > pointClick.y ) pointClick.y = pos(6).y;
		if ( pos(2).x < pointClick.x ) pointClick.x = pos(2).x;
		// TODO: tester si les objets peuvent être dans la table
		p(0)->assignerPositionRelative(pointClick);
		pointClick.x = -pointClick.x;
		p(4)->assignerPositionRelative(pointClick);
		break;
	}
	case 1: {
		if (pos(6).y < pointClick.y) pointClick.y = pos(6).y;
		if (pos(3).x < pointClick.x) pointClick.x = pos(3).x;
		// TODO: tester si les objets peuvent être dans la table
		p(1)->assignerPositionRelative(pointClick);
		pointClick.x = -pointClick.x;
		p(5)->assignerPositionRelative(pointClick);
		break;
	}
	case 2: {
		if (pointClick.y < pos(6).y) pointClick.y = pos(6).y;
		pointClick.x = pos(2).x;
		// TODO: tester si les objets peuvent être dans la table
		p(2)->assignerPositionRelative(pointClick);
		pointClick.y = -pointClick.y;
		p(3)->assignerPositionRelative(pointClick);
		break;
	}
	case 3: {
		if (pointClick.y > pos(7).y ) pointClick.y = pos(7).y;
		pointClick.x = pos(3).x;
		// TODO: tester si les objets peuvent être dans la table
		p(3)->assignerPositionRelative(pointClick);
		pointClick.y = -pointClick.y;
		p(2)->assignerPositionRelative(pointClick);
		break;
	}
	case 4: {
		if (pos(7).y > pointClick.y) pointClick.y = pos(7).y;
		if (pos(2).x > pointClick.x) pointClick.x = pos(2).x;
		// TODO: tester si les objets peuvent être dans la table
		p(4)->assignerPositionRelative(pointClick);
		pointClick.x = -pointClick.x;
		p(0)->assignerPositionRelative(pointClick);
		break;
	}
	case 5: {
		if (pos(7).y < pointClick.y) pointClick.y = pos(7).y;
		if (pos(3).x > pointClick.x) pointClick.x = pos(3).x;
		// TODO: tester si les objets peuvent être dans la table
		p(5)->assignerPositionRelative(pointClick);
		pointClick.x = -pointClick.x;
		p(1)->assignerPositionRelative(pointClick);
		break;
	}
	case 6: {
		//if (pointClick.y > pos(0).y) pointClick.y = pos(0).y;
		//if (pointClick.y < pos(1).y) pointClick.y = pos(1).y;
		pointClick.y = pos(6).y;
		if (pointClick.x > pos(3).x) pointClick.x = pos(3).x;
		// TODO: tester si les objets peuvent être dans la table
		p(6)->assignerPositionRelative(pointClick);
		pointClick.x = -pointClick.x;
		p(7)->assignerPositionRelative(pointClick);
		break;
	}
	case 7: {
		//if (pointClick.y > pos(4).y) pointClick.y = pos(4).y;
		//if (pointClick.y < pos(5).y) pointClick.y = pos(5).y;
		pointClick.y =  0;
		if (pointClick.x < pos(2).x) pointClick.x = pos(2).x;
		// TODO: tester si les objets peuvent être dans la table
		p(7)->assignerPositionRelative(pointClick);
		pointClick.x = -pointClick.x;
		p(6)->assignerPositionRelative(pointClick);
		break;
	}
	default : {
		break;
	}
	}
}

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