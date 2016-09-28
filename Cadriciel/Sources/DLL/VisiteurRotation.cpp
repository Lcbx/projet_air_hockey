#include <iostream>
#include <string>

#include "VisiteurRotation.h"
#include "ArbreRenduINF2990.h"


VisiteurRotation::VisiteurRotation() {
	etat_ = DETERMINER_CENTRE;
	nbrNoeudsVisites_ = 0;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}

void VisiteurRotation::rotate(float angle) {
	etat_ = APPLIQUER_ROTATION;
	angle_ = angle;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}

void VisiteurRotation::visiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne()) {
		auto posNoeud = noeud->obtenirPositionRelative();
		if (etat_ == DETERMINER_CENTRE) {
			posCentre_ *= nbrNoeudsVisites_++;
			posCentre_ += posNoeud;
			posCentre_ /= (float)nbrNoeudsVisites_;
			cout << "noeud actuel X=" << posNoeud.x << " Y=" << posNoeud.y << " Z=" << posNoeud.z << "\n";
		}
		else {	//etat == APPLIQUER_ROTATION
			auto newpos = glm::vec4(posNoeud - posCentre_, 1.f) * glm::rotate(glm::mat4(1.f), glm::radians(angle_), { 0,0,1 }) + glm::vec4(posCentre_, 1.f);
			noeud->assignerPositionRelative(glm::vec3(newpos[0], newpos[1], newpos[2]));
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