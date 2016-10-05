#include <iostream>
#include <string>

#include "VisiteurSauvegarde.h"
#include "ArbreRenduINF2990.h"



void VisiteurSauvegarde::visiter(NoeudAbstrait* noeud)

{
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementAbstrait{ documentXML_->NewElement("noeudAbstrait") };

	// TODO : Enregistrer dans elementAbstrait les attributs du noeud

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementAbstrait);
}

void VisiteurSauvegarde::visiter(NoeudComposite* noeud)
{
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementComposite{ documentXML_->NewElement("noeudComposite") };

	// TODO : Enregistrer dans elementComposite les attributs du noeud ?

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
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementMuret{ documentXML_->NewElement("noeudMuret") };

	// TODO : Enregistrer dans elementMuret les attributs du noeud
	elementMuret->SetAttribute("POSITION1", noeud->obtenirPositionRelative()[0]);
	elementMuret->SetAttribute("POSITION2", noeud->obtenirPositionRelative()[1]);
	elementMuret->SetAttribute("POSITION3", noeud->obtenirPositionRelative()[2]);
	elementMuret->SetAttribute("SCALE1", noeud->getScale()[0]);
	elementMuret->SetAttribute("SCALE2", noeud->getScale()[1]);
	elementMuret->SetAttribute("SCALE3", noeud->getScale()[2]);
	elementMuret->SetAttribute("ANGLE_ROTATION", noeud->getAngle());

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementMuret);
}

void VisiteurSauvegarde::visiter(NoeudBonus* noeud)
{
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementBonus{ documentXML_->NewElement("noeudBonus") };

	// TODO : Enregistrer dans elementBonus les attributs du noeud
	elementBonus->SetAttribute("POSITION1", noeud->obtenirPositionRelative()[0]);
	elementBonus->SetAttribute("POSITION2", noeud->obtenirPositionRelative()[1]);
	elementBonus->SetAttribute("POSITION3", noeud->obtenirPositionRelative()[2]);
	elementBonus->SetAttribute("SCALE1", noeud->getScale()[0]);
	elementBonus->SetAttribute("SCALE2", noeud->getScale()[1]);
	elementBonus->SetAttribute("SCALE3", noeud->getScale()[2]);
	elementBonus->SetAttribute("ANGLE_ROTATION", noeud->getAngle());

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementBonus);
}

void VisiteurSauvegarde::visiter(NoeudMaillet* noeud)
{

}

void VisiteurSauvegarde::visiter(NoeudPortail* noeud)
{
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementPortail{ documentXML_->NewElement("noeudPortail") };

	// TODO : Enregistrer dans elementPortail les attributs du noeud
	elementPortail->SetAttribute("POSITION1", noeud->obtenirPositionRelative()[0]);
	elementPortail->SetAttribute("POSITION2", noeud->obtenirPositionRelative()[1]);
	elementPortail->SetAttribute("POSITION3", noeud->obtenirPositionRelative()[2]);
	elementPortail->SetAttribute("SCALE1", noeud->getScale()[0]);
	elementPortail->SetAttribute("SCALE2", noeud->getScale()[1]);
	elementPortail->SetAttribute("SCALE3", noeud->getScale()[2]);
	elementPortail->SetAttribute("ANGLE_ROTATION", noeud->getAngle());
	elementPortail->SetAttribute("FRERE", noeud->getFrere());

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementPortail);
}