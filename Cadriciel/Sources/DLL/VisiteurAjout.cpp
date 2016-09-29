#include <iostream>
#include <string>
#include"FacadeModele.h"
#include "VisiteurAjout.h"
#include "ArbreRenduINF2990.h"



VisiteurAjout::VisiteurAjout(glm::dvec3 pos)
{
	position = pos;

}

void VisiteurAjout::visiter(NoeudAbstrait* noeud)

{

}

void VisiteurAjout::visiter(NoeudComposite* noeud)
{



}
void VisiteurAjout::visiter(NoeudRondelle* noeud) 
{


}

void VisiteurAjout::visiter(NoeudMuret* noeud) 
{
	cout << "Heloo!!c'est le visiteur ajout du muret" << endl;
	position.x -= 10;
	noeud->assignerPositionRelative(position);
	//verif dans la table 

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud);
}

void VisiteurAjout::visiter(NoeudBonus* noeud)
{
	cout << "Heloo!!c'est le visiteur ajout du bonus" << endl;
	position.x -= 10;
	noeud->assignerPositionRelative(position);
	//verif dans la table 
	
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud);
}
void VisiteurAjout::visiter(NoeudMaillet* noeud)
{

}
void VisiteurAjout::visiter(NoeudPortail* noeud)
{
	cout << "Heloo!!c'est le visiteur ajout du portail" << endl;
	position.x -= 10;
	noeud->assignerPositionRelative(position);
	//verif dans la table 

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud);

}
