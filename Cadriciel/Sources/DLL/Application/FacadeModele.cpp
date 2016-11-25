///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la première page de la documentation Doxygen.
/**

@mainpage Projet intégrateur de deuxième année -- INF2990

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
// Julien Gascon-Samson, été 2011
#include "tinyxml2.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "EtatOpenGL.h"
#include <iostream>
#include "Noeuds/NoeudTypes.h"

#include "../SauvegardeZoneDeJeu.h"

#include "JoueurVirtuel.h"
#include "../ConfigTournoi.h"

#include "../Application/TextOpenGL.h"

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_{ nullptr };


/// Chaîne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "donnees\\configuration.xml" };

/// Chaîne indiquant le nom du fichier de la zone de jeu par défaut.
const std::string FacadeModele::FICHIER_ZONEDEFAUT{ "ZoneDefaut.xml" };


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas été créée, elle la crée.  Cette
/// création n'est toutefois pas nécessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa création.
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
/// Cette fonction libère l'instance unique de cette classe.
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
/// Ce destructeur libère les objets du modèle.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	delete arbre_;
	delete vue_;
	if (this->tournoi_ != nullptr) {
		delete this->tournoi_;
		this->tournoi_ = nullptr;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle crée
/// un contexte OpenGL sur la fenêtre passée en paramètre, initialise
/// FreeImage (utilisée par le chargeur de modèles) et assigne des 
/// paramètres du contexte OpenGL.
///
/// @param[in] hWnd : La poignée ("handle") vers la fenêtre à utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être créé.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// Initialisation de la configuration
	chargerConfiguration();

	// FreeImage, utilisée par le chargeur, doit être initialisée
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);

	// Qualité
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Création de l'arbre de rendu.  À moins d'être complètement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de créer
	// l'arbre après avoir créé le contexte OpenGL.
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();
	
	// On crée une vue par défaut.
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
/// Cette fonction charge la configuration à partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est généré à
/// partir de valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// Vérification de l'existance du ficher
	
	// Si le fichier n'existe pas, on le crée.
	if (!utilitaire::fichierExiste(FICHIER_CONFIGURATION)) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {
		tinyxml2::XMLDocument document;

		// Lire à partir du fichier de configuration
		document.LoadFile(FacadeModele::FICHIER_CONFIGURATION.c_str());

		// On lit les différentes configurations.
		ConfigScene::obtenirInstance()->lireDOM(document);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction génère un fichier XML de configuration à partir de
/// valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	tinyxml2::XMLDocument document;
	// Écrire la déclaration XML standard...
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	
	// On enregistre les différentes configurations.
	ConfigScene::obtenirInstance()->creerDOM(document);
	
	// Écrire dans le fichier
	document.SaveFile(FacadeModele::FICHIER_CONFIGURATION.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerZoneJeu(std::string fichierZoneJeu) const
///
/// Cette fonction charge la zone de jeu à partir d'un fichier XML.
///
/// @param[in] fichierZoneJeu : Nom du fichier à charger.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerZoneJeu(char* fichierZoneJeu) const
{

	// Créé le document XML à partir du fichier spécifié
	tinyxml2::XMLDocument document;
	document.LoadFile(fichierZoneJeu);

	// Créé l'arbre de rendu à partir du document XML
	SauvegardeZoneDeJeu::lireArbre(document);

}


///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerZoneJeu(std::string fichierZoneJeu) const
///
/// Cette fonction genere un fichier XML contenant la zone de jeu actuelle.
///
/// @param[in] fichierZoneJeu : Nom du fichier àdans lequel sauvegarder.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::enregistrerZoneJeu(char* fichierZoneJeu) const
{
	// Génère une erreur si le nom du fichier correspond au fichier de zone par défaut
	if (fichierZoneJeu == FICHIER_ZONEDEFAUT)
		std::cerr << "Erreur : Tentative de modification de la zone de jeu par défaut" << std::endl;

	// Créé un document XML avec la déclaration XML standard
	tinyxml2::XMLDocument document;
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");

	// Créé le document XML à partir de l'arbre de rendu
	SauvegardeZoneDeJeu::creerArbre(document);

	// Enregistrer le document XML dans le fichier
	document.SaveFile(fichierZoneJeu);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ConfigTouches getConfigTouches()
///
/// Cette fonction retourne l'objet ConfigTouches de FacadeModele, afin
/// de manipuler les touches du joueur 2
///
/// @return ConfigTouches : l'objet ConfigTouches de l'instance de FacadeModele
///
////////////////////////////////////////////////////////////////////////
ConfigTouches* FacadeModele::getConfigTouches()
{
	return &_configTouches;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ConfigJeu getConfigJeu()
///
/// Cette fonction retourne l'objet ConfigJeu de FacadeModele, afin
/// de manipuler les options de jeu
///
/// @return ConfigJeu : l'objet ConfigJeu de l'instance de FacadeModele
///
////////////////////////////////////////////////////////////////////////
ConfigJeu* FacadeModele::getConfigJeu()
{
	return &_configJeu;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ConfigDebug getConfigDebug()
///
/// Cette fonction retourne l'objet ConfigDebug de FacadeModele, afin
/// de manipuler les options de debug
///
/// @return ConfigDebug : l'objet ConfigDebug de l'instance de FacadeModele
///
////////////////////////////////////////////////////////////////////////
ConfigDebug* FacadeModele::getConfigDebug()
{
	return &_configDebug;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ConfigProfils getConfigProfils()
///
/// Cette fonction retourne l'objet ConfigProfil de FacadeModele, afin
/// de manipuler les profils enregistrés
///
/// @return ConfigProfils l'objet ConfigProfils de l'instance de FacadeModele
///
////////////////////////////////////////////////////////////////////////
ConfigProfils* FacadeModele::getConfigProfils()
{
	return &_configProfils;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libère le contexte OpenGL et désinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On libère les instances des différentes configurations.
	ConfigScene::libererInstance();


	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être détruit.");

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scène.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Afficher la scène
	afficherBase();

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// creation d'une instance TextOpenGL
	if (partieRapide_)	// TODO -- set partie rapide a false qd on sort de la partie rapide
	{
		TextOpenGL text;
		text.afficher();
	}
	
		
	// Échange les tampons pour que le résultat du rendu soit visible.
	::SwapBuffers(hDC_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la scène, c'est-à-dire
/// qu'elle met en place l'éclairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la caméra
	glm::mat4 vueProjection(vue_->obtenirProjection().obtenirMatrice() * vue_->obtenirCamera().obtenirMatrice());

	// Afficher la scène.
	arbre_->afficher(vueProjection);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction réinitialise la scène à un état "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// Réinitialisation de la scène.
	arbre_->initialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les différents calculs d'animations
/// nécessaires pour le mode jeu, tel que les différents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise à jour des objets.
	arbre_->animer(temps);

	// Mise à jour de la vue.
	vue_->animer(temps);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::ajouterBonus(int x, int y)
///
/// Cette fonction permet d'ajouter le bonus accélerateur a la scene
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
/// @fn void FacadeModele::ajouterPortailDeux(int x2, int y2)
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterMuret(int x1, int y1, int x2, int y2)
///
/// Cette fonction permet d'ajouter un muret a la scene
///
/// @param[in]	x1, y1 : position du premier clic de la souris.
///				x2, y2 : position du second clic de la souris .
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
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
/// cette deplace un objet selon les coordonnées en param
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
/// @return nombre des objets selectionnées .
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
/// Cette fonction permet de supprimer le dernier objet ajouté
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
///	Permet d'obtenir les coefficients de friction, de rebond et d'accélération
///
/// @return	friction	: Coefficient de friction,
///			rebond		: Rebond des murs,
///			acceleration: Accélération des bonus vitesse
///
////////////////////////////////////////////////////////////////////////
CoefficientConfiguration FacadeModele::getCoefficient() const {
	return this->coeff_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setCoefficient()
///
///	Permet de modifier les coefficients de friction, de rebond et d'accélération
///
/// @param[in] coeff: Objet de transport de coefficients
///			friction	: Coefficient de friction,
///			rebond		: Rebond des murs,
///			acceleration: Accélération des bonus vitesse
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void ajouterMailletEtRondelle()
///
/// Cette fonction permet d'Ajouter les maillets et la rondelle
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterMailletEtRondelle()
{
	//ajout de la rondelle et les maillets
	arbre_->ajouterMailletEtRondelle();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void retirerMailletEtRondelle()
///
/// Cette fonction permet de retirer les maillets et la rondelle
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::retirerMailletEtRondelle()
{
	//effacer les maillets et la rondelle
	arbre_->effacer(arbre_->chercher("rondelle"));

	while (arbre_->chercher("maillet")) {
		arbre_->effacer(arbre_->chercher("maillet"));
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn deplacerMailletAvecClavier(double x, double y)
///
/// Cette fonction permet de deplacer le maillet avedc les touches de clavier
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerMailletAvecClavier(double x, double y)
{
	arbre_->deplacerMailletAvecClavier(x, y);

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void reinitialiserPartieCourante()
///
/// Cette fonction permet de re-initialiser la scene, donc mettre les maillets et la rondelle
/// a la position de depart
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiserPartieCourante()
{
	arbre_->reinitialiserPartieCourante();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void deplacerMailletAvecSouris(glm::dvec3 pos)
///
/// Cette fonction permet de deplacer le maillet avec la souris
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerMailletAvecSouris(double x, double y)
{
	glm::dvec3 posDeplacement;
	vue_->convertirClotureAVirtuelle(x, y, posDeplacement);
	arbre_->deplacerMailletAvecSouris(posDeplacement);

	// test fct appartient
	//if (arbre_->getTable()->appartientDroite({ 0,50,0 }, { 0,-50,0 }, { 0,0,0 }))
	//	std::cout << "Yay!";


	/*if (arbre_->joueurVirtuelDefensif)
		this->virtuelDefensif(10.,1);*/
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void activerRayonAttraction()
/// Author : Ali
/// Cette fonction permet d'activer l'affichage du rayon d'attraction
/// des portails 
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::activerRayonAttraction()
{
	arbre_->activerRayonPortail();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void deactiverRayonAttraction()
/// Author : Ali
/// Cette fonction permet de desactiver l'affichage du rayon d'attraction
/// des portails
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deactiverRayonAttraction()
{
	arbre_->deactiverRayonPortail();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void effacerPointControle()
/// Author : Ali
/// Cette fonction permet d'effacer les points de controle de la table
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::effacerPointControle()
{
	arbre_->effacerPointControle();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void afficherPointControle()
/// Author : Ali
/// Cette fonction permet d'afficher les points de controle de la table
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherPointControle()
{
	arbre_->afficherPointControle();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ActiverJoueurVirtuel(float vitesse, int probabilite )
/// Author : Ali
/// Cette fonction permet de deplacer le maillet du joueur virtuel
/// param [in] vitesse : la vitesse du maillet virtuel
///				probabilite : probabilite d'etre passif (rien faire)
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ActiverJoueurVirtuel(double vitesse, double probabilite)
{	

	if (joueurVirtuelActive_)
		
	{
		JoueurVirtuel J;
		J.setVitesse(vitesse);
		J.setProbabilite(probabilite);
		//J.setVitesse(vitesseVirtuelle_);
		//J.setProbabilite(probabilite_);
		J.deplacerMailletVirtuel();

	}
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setjoueurVirtuel(bool activer)
/// Author : Ali
/// Cette fonction permet de modifier la variable joueurVirtuelActive_
/// qui determine si le joueur virtuel est active' ou non
/// param[in] 
///			activer : true pour activer le joueur , false le cas contraire
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setjoueurVirtuel(bool activer)
{
	joueurVirtuelActive_ = activer;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::getjoueurVirtuel()
/// Author : Ali
/// Cette fonction permet de savoir si le joueur virtuel est active ou non
///
/// @return bool : true si active' , false sinon
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::getjoueurVirtuel()
{
	return joueurVirtuelActive_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::getVitesseVirtuel()
///
/// Author : Ali
/// Cette fonction permet de recuperer la vitesse du maillet virtuelle
/// @return double
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::getVitesseVirtuel()
{
	return vitesseVirtuelle_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setVitesseVirtuel( double vitesse)
///
/// Author : Ali
/// Cette fonction permet de modifier la vitesse du maillet virtuelle
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setVitesseVirtuel( double vitesse)
{
	vitesseVirtuelle_ = vitesse;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::getProbabiliteVirtuel()
///
/// Author : Ali
/// Cette fonction permet de recuperer la prob d'etre passif du maillet virtuelle
/// @return double
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::getProbabiliteVirtuel()
{
	return probabilite_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setProbabiliteVirtuel(double probabilite )
///
/// Author : Ali
/// Cette fonction permet de modifier la prob d'etre passif du maillet virtuelle
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setProbabiliteVirtuel(double probabilite )
{
	probabilite_ = probabilite;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setButDroite(bool but)
///
/// Author : Ali
/// Cette fonction permet de modifier la valeur but droit
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setButDroite(bool but)
{
	butDroite_ = but;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setButGauche(bool but)
///
/// Author : Ali
/// Cette fonction permet de modifier la valeur but gauche
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setButGauche(bool but)
{
	butGauche_ = but;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::getButDroite()
///
/// Author : Ali
/// Cette fonction permet de recuperer la valeur but droit
/// @return rien
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::getButDroite()
{
	return butDroite_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::getButGauche()
///
/// Author : Ali
/// Cette fonction permet de recuperer la valeur but gauche
/// @return rien
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::getButGauche()
{
	return butGauche_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::setNombreButs(int nombre)
///
/// Author : Ali
/// Cette fonction permet de modifier la valeur du nombre 
/// de but necessaire pour gagner une partie
///
/// parm[in] int nombre : nombre entre 1 et 5
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::setNombreButs(int nombre)
{
	if (nombre < 1 || nombre > 5)
		return false;
	nombreButsMax_ = nombre;
	return true;	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::getNombreButs()
///
/// Author : Ali
/// Cette fonction permet de recuperer la valeur du nombre 
/// de but necessaire pour gagner une partie
/// @return int 
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::getNombreButs()
{
	return nombreButsMax_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::getPartieRapide()
///
/// Author : Ali
/// Cette fonction permet de savoir si on est en mode partie rapide ou non
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::getPartieRapide()
{
	return partieRapide_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setPartieRapide(bool activer)
///
/// Author : Ali
/// Cette fonction permet d'activer ou deactiver le mode partie rapide 
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setPartieRapide(bool activer)
{
	partieRapide_ = activer;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::activerRondelle()
///
/// Author : Ali
/// @Brief :  Cette fonction permet d'activer la rondelle - apres la pause
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::activerRondelle()
{
	rondelleEnPause_ = false;

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deactiverRondelle()
///
/// Author : Ali
/// @Brief :  Cette fonction permet de mettre la rondelle en pause
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deactiverRondelle()
{
	rondelleEnPause_ = true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::estEnPauseRondelle()
///
/// Author : Ali
/// @Brief :  Cette fonction permet de savoir si la rondelle est en pause 
/// ou non 
/// @return bool : true si en pause / false sinon
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::estEnPauseRondelle()
{
	return rondelleEnPause_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn std::string FacadeModele::getnomJoueur(int index)
///
/// Author : Ali
/// @Brief :  Cette fonction permet de recuperer le nom d'un joueur courant
/// @ param[in] int index : le numero du joueur a recuperer
/// @return  std::string 
///
////////////////////////////////////////////////////////////////////////
std::string FacadeModele::getNomJoueurCourant(int index)
{	
	if (index == 1)
		return nomJoueurCourant1_;
	else
		if (index == 2)
			return nomJoueurCourant2_;
		else
		{
			std::string default = "default";
			return default;
		}
			
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::setNomJoueurCourant(std::string nom, int index)
///
/// Author : Ali
/// @Brief :  Cette fonction permet de modifier le nom d'un joueur courant
/// @ param[in] int index : le numero du joueur a recuperer
///				std::string nom : le nom a assigner
/// @return  bool 
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::setNomJoueurCourant(std::string nom, int index)
{
	if (index == 1)
	{
		nomJoueurCourant1_.assign(nom);
		return true;
	}
		
	else
		if (index == 2)
		{
			nomJoueurCourant2_.assign(nom);
			return true;
		}
		else
			return false;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::getScoreCourant(int index)
///
/// Author : Ali
/// @Brief :  Cette fonction permet de recuperer le score courant d'un joueur
/// @ param[in] int index : le numero du joueur a recuperer
/// @return  int
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::getScoreCourant(int index)
{
	if (index == 1)
		return scoreJoueurCourant1_;
	else
		if (index == 2)
			return scoreJoueurCourant2_;
		else // soit joueur2 par default 
			return scoreJoueurCourant2_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::setScoreCourant(int score, int index)
///
/// Author : Ali
/// @Brief :  Cette fonction permet de modifier le score d'un joueur courant
/// @ param[in] int index : le numero du joueur courant
///				int score : le score a modifier 
/// @return  bool 
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::setScoreCourant(int score, int index)
{
	if (index == 1)
	{
		scoreJoueurCourant1_ = score;
		return true;
	}

	else
		if (index == 2)
		{
			scoreJoueurCourant2_ = score;
			return true;
		}
		else
			return false;
}


 ////////////////////////////////////////////////////////////////////////
///
/// @fn std::string getConfigFile();
///
///	Permet d'obtenir la chaine de caractère correspondant au nom du
/// fichier de configuration
///
/// @return	std::string	: Nom du fichier de configuration
///
////////////////////////////////////////////////////////////////////////
/*std::string FacadeModele::getConfigFile() {
	return FICHIER_CONFIGURATION;
}*/

/// @fn void FacadeModele::creerTournoi(const char* nomZone, const int count, const char** nomsJoueurs, const bool* sontHumains, const char** nomProfils)
/// @brief Permet de créer un tournoi
/// @param nomZone : Nom de la zone de jeu
/// @param count : Nombre de joueurs
/// @param nomsJoueurs : Noms des joueurs
/// @param sontHumains : Si les joueurs sont humains ou non
/// @param nomProfils : Si le joueur est virtuel, le nom du profil
void FacadeModele::creerTournoi(const char* nomZone, const int count, const char** nomsJoueurs, const bool* sontHumains, const char** nomProfils) {
	std::string zoneDeJeu(nomZone);
	std::vector<AdaptateurJoueur> joueurs;
	for (int i = 0; i < count; i++) {
		std::string nomJoueur(nomsJoueurs[i]);
		bool estHumain = sontHumains[i];
		std::string nomProfil(nomProfils[i]);
		AdaptateurJoueur joueur(nomJoueur, estHumain, nomProfil);
		joueurs.push_back(joueur);
	}
	this->tournoi_ = new Tournoi<AdaptateurJoueur>(joueurs, nomZone);
	ConfigTournoi::sauvegarderJoueurs(joueurs, nomZone);
}


/// @fn void FacadeModele::loadTournoi(const char* nomZone, const int count, const char** nomsJoueurs, const bool* sontHumains, const char** nomProfils)
/// @brief Permet de charger la configuration d'un tournoi
/// @param[out] nomZone : Nom de la zone de jeu
/// @param[in] count : Nombre de joueurs
/// @param[out] nomsJoueurs : Noms des joueurs
/// @param[out] sontHumains : Si les joueurs sont humains ou non
/// @param[out] nomProfils : Si le joueur est virtuel, le nom du profil
void FacadeModele::loadTournoi(char* nomZone, int count, char* nomsJoueurs, bool* sontHumains, char* nomProfils) {
	std::vector<AdaptateurJoueur> joueurs;
	std::string zone;
	ConfigTournoi::obtenirJoueurs(joueurs, zone);
	strcpy(nomZone, zone.c_str());
	
	int iNom = 0;
	int iProfil = 0;
	for (int i = 0; i < count; i++) {
		std::string nomJoueur = joueurs[i].getNomJoueur();
		int j = 0;
		while (j < nomJoueur.length()) {
			nomsJoueurs[iNom + j] = nomJoueur[j];
			j++;
		}
		nomsJoueurs[iNom + j] = '\0';
		iNom += ++j;

		sontHumains[i] = joueurs[i].estHumain();

		std::string nomProfil = joueurs[i].getProfil().getNom();
		j = 0;
		while (j < nomProfil.length()) {
			nomProfils[iProfil + j] = nomProfil[j];
			j++;
		}
		nomProfils[iProfil + j] = '\0';
		iProfil += ++j;
	}
}

void FacadeModele::jouerSonModeJeu(bool mode)
{
	if (mode == true)
	{
		this->obtenirArbreRenduINF2990()->player->jouerSon(3);
	}
	else {
		this->obtenirArbreRenduINF2990()->player->arreterSon();
	}
}


void FacadeModele::MettrePauseSonModeJeu(bool pause)
{
	this->obtenirArbreRenduINF2990()->player->pauseSon(pause);
}