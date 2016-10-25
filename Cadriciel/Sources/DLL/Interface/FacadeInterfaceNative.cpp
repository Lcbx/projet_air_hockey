////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#pragma once


#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"
#include "Selection.h"
#include "Souris.h"

#include "AideGL.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"
#include "BancTests.h"

//using namespace std;



extern "C"
{
	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	///
	/// Cette fonction initialise un contexte OpenGL dans la fenêtre
	/// identifiée par le handle passé en paramètre.  Cette fonction doit
	/// être la première à être appelée, car la création de l'objet du modèle
	/// C++ s'attend à avoir un contexte OpenGL valide.
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND) handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction libère le contexte OpenGL. Cette fonction doit être la
	/// dernière à être appelée, car elle libère également l'objet du modèle
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();
		

		// Désinitialisation de la façade.  Le fait de le faire après la
		// désinitialisation du contexte OpenGL aura pour conséquence que la
		// libération des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
		// meme chose avec souris
		Souris::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la scène.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		// Affiche la scène.
		FacadeModele::obtenirInstance()->afficher();

		// Temporaire: pour détecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit être appelée lorsque la fenêtre est
	/// redimensionnée afin d'ajuster les paramètres de la machine à états
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fenêtre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fenêtre.
	/// @param[in] hauteur : La nouvelle hauteur de la fenêtre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(largeur, hauteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl animer(double temps)
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
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float) temps);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomIn()
	///
	/// Cette fonction applique un zoom avant sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomOut()
	///
	/// Cette fonction applique un zoom arrière sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	///
	/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	///
	/// @return Le nombre d'affichage par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl executerTests()
	{
		bool reussite = BancTests::obtenirInstance()->executer();
		return reussite ? 0 : 1;
	}

	
	// Click
	__declspec(dllexport) void __cdecl etatDelaSouris(int etat) {
		Souris::obtenirInstance()->EtatdelaSouris(etat);
	}

	__declspec(dllexport) void __cdecl clickStart(int x, int y)
	{
		Souris::obtenirInstance()->startClick(x, y);
	}
	__declspec(dllexport) bool __cdecl clickCurrent(int x, int y)
	{
		return Souris::obtenirInstance()->currentClick(x, y);
	}
	__declspec(dllexport) void __cdecl clickEnd(int x, int y)
	{
		Souris::obtenirInstance()->endClick(x, y);
	}
	__declspec(dllexport) bool __cdecl positionSouris(int x, int y)
	{
		return Souris::obtenirInstance()->sourisPostition(x, y);
	}
	__declspec(dllexport) void rightClick(bool presse)
	{
		Souris::obtenirInstance()->clickRight(presse);
	}

	//touche control
	__declspec(dllexport) void __cdecl toucheControl(bool presse)
	{
		Souris::obtenirInstance()->setControl(presse);
	}

	//touche alt
	__declspec(dllexport) void __cdecl toucheAlt(bool presse)
	{
		Souris::obtenirInstance()->setAlt(presse);
	}
	
	
	////touche escape
	__declspec(dllexport) void escEnfonce()
	{
		Souris::obtenirInstance()->escPresse();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ajouterPortail()
	///
	/// Cette fonction ajoute le premier portail a la table 
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void ajouterPortail(int x1, int y1)
	{
		FacadeModele::obtenirInstance()->ajouterPortail(x1, y1);
	}


	/*__declspec(dllexport) void escEnfonce(bool escTouche) 
	{
		std::printf("je suis ici dans facade native");
		//prend un bool en param (touche esc est enfonce ou pas)
		FacadeModele::obtenirInstance()->supprimerPortail(escTouche);
		
	}*/


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ajouterPortailDeux()
	///
	/// Cette fonction ajoute le deuxieme portail a la table 
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void ajouterPortailDeux(int x2, int y2)
	{
		FacadeModele::obtenirInstance()->ajouterPortailDeux(x2, y2);
	}




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) double __cdecl getPosX()
	///
	/// Cette fonction permet de determiner la positon relative X d'un objet
	///
	/// @return position d'un objet en X
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl getPosX()
	{
		return FacadeModele::obtenirInstance()->getPosDataBidingX();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) double __cdecl getPosY()
	///
	/// Cette fonction permet de determiner la positon relative y d'un objet
	///
	/// @return position d'un objet en Y
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl getPosY()
	{
		return FacadeModele::obtenirInstance()->getPosDataBidingY();
	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl supprimerObjet()
	///
	/// Cette fonction permet de supprimer les objets
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void supprimerObjet()
	{
		return FacadeModele::obtenirInstance()->effacerObjet();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl deplacerObjet(double x, double y, double angle, double scale)
	///
	/// Cette fonction de deplacer un objet a partir des coordonnees 
	/// entrées dans la boite config
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void configurerObjet(double x, double y, double angle, double scale)
	{
		return FacadeModele::obtenirInstance()->deplacerObjet(x, y, angle, scale);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl nombreObjetSelectionne()
	///
	/// Cette fonction permet de retourner le nonnbre d'objets selectionnes
	///
	/// @return Le nombre d'objets selectionnées
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl nombreObjetSelectionne()
	{
		return FacadeModele::obtenirInstance()->nombreObjetSelectionne();
	}




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) double __cdecl getAngle()
	///
	/// Cette fonction permet de retourner l'angle d'un objet 
	///
	/// @return L'angle d'un objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl getAngle()
	{
		return FacadeModele::obtenirInstance()->getAngle();
	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void DeplacerVueXY();
	///
	/// Cette fonction permet de deplacer la camera de la vue sur le plan
	///    perpendiculaire à la direction regardée
	///
	/// @return void
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerVueXY(double deplacementX, double deplacementY)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(deplacementX, deplacementY);
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) double __cdecl getScale()
	///
	/// Cette fonction permet de retourner le scale d'un objet 
	///
	/// @return Le scale d'un objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl getScale()
	{
		return FacadeModele::obtenirInstance()->getScale();
	}

	__declspec(dllexport) bool __cdecl objetEstDansLaTable()
	{
		return FacadeModele::obtenirInstance()->objetEstDansLaTable();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void setCoefficient(double friction, double rebond, double acceleration)
	/// @brief Permet de changer les coefficients de la table de jeu
	///
	/// Permet de changer les coefficients de la table à travers l'objet de transport des coefficients
	///
	/// @param[in] friction : Coefficient de friction
	/// @param[in] rebond : Coefficient de rebond
	/// @param[in] acceleration : Coefficient d'acceleration
	/// 
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void setCoefficient(double friction, double rebond, double acceleration) {
		FacadeModele::obtenirInstance()->setCoefficient({friction, rebond, acceleration});
	}
	

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) double getCoefficientFriction()
	/// @brief Permet d'obtenir le coefficient de friction
	///
	/// Permet d'obtenir le coefficient de friction pour la table
	///
	/// @return Le coefficient de friction de la table
	/// 
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getCoefficientFriction() {
		return FacadeModele::obtenirInstance()->getCoefficient().friction;
	}
		


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) double getCoefficientRebond()
	/// @brief Permet d'obtenir le coefficient de friction
	///
	/// Permet d'obtenir le coefficient de rebond
	///
	/// @return Le coefficient de rebond de la table
	/// 
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getCoefficientRebond() {
		return FacadeModele::obtenirInstance()->getCoefficient().rebond;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn	__declspec(dllexport) double getCoefficientAcceleration()
	/// @brief Permet d'obtenir le coefficient de friction
	///
	/// Permet d'obtenir le coefficient d'accélération
	///
	/// @return Le coefficient d'accélération de la table
	/// 
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getCoefficientAcceleration() {
		return FacadeModele::obtenirInstance()->getCoefficient().acceleration;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void enregistrerZoneJeu(char *fichierZoneJeu)
	///
	/// Cette fonction permet de sauvegarder la zone de jeu dans un fichier 
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl enregistrerZoneJeu(char *fichierZoneJeu)
	{
		FacadeModele::obtenirInstance()->enregistrerZoneJeu(fichierZoneJeu);
	}

	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void chargerZoneJeu(char *fichierZoneJeu)
	///
	/// Cette fonction permet de charger la zone de jeu contenue dans un fichier 
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl chargerZoneJeu(char *fichierZoneJeu)
	{
		FacadeModele::obtenirInstance()->chargerZoneJeu(fichierZoneJeu);
	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn 	__declspec(dllexport) void __cdecl initialiserScene()
	///
	/// Cette fonction permet d'initialiser la scene 
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserScene()
	{
		FacadeModele::obtenirInstance()->initialiserScene();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn 	__declspec(dllexport) void __cdecl ajouterMailletEtRondelle()
	///
	/// Cette fonction permet d'ajouter les maillets et la rondelle
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ajouterMailletEtRondelle()
	{
		FacadeModele::obtenirInstance()->ajouterMailletEtRondelle();

	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn  __declspec(dllexport) void __cdecl retirerMailletEtRondelle()
	///
	/// Cette fonction permet de retirer les maillets et la rondelle pour le mode edition
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl retirerMailletEtRondelle()
	{
		FacadeModele::obtenirInstance()->retirerMailletEtRondelle();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn 		__declspec(dllexport) void deplacerMailletAvecClavier()
	///
	/// Cette fonction permet de deplacer le maillet avec les touches de clavier
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerMailletAvecClavier(double x, double y)
	{
		FacadeModele::obtenirInstance()->deplacerMailletAvecClavier(x, y);
	}


	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void reinitialiserPartieCourante();
	///
	/// Cette fonction permet de deplacerRe-initialiser la partie
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl reinitialiserPartieCourante()
	{
		FacadeModele::obtenirInstance()->reinitialiserPartieCourante();

	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void  deplacerVersLaGauche(int toucheDeplacementAGauche);
	///
	/// Cette fonction permet de deplacer l'objet vers la gauche
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void  deplacerVersLaGauche(int toucheDeplacementAGauche);
	//{
		//FacadeModele:: obtenirInstance()
	//}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void deplacertVersLaDroite(int toucheDeplacementADroite_);
	///
	/// Cette fonction permet de deplacer l'objet vers la droite
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void deplacertVersLaDroite(int toucheDeplacementADroite_);
	//{
		//FacadeModele::obtenirInstance

	//}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void deplacerVersLeHaut(int toucheDeplacementEnHaut_);
	///
	/// Cette fonction permet de deplacer l'objet vers le haut
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void deplacerVersLeHaut(int toucheDeplacementEnHaut_);
	//{
		//FacadeModele::obtenirInstance()

	//}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ___declspec(dllexport)  void deplacerVersLeBas(int toucheDeplacementEnBas_);
	///
	/// Cette fonction permet de deplacer l'objet vers le bas 
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport)  void deplacerVersLeBas(int toucheDeplacementEnBas_);
	//{
		//FacadeModele::obtenirInstance()->

	//}




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn 		__declspec(dllexport) void deplacerMailletAvecSouris()
	///
	/// Cette fonction permet de deplacer le maillet avec la souris
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerMailletAvecSouris(double x, double y)
	{
		FacadeModele::obtenirInstance()->deplacerMailletAvecSouris(x, y);
	}

	////////////////////////////////////////////////////////////////////////
	/// Author : Ali
	/// @fn 		__declspec(dllexport) void virtuelDefensif();
	///
	/// Cette fonction permet de deplacer le maillet du joueur virtuel
	/// selon un scenario defensif
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl virtuelDefensif()
	{
		FacadeModele::obtenirInstance()->virtuelDefensif();
	}


}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
