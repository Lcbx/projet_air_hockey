#include <iostream>
#include <string>

#include "VisiteurSauvegarde.h"
#include "ArbreRenduINF2990.h"
#include <iostream>



void VisiteurSauvegarde::visiter(NoeudAbstrait* noeud)

{
	// Template de code à appliquer aux noeuds
	/*
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementAbstrait{ documentXML_->NewElement("noeudAbstrait") };

	// TODO : Enregistrer dans elementAbstrait les attributs du noeud

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementAbstrait);
	*/
}

void VisiteurSauvegarde::visiter(NoeudComposite* noeud)
{
	// Le noeud composite n'est pas enregistré, on parcourt simplement ses fils

	// Visite les fils de ce noeud composite
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		if (noeud->chercher(i)->estEnregistrable()) {
			VisiteurSauvegarde* VS = new VisiteurSauvegarde(elementXMLPere_, documentXML_);
			noeud->chercher(i)->accepter(VS);
			delete VS;
		}
	}
	
}

void VisiteurSauvegarde::visiter(NoeudRondelle* noeud)
{

}

void VisiteurSauvegarde::visiter(NoeudMuret* noeud)
{
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementMuret{ documentXML_->NewElement("NoeudMuret") };

	// TODO : Enregistrer dans elementMuret les attributs du noeud
	elementMuret->SetAttribute("TYPE", "muret");
	elementMuret->SetAttribute("POSITION1", noeud->obtenirPositionRelative().x);
	elementMuret->SetAttribute("POSITION2", noeud->obtenirPositionRelative().y);
	elementMuret->SetAttribute("POSITION3", noeud->obtenirPositionRelative().z);
	elementMuret->SetAttribute("SCALE1", noeud->getScale().x);
	elementMuret->SetAttribute("SCALE2", noeud->getScale().y);
	elementMuret->SetAttribute("SCALE3", noeud->getScale().z);
	elementMuret->SetAttribute("ANGLE_ROTATION", noeud->getAngle());

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementMuret);
}

void VisiteurSauvegarde::visiter(NoeudBonus* noeud)
{
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementBonus{ documentXML_->NewElement("NoeudBonus") };

	// TODO : Enregistrer dans elementBonus les attributs du noeud
	elementBonus->SetAttribute("TYPE", "bonus");
	elementBonus->SetAttribute("POSITION1", noeud->obtenirPositionRelative().x);
	elementBonus->SetAttribute("POSITION2", noeud->obtenirPositionRelative().y);
	elementBonus->SetAttribute("POSITION3", noeud->obtenirPositionRelative().z);
	elementBonus->SetAttribute("SCALE1", noeud->getScale().x);
	elementBonus->SetAttribute("SCALE2", noeud->getScale().y);
	elementBonus->SetAttribute("SCALE3", noeud->getScale().z);
	elementBonus->SetAttribute("ANGLE_ROTATION", noeud->getAngle());

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementBonus);
}

void VisiteurSauvegarde::visiter(NoeudMaillet* noeud)
{

}

void VisiteurSauvegarde::visiter(NoeudPortail* noeud)
{

	// Dans le noeud XML est stocké la paire de portails

	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementPortail{ documentXML_->NewElement("noeudPortail") };

	// Enregistrer dans elementPortail les attributs du portail
	elementPortail->SetAttribute("TYPE", (ArbreRenduINF2990::NOM_PORTAIL).c_str());
	elementPortail->SetAttribute("POSITION1", noeud->obtenirPositionRelative().x);
	elementPortail->SetAttribute("POSITION2", noeud->obtenirPositionRelative().y);
	elementPortail->SetAttribute("POSITION3", noeud->obtenirPositionRelative().z);
	elementPortail->SetAttribute("SCALE1", noeud->getScale().x);
	elementPortail->SetAttribute("SCALE2", noeud->getScale().y);
	elementPortail->SetAttribute("SCALE3", noeud->getScale().z);
	elementPortail->SetAttribute("ANGLE_ROTATION", noeud->getAngle());

	// Enregistrer dans elementPortail les attributs du frere du portail
	elementPortail->SetAttribute("FRERE_POSITION1", noeud->getFrere()->obtenirPositionRelative().x);
	elementPortail->SetAttribute("FRERE_POSITION2", noeud->getFrere()->obtenirPositionRelative().y);
	elementPortail->SetAttribute("FRERE_POSITION3", noeud->getFrere()->obtenirPositionRelative().z);
	elementPortail->SetAttribute("FRERE_SCALE1", noeud->getFrere()->getScale().x);
	elementPortail->SetAttribute("FRERE_SCALE2", noeud->getFrere()->getScale().y);
	elementPortail->SetAttribute("FRERE_SCALE3", noeud->getFrere()->getScale().z);
	elementPortail->SetAttribute("FRERE_ANGLE_ROTATION", noeud->getFrere()->getAngle());

	// Pour ne pas enregistrer chaque paire 2 fois
	noeud->getFrere()->assignerEstEnregistrable(false);

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementPortail);

}