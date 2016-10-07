
#include "SauvegardeZoneDeJeu.h"

#include "FacadeModele.h"
#include "VisiteurSauvegarde.h"
#include "VisiteurAjout.h"
#include "Arbre/ArbreRenduINF2990.h"
#include "Arbre/Noeuds/NoeudTable.h"
#include <typeinfo>

////////////////////////////////////////////////////////////////////////
/// @fn void SauvegardeZoneDeJeu::creerArbre(tinyxml2::XMLDocument& document)
///
/// Créé un arbre DOM a partir de l'arbre de rendu
///
/// @param[in] document : document dans lequel créer l'arbre
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SauvegardeZoneDeJeu::creerArbre(tinyxml2::XMLDocument& document)
{
	// Noeud arbreDeRendu
	tinyxml2::XMLElement* elementArbreDeRendu{ document.NewElement("arbreDeRendu") };

	// Ajoute le noeud table, contenant les informations de la zone de jeu
	elementArbreDeRendu->LinkEndChild(sauvegarderTable(document));


	// Constantes de la zone de jeux
	CoefficientConfiguration coefs = FacadeModele::obtenirInstance()->getCoefficient();
	elementArbreDeRendu->SetAttribute("REBOND", coefs.rebond);
	elementArbreDeRendu->SetAttribute("ACCELERATION", coefs.acceleration);
	elementArbreDeRendu->SetAttribute("FRICTION", coefs.friction);

	// Creation de l'arbre DOM a partir de l'arbre de rendu
	VisiteurSauvegarde* VS = new VisiteurSauvegarde(elementArbreDeRendu, &document);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(VS);
	delete VS;

	document.LinkEndChild(elementArbreDeRendu);
}


////////////////////////////////////////////////////////////////////////
/// @fn void SauvegardeZoneDeJeu::sauvegarderTable(tinyxml2::XMLDocument& document)
///
/// Retourne un élément XML contenant les propriétés de la table
///
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
tinyxml2::XMLElement* SauvegardeZoneDeJeu::sauvegarderTable(tinyxml2::XMLDocument& document)
{
	// Cree l'element XML correspondant a ce noeud
	tinyxml2::XMLElement* elementTable{ document.NewElement("noeudTable") };

	// Enregistrer dans elementTable les attributs du noeud
	elementTable->SetAttribute("TYPE", (ArbreRenduINF2990::NOM_TABLE).c_str());

	NoeudTable* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable();

	// Enregistre les coordonées des points de contrôle (Oui, très répétitif)
	glm::vec3 P0, P1, P2, P3, P4, P5, P6, P7;
	P0 = table->chercher(0)->obtenirPositionRelative();
	P1 = table->chercher(1)->obtenirPositionRelative();
	P2 = table->chercher(2)->obtenirPositionRelative();
	P3 = table->chercher(3)->obtenirPositionRelative();
	P4 = table->chercher(4)->obtenirPositionRelative();
	P5 = table->chercher(5)->obtenirPositionRelative();
	P6 = table->chercher(6)->obtenirPositionRelative();
	P7 = table->chercher(7)->obtenirPositionRelative();
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

	// Visite les fils de ce noeud composite

	// retourne l'élément pour qu'il soit ajouté
	return(elementTable);

}


////////////////////////////////////////////////////////////////////////
/// @fn void SauvegardeZoneDeJeu::lireArbre(tinyxml2::XMLDocument& document)
///
/// Créé l'arbre de rendu à partir d'un arbre DOM
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SauvegardeZoneDeJeu::lireArbre(const tinyxml2::XMLDocument& document)
{
	// Réinitialise l'arbre
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiser();

	// Cherche l'élément arbreDeRendu
	const tinyxml2::XMLElement* elementArbreDeRendu{ document.FirstChildElement("arbreDeRendu") };

	// Enregistre la configuration
	if (elementArbreDeRendu != nullptr) {
		CoefficientConfiguration coefs = COEFFICIENTS_DEFAULT;
		double variableDeTransport;
		if (elementArbreDeRendu->QueryDoubleAttribute("FRICTION", &variableDeTransport) == tinyxml2::XMLError::XML_SUCCESS)
			coefs.friction = variableDeTransport;
		if (elementArbreDeRendu->QueryDoubleAttribute("REBOND", &variableDeTransport) == tinyxml2::XMLError::XML_SUCCESS)
			coefs.rebond = variableDeTransport;
		if (elementArbreDeRendu->QueryDoubleAttribute("ACCELERATION", &variableDeTransport) == tinyxml2::XMLError::XML_SUCCESS)
			coefs.acceleration = variableDeTransport;

		FacadeModele::obtenirInstance()->setCoefficient(coefs);
	}


	// Récupere les informations de la table
	if (elementArbreDeRendu != nullptr && elementArbreDeRendu->FirstChild() != nullptr) {
		const tinyxml2::XMLElement* elementTable{ elementArbreDeRendu->FirstChildElement("noeudTable") };
		if (elementTable != nullptr)
			SauvegardeZoneDeJeu::restituerTable(*elementTable);
	}

	
		// Parcours le reste des noeuds
		SauvegardeZoneDeJeu::lireNoeudXML(*(elementArbreDeRendu->FirstChild()->ToElement()));
		
		if(elementArbreDeRendu->FirstChild() != nullptr) {
			SauvegardeZoneDeJeu::lireNoeudXML(*(elementArbreDeRendu->FirstChild()->ToElement()));
		}
	
}


////////////////////////////////////////////////////////////////////////
/// @fn void SauvegardeZoneDeJeu::restituerTable(const tinyxml2::XMLElement& element)
///
/// Charge les configurations de la table.
///
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void SauvegardeZoneDeJeu::restituerTable(const tinyxml2::XMLElement& element)
{
	NoeudTable* t = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable();
	t->chercher(0)->assignerPositionRelative({ element.FloatAttribute("P0X"), element.FloatAttribute("P0Y"), element.FloatAttribute("P0Z") });
	t->chercher(1)->assignerPositionRelative({ element.FloatAttribute("P1X"), element.FloatAttribute("P1Y"), element.FloatAttribute("P1Z") });
	t->chercher(2)->assignerPositionRelative({ element.FloatAttribute("P2X"), element.FloatAttribute("P2Y"), element.FloatAttribute("P2Z") });
	t->chercher(3)->assignerPositionRelative({ element.FloatAttribute("P3X"), element.FloatAttribute("P3Y"), element.FloatAttribute("P3Z") });
	t->chercher(4)->assignerPositionRelative({ element.FloatAttribute("P4X"), element.FloatAttribute("P4Y"), element.FloatAttribute("P4Z") });
	t->chercher(5)->assignerPositionRelative({ element.FloatAttribute("P5X"), element.FloatAttribute("P5Y"), element.FloatAttribute("P5Z") });
	t->chercher(6)->assignerPositionRelative({ element.FloatAttribute("P6X"), element.FloatAttribute("P6Y"), element.FloatAttribute("P6Z") });
	t->chercher(7)->assignerPositionRelative({ element.FloatAttribute("P7X"), element.FloatAttribute("P7Y"), element.FloatAttribute("P7Z") });
}


////////////////////////////////////////////////////////////////////////
/// @fn void SauvegardeZoneDeJeu::lireNoeudXML(const tinyxml2::XMLElement& element)
///
/// Lit un noeud XML, et créé dans l'Arbre de rendu les éléments correspondants
///
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void SauvegardeZoneDeJeu::lireNoeudXML(const tinyxml2::XMLElement& element)
{
	std::cout << "Lecture d'un noeud" << std::endl;
	std::cout << element.Name() << std::endl;

	// Ajoute le noeud correspondant à l'arbre de rendu
	//NoeudAbstrait *n = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(element.Attribute("TYPE"));
	std::cout << element.Attribute("TYPE") << std::endl;
	std::cout << typeid(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(element.Attribute("TYPE"))).name() << std::endl;
	
	if (element.Attribute("TYPE") == "table")
		restituerTable(element);
	else
		ajouterNoeudXML(element);


	// Passe au noeud suivant
	if (!element.NoChildren()) {
		lireNoeudXML(*(element.FirstChild()->ToElement()));
	}

	if (element.NextSibling() != nullptr)
		lireNoeudXML(*(element.NextSibling()->ToElement()));
}




////////////////////////////////////////////////////////////////////////
/// @fn void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element)
///
/// Créé un noeud de l'arbre de rendu a partir d'un élément XML
///
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element)
{
	if (element.Attribute("TYPE") == ArbreRenduINF2990::NOM_TABLE)
		return;

	NoeudAbstrait* nouveauNoeud{ FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(element.Attribute("TYPE")) };
	
	glm::dvec3 position(element.FloatAttribute("POSITION1"), element.FloatAttribute("POSITION2"), element.FloatAttribute("POSITION3"));
	Visiteur* v1 = new VisiteurAjout(position);

	glm::dvec3 scale(element.FloatAttribute("SCALE1"), element.FloatAttribute("SCALE2"), element.FloatAttribute("SCALE3"));
	nouveauNoeud->setScale(scale);

	nouveauNoeud->setAngle(element.FloatAttribute("ANGLE_ROTATION"));

	nouveauNoeud->accepter(v1);
	delete v1;
	if (element.Attribute("TYPE") == ArbreRenduINF2990::NOM_PORTAIL){
		NoeudAbstrait* secondNoeud{ FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_PORTAIL) };
		
		glm::dvec3 frere_position(element.FloatAttribute("FRERE_POSITION1"), element.FloatAttribute("FRERE_POSITION2"), element.FloatAttribute("FRERE_POSITION3"));
		Visiteur* v1 = new VisiteurAjout(frere_position);

		glm::dvec3 frere_scale(element.FloatAttribute("FRERE_SCALE1"), element.FloatAttribute("FRERE_SCALE2"), element.FloatAttribute("FRERE_SCALE3"));
		secondNoeud->setScale(frere_scale);

		secondNoeud->setAngle(element.FloatAttribute("FRERE_ANGLE_ROTATION"));

		//etablir les liens entre les 2 portails
		nouveauNoeud->setFrere(secondNoeud);
		secondNoeud->setFrere(nouveauNoeud);

		secondNoeud->accepter(v1);
		delete v1;
		//delete v2;
	}

}
