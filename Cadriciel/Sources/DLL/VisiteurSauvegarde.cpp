#include <iostream>
#include <string>

#include "VisiteurSauvegarde.h"
#include "ArbreRenduINF2990.h"



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
	
	// Cree l'element XML correspondant a ce noeud
	//tinyxml2::XMLElement* elementComposite{ documentXML_->NewElement("NoeudComposite") };

	// TODO : Enregistrer dans elementComposite les attributs du noeud ?
	//elementComposite->SetAttribute("TYPE", "composite");

	// Visite les fils de ce noeud composite
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		if (noeud->chercher(i)->estEnregistrable()) {
			VisiteurSauvegarde* VS = new VisiteurSauvegarde(elementXMLPere_, documentXML_);
			noeud->chercher(i)->accepter(VS);
			delete VS;
		}
	}
	// Ajouter le noeud a l'arbre
	//elementXMLPere_->LinkEndChild(elementComposite);
	
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

	std::cout << "Visite du portail" << std::endl;

	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementPortail{ documentXML_->NewElement("noeudPortail") };

	// TODO : Enregistrer dans elementPortail les attributs du noeud
	elementPortail->SetAttribute("TYPE", (ArbreRenduINF2990::NOM_PORTAIL).c_str());
	elementPortail->SetAttribute("POSITION1", noeud->obtenirPositionRelative().x);
	elementPortail->SetAttribute("POSITION2", noeud->obtenirPositionRelative().y);
	elementPortail->SetAttribute("POSITION3", noeud->obtenirPositionRelative().z);
	elementPortail->SetAttribute("SCALE1", noeud->getScale().x);
	elementPortail->SetAttribute("SCALE2", noeud->getScale().y);
	elementPortail->SetAttribute("SCALE3", noeud->getScale().z);
	elementPortail->SetAttribute("ANGLE_ROTATION", noeud->getAngle());

	elementPortail->SetAttribute("FRERE_POSITION1", noeud->getFrere()->obtenirPositionRelative().x);
	elementPortail->SetAttribute("FRERE_POSITION2", noeud->getFrere()->obtenirPositionRelative().y);
	elementPortail->SetAttribute("FRERE_POSITION3", noeud->getFrere()->obtenirPositionRelative().z);
	elementPortail->SetAttribute("FRERE_SCALE1", noeud->getFrere()->getScale().x);
	elementPortail->SetAttribute("FRERE_SCALE2", noeud->getFrere()->getScale().y);
	elementPortail->SetAttribute("FRERE_SCALE3", noeud->getFrere()->getScale().z);
	elementPortail->SetAttribute("FRERE_ANGLE_ROTATION", noeud->getFrere()->getAngle());

	noeud->getFrere()->assignerEstEnregistrable(false);

	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementPortail);

	std::cout << "Visite du portail 2" << std::endl;
}

void VisiteurSauvegarde::visiter(NoeudTable* noeud)
{
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementTable{ documentXML_->NewElement("noeudTable") };

	// TODO : Enregistrer dans elementTable les attributs du noeud
	elementTable->SetAttribute("TYPE", (ArbreRenduINF2990::NOM_TABLE).c_str());

	// Enregistre les coordonées des points de contrôle (Oui, très répétitif)
	glm::vec3 P0, P1, P2, P3, P4, P5, P6, P7, P8;
	noeud->getPointControle(0, P0);
	noeud->getPointControle(1, P1);
	noeud->getPointControle(2, P2);
	noeud->getPointControle(3, P3);
	noeud->getPointControle(4, P4);
	noeud->getPointControle(5, P5);
	noeud->getPointControle(6, P6);
	noeud->getPointControle(7, P7);
	noeud->getPointControle(8, P8);
	elementTable->SetAttribute("P0X", P0.x);
	elementTable->SetAttribute("P0Y", P0.y);
	elementTable->SetAttribute("P0Z", P0.z);
	elementTable->SetAttribute("P1X", P1.x);
	elementTable->SetAttribute("P1Y", P1.y);
	elementTable->SetAttribute("P1Z", P1.z);
	elementTable->SetAttribute("P2X", P2.x);
	elementTable->SetAttribute("P2Y", P2.y);
	elementTable->SetAttribute("P2Z", P2.z);
	elementTable->SetAttribute("P3X", P3.x);
	elementTable->SetAttribute("P3Y", P3.y);
	elementTable->SetAttribute("P3Z", P3.z);
	elementTable->SetAttribute("P4X", P4.x);
	elementTable->SetAttribute("P4Y", P4.y);
	elementTable->SetAttribute("P4Z", P4.z);
	elementTable->SetAttribute("P5X", P5.x);
	elementTable->SetAttribute("P5Y", P5.y);
	elementTable->SetAttribute("P5Z", P5.z);
	elementTable->SetAttribute("P6X", P6.x);
	elementTable->SetAttribute("P6Y", P6.y);
	elementTable->SetAttribute("P6Z", P6.z);
	elementTable->SetAttribute("P7X", P7.x);
	elementTable->SetAttribute("P7Y", P7.y);
	elementTable->SetAttribute("P7Z", P7.z);
	elementTable->SetAttribute("P8X", P8.x);
	elementTable->SetAttribute("P8Y", P8.y);
	elementTable->SetAttribute("P8Z", P8.z);

	// Visite les fils de ce noeud composite
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		if (noeud->chercher(i)->estEnregistrable()) {
			VisiteurSauvegarde* VS = new VisiteurSauvegarde(elementTable, documentXML_);
			noeud->chercher(i)->accepter(VS);
			delete VS;
		}
	}


	// Ajouter le noeud a l'arbre
	elementXMLPere_->LinkEndChild(elementTable);
}
