#include <iostream>
#include <string>

#include "VisiteurRotation.h"
#include "FacadeModele.h"
#include "../ArbreRenduINF2990.h"
#include "../../Commun/Utilitaire/Vue/Vue.h"
#include "VisiteurPointMilieu.h"

VisiteurRotation::VisiteurRotation(){
	VisiteurPointMilieu v(posCentre_);
}

void VisiteurRotation::rotate(float angle) {
	angle_ = angle;
	tester_ = true;	//s'il faut tester si la manipulation est viable
	effectuer_ = true;	//s'il faut effectuer la manipulation
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
	tester_ = false;
	if(effectuer_) FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}

void VisiteurRotation::visiter(NoeudAbstrait* noeud)
{ 
	if (noeud->estSelectionne()) {
		auto posNoeud = noeud->obtenirPositionRelative();
		auto newpos = glm::vec4(posNoeud - posCentre_, 1) * glm::rotate(glm::mat4(1), glm::radians(angle_), { 0,0,1 }) + glm::vec4(posCentre_, 1);
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(glm::vec3(newpos[0], newpos[1], newpos[2])))
			effectuer_ = false;
		else if(!tester_ && effectuer_) {
			noeud->assignerPositionRelative(glm::vec3(newpos[0], newpos[1], newpos[2]));
			noeud->setAngle(noeud->getAngle() - angle_ / 60);
		}
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