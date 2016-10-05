#include <iostream>
#include <string>

#include "VisiteurSauvegarde.h"
#include "ArbreRenduINF2990.h"



void VisiteurSauvegarde::visiter(NoeudAbstrait* noeud)

{

	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementAbstrait{ documentXML_->NewElement("noeudAbstrait") };

	// TODO : Enregistrer dans elementComposite les attributs du noeud

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementAbstrait);
}

void VisiteurSauvegarde::visiter(NoeudComposite* noeud)
{
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementComposite{ documentXML_->NewElement("noeudComposite") };

	// TODO : Enregistrer dans elementComposite les attributs du noeud

	// Visite les fils de ce noeud composite
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		VisiteurSauvegarde* VS = new VisiteurSauvegarde(elementComposite, documentXML_);
		noeud->chercher(i)->accepter(VS);
		delete VS;
	}

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementComposite);
}

void VisiteurSauvegarde::visiter(NoeudRondelle* noeud)
{

}

void VisiteurSauvegarde::visiter(NoeudMuret* noeud)
{

}

void VisiteurSauvegarde::visiter(NoeudBonus* noeud)
{

}

void VisiteurSauvegarde::visiter(NoeudMaillet* noeud)
{

}

void VisiteurSauvegarde::visiter(NoeudPortail* noeud)
{

}