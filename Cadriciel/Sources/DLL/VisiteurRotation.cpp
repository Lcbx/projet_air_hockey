#include "VisiteurRotation.h"
#include "FacadeModele.h"
#include "../ArbreRenduINF2990.h"
#include "../../Commun/Utilitaire/Vue/Vue.h"
#include "VisiteurPointMilieu.h"
#include "VisiteurDansLaTable.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::VisiteurRotation(glm::vec3 dep)
///
/// initialisation du visiteur de rotation
/// determine le milieu de la selection
/// 
/// @return Aucune (constructeur).
///
/////////////////////////////////////////////////////////////////////////
VisiteurRotation::VisiteurRotation(){
	VisiteurPointMilieu v(posCentre_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudAbstrait* noeud)
///
/// verifie qu'on peut faire la rotation, puis rotate
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurRotation::rotate(float angle) {
	angle_ = angle;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
	angle_ = -angle_;
	VisiteurDansLaTable v(effectuer_);
	if(!effectuer_) FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudAbstrait* noeud)
///
///  rotate le noeud proprement dit
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudAbstrait* noeud)
{ 
	if (noeud->estSelectionne()) {
		auto posNoeud = noeud->obtenirPositionRelative();
		auto newpos = glm::vec4(posNoeud - posCentre_, 1) * glm::rotate(glm::mat4(1), glm::radians(angle_), { 0,0,1 }) + glm::vec4(posCentre_, 1);
		noeud->assignerPositionRelative(glm::vec3(newpos[0], newpos[1], newpos[2]));
		noeud->setAngle(noeud->getAngle() - angle_ / 60);
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudComposite* noeud)
///
/// visite les noeuds inferieur du composite
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
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