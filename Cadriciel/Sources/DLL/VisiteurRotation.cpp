#include <iostream>
#include <string>

#include "VisiteurRotation.h"
#include "ArbreRenduINF2990.h"
#include "VisiteurPointMilieu.h"

VisiteurRotation::VisiteurRotation() {
	VisiteurPointMilieu v(posCentre_);	
}

void VisiteurRotation::rotate(float angle) {
	angle_ = angle;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}

void VisiteurRotation::visiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne()) {
		auto posNoeud = noeud->obtenirPositionRelative();
		auto newpos = glm::vec4(posNoeud - posCentre_, 0.f) * glm::rotate(glm::mat4(1.f), glm::radians(angle_), { 0.f,0.f,1.f }) + glm::vec4(posCentre_, 0.f);
		noeud->assignerPositionRelative(glm::vec3(newpos[0], newpos[1], newpos[2]));
		noeud->setAngle(noeud->getAngle() - angle_/60);
	}
}

void VisiteurRotation::visiter(NoeudComposite* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

void VisiteurRotation::visiter(NoeudRondelle* noeud)
{
	VisiteurRotation::visiter((NoeudAbstrait*)noeud);
}

void VisiteurRotation::visiter(NoeudMuret* noeud)
{
	VisiteurRotation::visiter((NoeudAbstrait*)noeud);
}

void VisiteurRotation::visiter(NoeudBonus* noeud)
{
	VisiteurRotation::visiter( (NoeudAbstrait*) noeud );
}


void VisiteurRotation::visiter(NoeudMaillet* noeud)
{
	VisiteurRotation::visiter((NoeudAbstrait*)noeud);
}
void VisiteurRotation::visiter(NoeudPortail* noeud)
{
	VisiteurRotation::visiter((NoeudAbstrait*)noeud);
}