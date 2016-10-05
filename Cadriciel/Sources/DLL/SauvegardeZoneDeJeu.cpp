
#include "SauvegardeZoneDeJeu.h"

#include "FacadeModele.h"
#include "VisiteurSauvegarde.h"

////////////////////////////////////////////////////////////////////////
/// @fn void SauvegardeZoneDeJeu::creerArbre(tinyxml2::XMLDocument document)
///
/// Créé un arbre DOM a partir de l'arbre de rendu
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SauvegardeZoneDeJeu::creerArbre(tinyxml2::XMLDocument document)
{
	// Noeud arbreDeRendu
	tinyxml2::XMLElement* elementArbreDeRendu{ document.NewElement("arbreDeRendu") };

	// Creation de l'arbre DOM a partir de l'arbre de rendu
	VisiteurSauvegarde* VS = new VisiteurSauvegarde(elementArbreDeRendu, document);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(VS);
	delete VS;
}

////////////////////////////////////////////////////////////////////////
/// @fn void SauvegardeZoneDeJeu::lireArbre(tinyxml2::XMLDocument document)
///
/// Créé l'arbre de rendu à partir d'un arbre DOM
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SauvegardeZoneDeJeu::lireArbre(const tinyxml2::XMLDocument document)
{
	// Initialise l'arbre
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->initialiser();

	// Tenter d'obtenir le noeud 'Configuration'
	const tinyxml2::XMLElement* elementArbreDeRendu{ document.FirstChildElement("arbreDeRendu") };
	if (elementArbreDeRendu != nullptr) {

		SauvegardeZoneDeJeu::lireNoeudXML(elementArbreDeRendu);

	}
}



////////////////////////////////////////////////////////////////////////
/// @fn void SauvegardeZoneDeJeu::lireNoeudXML()
///
/// Lit un noeud XML, et créé dans l'Arbre de rendu les éléments correspondants
///
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void SauvegardeZoneDeJeu::lireNoeudXML(const tinyxml2::XMLElement& element)
{
	// Ajoute le noeud correspondant à l'arbre de rendu
	ajouterNoeudXML(element, element.Name());


	// Passe au noeud suivant
	if (!element.NoChildren)
		lireNoeudXML(element.FirstChild);

	else if (element.NextSibling != NULL)
		lireNoeudXML(element.NextSibling);

	/*
	// Tenter d'obtenir l'élément CScene, puis l'attribut CALCULS_PAR_IMAGE
	const tinyxml2::XMLElement* elementScene{ elementConfiguration->FirstChildElement("CScene") };
	if (elementScene != nullptr) {
		if (elementScene->QueryIntAttribute("CALCULS_PAR_IMAGE", &ConfigScene::CALCULS_PAR_IMAGE) != tinyxml2::XML_SUCCESS) {
			std::cerr << "Erreur : CALCULS_PAR_IMAGE : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
		}
	*/
}


void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudComposite* noeud)
{
		
}


void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudBonus* noeud)
{
	glm::dvec3 position(element.Attribute("POSITION1"), element.Attribute("POSITION2"), element.Attribute("POSITION3"));
	glm::dvec3 scale(element.Attribute("SCALE1"), element.Attribute("SCALE2"), element.Attribute("SCALE3"));
	float angleRotation(element.IntAttribute("ANGLE_ROTATION"));

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990->ajouterBonus(position, scale, angleRotation);
}


void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudPortail* noeud)
{
	glm::dvec3 position(element.Attribute("POSITION1"), element.Attribute("POSITION2"), element.Attribute("POSITION3"));
	glm::dvec3 scale(element.Attribute("SCALE1"), element.Attribute("SCALE2"), element.Attribute("SCALE3"));
	float angleRotation(element.IntAttribute("ANGLE_ROTATION"));
	// TODO : Régler conversion
	const char *charFrere(element.Attribute("FRERE"));
	NoeudAbstrait *frere = NoeudAbstrait*(charFrere);

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990->ajouterPortail(position, scale, angleRotation, frere);
}


void SauvegardeZoneDeJeu::ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudMuret* noeud)
{
	glm::dvec3 position(element.Attribute("POSITION1"), element.Attribute("POSITION2"), element.Attribute("POSITION3"));
	glm::dvec3 scale(element.Attribute("SCALE1"), element.Attribute("SCALE2"), element.Attribute("SCALE3"));
	float angleRotation(element.IntAttribute("ANGLE_ROTATION"));

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990->ajouterMuret(position, scale, angleRotation);
}