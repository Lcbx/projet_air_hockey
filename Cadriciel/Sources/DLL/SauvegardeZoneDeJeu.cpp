
#include "SauvegardeZoneDeJeu.h"

#include "FacadeModele.h"
#include "VisiteurSauvegarde.h"
#include "Arbre/ArbreRenduINF2990.h"

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
	NoeudAbstrait *n = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(element.Attribute("TYPE"));
	ajouterNoeudXML(element, n);


	// Passe au noeud suivant
	if (!element.NoChildren()) {
		lireNoeudXML(*(element.FirstChild()->ToElement()));
	}

	if (element.NextSibling() != nullptr)
		lireNoeudXML(*(element.NextSibling()->ToElement()));
}


void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudAbstrait *noeud)
{

}


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