
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
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SauvegardeZoneDeJeu::creerArbre(tinyxml2::XMLDocument& document)
{
	// Noeud arbreDeRendu
	tinyxml2::XMLElement* elementArbreDeRendu{ document.NewElement("arbreDeRendu") };

	// Creation de l'arbre DOM a partir de l'arbre de rendu
	VisiteurSauvegarde* VS = new VisiteurSauvegarde(elementArbreDeRendu, &document);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(VS);
	delete VS;

	document.LinkEndChild(elementArbreDeRendu);
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
	// Initialise l'arbre
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiser();

	//
	const tinyxml2::XMLElement* elementArbreDeRendu{ document.FirstChildElement("arbreDeRendu") };
	if (elementArbreDeRendu != nullptr && elementArbreDeRendu->FirstChild() != nullptr) {
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
	t->setPointControle(0, { element.FloatAttribute("P0X"), element.FloatAttribute("P0Y"), element.FloatAttribute("P0Z") });
	t->setPointControle(1, { element.FloatAttribute("P1X"), element.FloatAttribute("P1Y"), element.FloatAttribute("P1Z") });
	t->setPointControle(2, { element.FloatAttribute("P2X"), element.FloatAttribute("P2Y"), element.FloatAttribute("P2Z") });
	t->setPointControle(3, { element.FloatAttribute("P3X"), element.FloatAttribute("P3Y"), element.FloatAttribute("P3Z") });
	t->setPointControle(4, { element.FloatAttribute("P4X"), element.FloatAttribute("P4Y"), element.FloatAttribute("P4Z") });
	t->setPointControle(5, { element.FloatAttribute("P5X"), element.FloatAttribute("P5Y"), element.FloatAttribute("P5Z") });
	t->setPointControle(6, { element.FloatAttribute("P6X"), element.FloatAttribute("P6Y"), element.FloatAttribute("P6Z") });
	t->setPointControle(7, { element.FloatAttribute("P7X"), element.FloatAttribute("P7Y"), element.FloatAttribute("P7Z") });
	t->setPointControle(8, { element.FloatAttribute("P8X"), element.FloatAttribute("P8Y"), element.FloatAttribute("P8Z") });
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

/*
void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudComposite *noeud)
{
	std::cout << "Coucou toi" << std::endl;
}


void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudBonus *noeud)
{
	glm::dvec3 position(element.FloatAttribute("POSITION1"), element.FloatAttribute("POSITION2"), element.FloatAttribute("POSITION3"));
	glm::dvec3 scale(element.FloatAttribute("SCALE1"), element.FloatAttribute("SCALE2"), element.FloatAttribute("SCALE3"));
	float angleRotation(element.FloatAttribute("ANGLE_ROTATION"));

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouterBonus(position, scale, angleRotation);
}


void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudPortail *noeud)
{
	std::cout << "Portail ici !" << std::endl;
	glm::dvec3 positionPremier(element.FloatAttribute("POSITION1"), element.FloatAttribute("POSITION2"), element.FloatAttribute("POSITION3"));
	glm::dvec3 scalePremier(element.FloatAttribute("SCALE1"), element.FloatAttribute("SCALE2"), element.FloatAttribute("SCALE3"));
	float angleRotationPremier(element.FloatAttribute("ANGLE_ROTATION"));

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouterPortail(positionPremier, scalePremier, angleRotationPremier);

	glm::dvec3 positionDeuxieme(element.FloatAttribute("POSITION1"), element.FloatAttribute("POSITION2"), element.FloatAttribute("POSITION3"));
	glm::dvec3 scaleDeuxieme(element.FloatAttribute("SCALE1"), element.FloatAttribute("SCALE2"), element.FloatAttribute("SCALE3"));
	float angleRotationDeuxieme(element.FloatAttribute("ANGLE_ROTATION"));

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouterPortailDeux(positionDeuxieme, scaleDeuxieme, angleRotationDeuxieme);

	
}


void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudMuret *noeud)
{
	glm::dvec3 position(element.FloatAttribute("POSITION1"), element.FloatAttribute("POSITION2"), element.FloatAttribute("POSITION3"));
	glm::dvec3 scale(element.FloatAttribute("SCALE1"), element.FloatAttribute("SCALE2"), element.FloatAttribute("SCALE3"));
	float angleRotation(element.FloatAttribute("ANGLE_ROTATION"));

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouterMuret(position, scale, angleRotation);
}
*/