///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la premi�re page de la documentation Doxygen.
/**

@mainpage Projet int�grateur de deuxi�me ann�e -- INF2990

*/

#include <windows.h>
#include <cassert>

#include "GL/glew.h"
#include "FreeImage.h"

#include "FacadeModele.h"

#include "VueOrtho.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "ConfigScene.h"
#include "CompteurAffichage.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, �t� 2011
#include "tinyxml2.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "EtatOpenGL.h"
#include <iostream>
#include "Noeuds/NoeudTypes.h"

#include "../SauvegardeZoneDeJeu.h"



/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_{ nullptr };


/// Cha�ne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "configuration.xml" };

/// Cha�ne indiquant le nom du fichier de la zone de jeu par d�faut.
const std::string FacadeModele::FICHIER_ZONEDEFAUT{ "ZoneDefaut.xml" };


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas �t� cr��e, elle la cr�e.  Cette
/// cr�ation n'est toutefois pas n�cessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa cr�ation.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == nullptr)
		instance_ = new FacadeModele;

	return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction lib�re l'instance unique de cette classe.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur lib�re les objets du mod�le.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	delete arbre_;
	delete vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle cr�e
/// un contexte OpenGL sur la fen�tre pass�e en param�tre, initialise
/// FreeImage (utilis�e par le chargeur de mod�les) et assigne des 
/// param�tres du contexte OpenGL.
///
/// @param[in] hWnd : La poign�e ("handle") vers la fen�tre � utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu �tre cr��.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// Initialisation de la configuration
	chargerConfiguration();

	// FreeImage, utilis�e par le chargeur, doit �tre initialis�e
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);

	// Qualit�
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Cr�ation de l'arbre de rendu.  � moins d'�tre compl�tement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de cr�er
	// l'arbre apr�s avoir cr�� le contexte OpenGL.
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();

	// On cr�e une vue par d�faut.
	vue_ = new vue::VueOrtho{
		vue::Camera{ 
			glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 1, 0),   glm::dvec3(0, 1, 0)},
		vue::ProjectionOrtho{ 
				606, 437,
				1, 1000, 5, 0.5, 0.25,
				200, 200}
	};
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration � partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est g�n�r� �
/// partir de valeurs par d�faut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// V�rification de l'existance du ficher

	// Si le fichier n'existe pas, on le cr�e.
	if (!utilitaire::fichierExiste(FICHIER_CONFIGURATION)) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {
		tinyxml2::XMLDocument document;

		// Lire � partir du fichier de configuration
		document.LoadFile(FacadeModele::FICHIER_CONFIGURATION.c_str());

		// On lit les diff�rentes configurations.
		ConfigScene::obtenirInstance()->lireDOM(document);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction g�n�re un fichier XML de configuration � partir de
/// valeurs par d�faut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	tinyxml2::XMLDocument document;
	// �crire la d�claration XML standard...
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	
	// On enregistre les diff�rentes configurations.
	ConfigScene::obtenirInstance()->creerDOM(document);
	
	// �crire dans le fichier
	document.SaveFile(FacadeModele::FICHIER_CONFIGURATION.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerZoneJeu(std::string fichierZoneJeu) const
///
/// Cette fonction charge la zone de jeu � partir d'un fichier XML.
///
/// @param[in] fichierZoneJeu : Nom du fichier � charger.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerZoneJeu(char* fichierZoneJeu) const
{
	// Cr�� le document XML � partir du fichier sp�cifi�
	tinyxml2::XMLDocument document;
	document.LoadFile(fichierZoneJeu);

	// Cr�� l'arbre de rendu � partir du document XML
	SauvegardeZoneDeJeu::lireArbre(document);

}


///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerZoneJeu(std::string fichierZoneJeu) const
///
/// Cette fonction genere un fichier XML contenant la zone de jeu actuelle.
///
/// @param[in] fichierZoneJeu : Nom du fichier �dans lequel sauvegarder.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::enregistrerZoneJeu(char* fichierZoneJeu) const
{
	// G�n�re une erreur si le nom du fichier correspond au fichier de zone par d�faut
	if (fichierZoneJeu == FICHIER_ZONEDEFAUT)
		std::cerr << "Erreur : Tentative de modification de la zone de jeu par d�faut" << std::endl;

	// Cr�� un document XML avec la d�claration XML standard
	tinyxml2::XMLDocument document;
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");

	// Cr�� le document XML � partir de l'arbre de rendu
	SauvegardeZoneDeJeu::creerArbre(document);

	// Enregistrer le document XML dans le fichier
	document.SaveFile(fichierZoneJeu);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction lib�re le contexte OpenGL et d�sinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On lib�re les instances des diff�rentes configurations.
	ConfigScene::libererInstance();


	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu �tre d�truit.");

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la sc�ne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Afficher la sc�ne
	afficherBase();

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// �change les tampons pour que le r�sultat du rendu soit visible.
	::SwapBuffers(hDC_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la sc�ne, c'est-�-dire
/// qu'elle met en place l'�clairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la cam�ra
	glm::mat4 vueProjection(vue_->obtenirProjection().obtenirMatrice() * vue_->obtenirCamera().obtenirMatrice());

	// Afficher la sc�ne.
	arbre_->afficher(vueProjection);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction r�initialise la sc�ne � un �tat "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// R�initialisation de la sc�ne.
	arbre_->initialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les diff�rents calculs d'animations
/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise � jour des objets.
	arbre_->animer(temps);

	// Mise � jour de la vue.
	vue_->animer(temps);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::ajouterBonus(int x, int y)
///
/// Cette fonction permet d'ajouter le bonus acc�lerateur a la scene
///
/// @param[in] x, y : position de clic de la souris .
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::ajouterBonus(int x, int y)
{
	glm::dvec3 position;
	vue_->convertirClotureAVirtuelle(x, y, position);
	arbre_->ajouterBonus(position);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::void FacadeModele::ajouterPortail(int x1, int y1)
///
/// Cette fonction permet d'ajouter le portail a la scene
///
/// @param[in] x1, y1, x2, y2 : position de clic de la souris .
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterPortail(int x1, int y1)
{
	glm::dvec3 position1;
	vue_->convertirClotureAVirtuelle(x1, y1, position1);
	arbre_->ajouterPortail(position1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::void FacadeModele::ajouterPortailDeux(int x2, int y2)
///
/// Cette fonction permet d'ajouter le deuxieme portail a la scene
///
/// @param[in] x2, y2 : position de clic de la souris .
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterPortailDeux(int x2, int y2)
{
	glm::dvec3 position2;
	vue_->convertirClotureAVirtuelle(x2, y2, position2);
	arbre_->ajouterPortailDeux(position2);
}


void FacadeModele::ajouterMuret(int x1, int y1, int x2, int y2)
{
	glm::dvec3 position1;
	vue_->convertirClotureAVirtuelle(x1, y1, position1);
	glm::dvec3 position2;
	vue_->convertirClotureAVirtuelle(x2, y2, position2);
	arbre_->ajouterMuret(position1, position2);
}





////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::getPosDataBidingX()
///
/// cette fonction retourne la position X d'un objet
///
/// @param[in] rien
/// @return position X.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::getPosDataBidingX()
{
	return arbre_->getPosiX();
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::getPosDataBidingY()
///
/// cette fonction retourne la position Y d'un objet
///
/// @param[in] rien
/// @return position Y.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::getPosDataBidingY()
{
	return arbre_->getPosiY();

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::effacerObjet()
///
/// cette fonction enleve un objet de la scene
///
/// @param[in] rien
/// @return rien.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::effacerObjet()
{
	arbre_->effacerSelection();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerObjet(double x, double y)
///
/// cette deplace un objet selon les coordonn�es en param
///
/// @param[in] double x: position en x
///	    		double y : position en y			
/// @return rien.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerObjet(double x, double y, double angle, double scale)
{
	glm::dvec3 NouvPos{x, y, 0.f}; //la nouvelle position a assigner
	double nvAngle= utilitaire::DEG_TO_RAD(angle); //conversion degre en rad 
	arbre_->deplacerObjet(NouvPos, nvAngle, scale);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::nombreObjetSelectionne()
///
/// cette fonction permet de retourner le nombre des objets selectionnes sur la scene
///
/// @param[in] rien
///	    		
/// @return nombre des objets selectionn�es .
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::nombreObjetSelectionne()
{
	return arbre_->obtenirNombreObjetSelctionnes();

}


////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::getAngle()
///
/// Cette fonction permet de retourner l'angle d'un objet
/// 
/// @param[in] rien
///
/// @return l'angle d'un objet
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::getAngle()
{
	return arbre_->getAngleDataBinding();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::getScale()
///
/// Cette fonction permet de retourner le scale d'un objet
/// 
/// @param[in] rien
///
/// @return le scale d'un objet
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::getScale()
{
	return arbre_->getScaleDataBinding();

}


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::void FacadeModele::supprimerDernierObjet()
///
/// Cette fonction permet de supprimer le dernier objet ajout�
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimerDernierObjet()
{
	arbre_->effacer(arbre_->chercher(arbre_->obtenirNombreEnfants()-1));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool objetEstDansLaTable()
///
/// Cette fonction de retourner faux si un objet a l'exterieur de la table
///
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::objetEstDansLaTable()
{
	return arbre_->objetEstDansLaTable();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn CoefficientConfiguration FacadeModele::getCoefficient()
///
///	Permet d'obtenir les coefficients de friction, de rebond et d'acc�l�ration
///
/// @return	friction	: Coefficient de friction,
///			rebond		: Rebond des murs,
///			acceleration: Acc�l�ration des bonus vitesse
///
////////////////////////////////////////////////////////////////////////
CoefficientConfiguration FacadeModele::getCoefficient() const {
	return this->coeff_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setCoefficient()
///
///	Permet de modifier les coefficients de friction, de rebond et d'acc�l�ration
///
/// @param[in] coeff: Objet de transport de coefficients
///			friction	: Coefficient de friction,
///			rebond		: Rebond des murs,
///			acceleration: Acc�l�ration des bonus vitesse
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setCoefficient(CoefficientConfiguration coeff) {
	coeff.friction = std::min(std::max(coeff.friction, COEFFICIENTS_MINIMAUX.friction), COEFFICIENTS_MAXIMAUX.friction);
	coeff.rebond = std::min(std::max(coeff.rebond, COEFFICIENTS_MINIMAUX.rebond), COEFFICIENTS_MAXIMAUX.rebond);
	coeff.acceleration = std::min(std::max(coeff.acceleration, COEFFICIENTS_MINIMAUX.acceleration), COEFFICIENTS_MAXIMAUX.acceleration);

	this->coeff_ = coeff;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  initialiserScene()
///
/// Cette fonction permet d'initialiser la scene 
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserScene()
{
	arbre_->initialiser();
}


void FacadeModele::ajouterMailletEtRondelle()
{
	//ajout de la rondelle et les maillets
	arbre_->ajouterMailletEtRondelle();
}

void FacadeModele::retirerMailletEtRondelle()
{
	//effacer les maillets et la rondelle
	arbre_->effacer(arbre_->chercher("rondelle"));

	while (arbre_->chercher("maillet")) {
		arbre_->effacer(arbre_->chercher("maillet"));
	}

}