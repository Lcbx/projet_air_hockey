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
#include "../Affichage_debuggage.h"

///TODO: Retirer pour la remise
#include "../Tournoi.h"

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

	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl etatDelaSouris(int etat)
	///
	/// Cette fonction est appelée quand on change d,outil d'edition
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl etatDelaSouris(int etat) {
		Souris::obtenirInstance()->EtatdelaSouris(etat);
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl clickStart(int x, int y)
	///
	/// Cette fonction est appelée au debut d'un click de la souris
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl clickStart(int x, int y)
	{
		Souris::obtenirInstance()->startClick(x, y);
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl clickCurrent(int x, int y)
	///
	/// Cette fonction est appelée au cours d'un click de la souris
	///
	/// @return un booleen signifiant que l'emplacement est dans la table.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl clickCurrent(int x, int y)
	{
		return Souris::obtenirInstance()->currentClick(x, y);
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl clickEnd(int x, int y)
	///
	/// Cette fonction est appelée à la fin d'un click de la souris
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl clickEnd(int x, int y)
	{
		Souris::obtenirInstance()->endClick(x, y);
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl positionSouris(int x, int y)
	///
	/// Cette fonction est appelée quand la souris n'est pas pesee
	///
	/// @return un booleen signifiant que l'emplacement est dans la table.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl positionSouris(int x, int y)
	{
		return Souris::obtenirInstance()->sourisPostition(x, y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl rightClick(bool presse)
	///
	/// Cette fonction est appelée quand le bouton droit de la souris est pese
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void rightClick(bool presse)
	{
		Souris::obtenirInstance()->clickRight(presse);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl toucheControl(bool presse)
	///
	/// Cette fonction est appelée quand la touche control est pressée
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl toucheControl(bool presse)
	{
		Souris::obtenirInstance()->setControl(presse);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl toucheAlt(bool presse)
	///
	/// Cette fonction est appelée quand la touche alt est pressée
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl toucheAlt(bool presse)
	{
		Souris::obtenirInstance()->setAlt(presse);
	}
	

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl escEnfonce()
	///
	/// Cette fonction est appelée quand la touche echap est pressée
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
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
	/// @fn __declspec(dllexport) void touches(int toucheDeplacementAGauche_, int toucheDeplacementADroite_, int toucheDeplacementEnHaut_, int toucheDeplacementEnBas_);
	///
	/// Cette fonction permet de deplacer maillet
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void  touches(int toucheDeplacementAGauche_, int toucheDeplacementADroite_, int toucheDeplacementEnHaut_, int toucheDeplacementEnBas_);
	//{
		//FacadeModele:: obtenirInstance()
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
	/// @fn 		__declspec(dllexport) void afficherRayonAttraction();
	/// Author : Ali
	/// Cette fonction permet d'afficher le rayon d'attraction
	/// des portails
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl afficherRayonAttraction()
	{
		FacadeModele::obtenirInstance()->activerRayonAttraction();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 		__declspec(dllexport) void enleverRayonAttraction();
	/// Author : Ali
	/// Cette fonction permet d'enlever le rayon d'attraction 
	/// des portail
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl enleverRayonAttraction()
	{
		FacadeModele::obtenirInstance()->deactiverRayonAttraction();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 		__declspec(dllexport) void afficherPointControle();
	/// Author : Ali
	/// Cette fonction permet d'afficher les points de controle de
	/// la table
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl afficherPointControle()
	{
		FacadeModele::obtenirInstance()->afficherPointControle();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 		__declspec(dllexport) void effacerPointControle();
	/// Author : Ali
	// Cette fonction permet d'effacer l'affichage les points de controle
	/// de la table
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl effacerPointControle()
	{
		FacadeModele::obtenirInstance()->effacerPointControle();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 		_declspec(dllexport) void activerJoueurVirtuel(double vitesse, double probabilite)
	/// Author : Ali
	/// Cette fonction permet d'activer le mode joueur virtuel
	///	le maillet deplace automatiquement 
	/// param [in] vitesse : la vitesse du maillet virtuel
	///				probabilite : probabilite d'etre passif (rien faire)
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void activerJoueurVirtuel(double vitesse, double probabilite)
	{ 
		FacadeModele::obtenirInstance()->setjoueurVirtuel(true);
		FacadeModele::obtenirInstance()->ActiverJoueurVirtuel(vitesse,probabilite);
		
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 		__declspec(dllexport) void __cdecl setjoueurVirtuel(bool activer)
	/// Author : Ali
	// Cette fonction permet de modifier la variable qui permet d'activer le 
	/// joueur virtuel
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl setjoueurVirtuel(bool activer)
	{
		FacadeModele::obtenirInstance()->setjoueurVirtuel(activer);
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) bool __cdecl getjoueurVirtuel()
	/// Author : Ali
	// Cette fonction permet de recupere la valeur de la variable qui permet d'activer le 
	/// joueur virtuel
	///
	/// @return bool
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl getjoueurVirtuel()
	{
		return FacadeModele::obtenirInstance()->getjoueurVirtuel();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) double getVitesseVirtuel()
	/// Author : Ali
	// Cette fonction permet de recupere la vitessedu joueur virtuel
	///
	/// @return double
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getVitesseVirtuel()
	{
		return FacadeModele::obtenirInstance()->getVitesseVirtuel();
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) double getProbabiliteVirtuel()
	/// Author : Ali
	// Cette fonction permet de recupere la probabilite du joueur virtuel
	///
	/// @return double
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getProbabiliteVirtuel()
	{
		return FacadeModele::obtenirInstance()->getProbabiliteVirtuel();
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) void setProbabiliteVirtuel(double probabilite)
	/// Author : Ali
	// Cette fonction permet de modifier la probabilite du joueur virtuel
	///
	/// @return double
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void setProbabiliteVirtuel(double probabilite)
	{
		double prob;
		if (probabilite < 0)
			prob = 0;
		else
			if (probabilite > 1)
				prob = 1;
			else
				prob = probabilite;
		FacadeModele::obtenirInstance()->setProbabiliteVirtuel(prob);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) void setVitesseVirtuel(double vitesse)
	/// Author : Ali
	// Cette fonction permet de modifier la vitesse du joueur virtuel
	///
	/// @return double
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void  setVitesseVirtuel(double vitesse)
	{
		double v;
		if (vitesse < 0)
			v = 0;
		else
			v = vitesse;
		FacadeModele::obtenirInstance()->setVitesseVirtuel(v);
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) bool estButDroite()
	/// Author : Ali
	/// Cette fonction permet savoir s'il la rondelle a rentre' dans le but 
	/// a droite 
	///
	/// @return bool
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool estButDroite()
	{
		return FacadeModele::obtenirInstance()->getButDroite();
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) bool estButGauche()
	/// Author : Ali
	/// Cette fonction permet savoir s'il la rondelle a rentre' dans le but 
	/// a gauche 
	///
	/// @return bool
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool estButGauche()
	{
		return FacadeModele::obtenirInstance()->getButGauche();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) void setButDroite()
	/// Author : Ali
	/// Cette fonction permet de modifier la varriable butDroite_ 
	/// dans facade modele 
	/// on l'utilise lorsque un des 2 joueurs marque un but 
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void setButDroite(bool etat)
	{
		FacadeModele::obtenirInstance()->setButDroite(etat);		
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) void setButGauche()
	/// Author : Ali
	/// Cette fonction permet de modifier la varriable butGauche_ 
	/// dans facade modele 
	/// on l'utilise lorsque un des 2 joueurs marque un but 
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void setButGauche(bool etat)
	{
		 FacadeModele::obtenirInstance()->setButGauche(etat);		
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) int getNombreButs()
	/// Author : Ali
	/// @brief : Cette fonction permet de recuperer le nombre de buts pour
	/// gagner une partie
	/// 
	/// @return int
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int getNombreButs()
	{
		return FacadeModele::obtenirInstance()->getNombreButs();
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) void setNombreButs(int nombre)
	/// Author : Ali
	/// @brief : Cette fonction permet de modifier le nombre de buts pour
	/// gagner une partie
	/// 
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void setNombreButs(int nombre)
	{
		FacadeModele::obtenirInstance()->setNombreButs(nombre);
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) bool estPartieRapide()
	/// Author : Ali
	/// @brief : Cette fonction permet de savoir si on est en mode partie 
	/// rapide ou non
	/// 
	/// @return bool
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool estPartieRapide()
	{
		return FacadeModele::obtenirInstance()->getPartieRapide();
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) void setPartieRapide(bool activer)
	/// Author : Ali
	/// @brief : Cette fonction permet d'activer ou deactiver le mode partie
	/// rapide 
	/// param[in] bool activer : true si activer / false sinon 
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void setPartieRapide(bool activer)
	{
		FacadeModele::obtenirInstance()->setPartieRapide(activer);
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) void activerRondelle()
	/// Author : Ali
	/// @brief : Cette fonction permet de remettre la rondelle en mouvement
	/// apres qu'elle etait mise en pause
	/// 
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void activerRondelle()
	{
		FacadeModele::obtenirInstance()->activerRondelle();
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) void deactiverRondelle()
	/// Author : Ali
	/// @brief : Cette fonction permet de mettre la rondelle en pause
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void deactiverRondelle()
	{
		FacadeModele::obtenirInstance()->deactiverRondelle();
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) bool estEnPauseRondelle()
	/// Author : Ali
	/// @brief : Cette fonction permet de savoir si la rondelle est en 
	/// pause ou non
	///
	/// @return bool 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool estEnPauseRondelle()
	{
		return FacadeModele::obtenirInstance()->estEnPauseRondelle();
	}
	/// Livrable 3
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) void getNomJoueurCourant(int index, char ** nom)
	/// Author : Ali
	/// @brief : Cette fonction permet d'obtenir le nom du joueur courant
	/// @ param[in] 
	///			int index : le numero du joueur courant (1 ou 2)
	///			char ** nom : pointeur vers la chaine de caracteres du nom
	/// @return rien 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void getNomJoueurCourant(int index, char ** nom)
	{
		std::string str = FacadeModele::obtenirInstance()->getNomJoueurCourant(index);
		char * ptr = new char[str.size() + 1];
		std::copy(str.begin(), str.end(), ptr);
		ptr[str.size()] = '\0'; 
		** nom = *ptr;
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) bool setNomJoueurCourant(char* nom, int index)
	/// Author : Ali
	/// @brief : Cette fonction permet de modifier le nom du joueur courant
	/// @ param[in] 
	///			int index : le numero du joueur courant (1 ou 2)
	///			char * nom : chaine de caracteres representant le nom du joueur
	/// @return bool 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool setNomJoueurCourant(char* nom, int index)
	{
		if ((index == 1) || (index == 2))
			FacadeModele::obtenirInstance()->setNomJoueurCourant(std::string (nom), index);
		else
			return false;
		return true;		
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) bool setScoreCourant(int score, int index)
	/// Author : Ali
	/// @brief : Cette fonction permet de modifier le score courant du joueur
	/// @ param[in] 
	///			int index : le numero du joueur courant (1 ou 2)
	///			int score : le score a attribuer
	/// @return bool  
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool setScoreCourant(int score, int index)
	{
		if ( (index == 1) || (index == 2) )
		{
			FacadeModele::obtenirInstance()->setScoreCourant(score, index);
			return true;
		}
		else
			return false;
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) int getScoreCourant(int index)
	/// Author : Ali
	/// @brief : Cette fonction permet de modifier le score courant du joueur
	/// @ param[in] 
	///			int index : le numero du joueur courant (1 ou 2)
	///			
	/// @return int  
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int getScoreCourant(int index)
	{
		if ( (index == 1) || (index == 2) )
			return FacadeModele::obtenirInstance()->getScoreCourant(index);
		else 
			return FacadeModele::obtenirInstance()->getScoreCourant(1);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 		__declspec(dllexport) void sauvegarderTouches();
	/// Author : Arthur
	/// Cette fonction permet de modifier et enregistrer les touches de
	/// déplacement du joueur 2
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl sauvegarderTouches(int haut, int droite, int bas, int gauche)
	{
		FacadeModele::obtenirInstance()->getConfigTouches()->enregistrerTouches(haut, droite, bas, gauche);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 		__declspec(dllexport) int[] obtenirTouches();
	/// Author : Arthur
	/// Cette fonction permet de charger les touches de
	/// déplacement du joueur 2
	///
	/// @return int[4] : [haut, droite, bas, gauche]
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl obtenirTouches(int *touches)
	{
		FacadeModele::obtenirInstance()->getConfigTouches()->obtenirTouches(touches);
	}
	////////////////////////////////////////////////////////////////////////
	/// A DEPLACER ICI:
	/// @fn 	__declspec(dllexport) void enregistrerOptionsJeu();
	/// Author : Arthur
	/// Cette fonction permet de modifier et enregistrer les options de jeu
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) OptionsJeu obtenirOptionsJeu();
	/// Author : Arthur
	/// Cette fonction permet d'obtenir les options de jeu
	///
	/// @return OptionsJeu : {nombre de buts, type de joueur}
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) struct OptionsJeu* __cdecl obtenirOptionsJeu()
	{
		return FacadeModele::obtenirInstance()->getConfigJeu()->getOptionsJeu();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) void obtenirListeProfils(int *noms)
	/// Author : Arthur
	/// Cette fonction permet d'obtenir une liste des noms des profils,
	///  enregistrée dans une chaine d'entier afin d'être transmise entre
	///  les parties c# et c++ du programme
	///
	/// @param[out] noms : chaine d'entier correspondant à la liste des
	///                      noms des profils
	///
	/// @return void
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl obtenirListeProfils(int *noms)
	{
		FacadeModele::obtenirInstance()->getConfigProfils()->getNoms(noms);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) double obtenirVitesseProfil(char *nom)
	/// Author : Arthur
	/// Cette fonction permet d'obtenir la vitesse d'un profil spécifié
	///
	/// @param[in] nom : nom du profil recherché
	///
	/// @return double : vitesse du profil spécifié
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl obtenirVitesseProfil(char *nom)
	{
		return FacadeModele::obtenirInstance()->getConfigProfils()->getVitesse((std::string) nom);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) double obtenirProbabiliteProfil(char *nom)
	/// Author : Arthur
	/// Cette fonction permet d'obtenir la probabilite d'un profil spécifié
	///
	/// @param[in] nom : nom du profil recherché
	///
	/// @return double : probabilite du profil spécifié
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl obtenirProbabiliteProfil(char *nom)
	{
		return FacadeModele::obtenirInstance()->getConfigProfils()->getProbabilite((std::string)nom);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) void supprimerProfil(char *nom)
	/// Author : Arthur
	/// Cette fonction permet de supprimer un profil spécifié
	///
	/// @param[in] nom : nom du profil à supprimer
	///
	/// @return void
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl supprimerProfil(char *nom)
	{
		FacadeModele::obtenirInstance()->getConfigProfils()->supprimerProfil(nom);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) int obtenirNombreProfils()
	/// Author : Arthur
	/// Cette fonction permet d'obtenir le nombre de profil
	///
	/// @return le nombre de profils
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreProfils()
	{
		return FacadeModele::obtenirInstance()->getConfigProfils()->getNombre();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) OptionsDebug obtenirListeProfils();
	/// Author : Arthur
	/// Cette fonction permet d'obtenir les options de debug
	///
	/// @return struct OptionsDebug
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) struct OptionsDebug* __cdecl obtenirOptionsDebug()
	{
		return FacadeModele::obtenirInstance()->getConfigDebug()->getOptionsDebug();
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) profilCourant(string nom, double vitesse, double probaDAgirPassivemnt)
	/// Author : ikram
	/// Cette fonction permet de envoyer le joueur courant 
	/// 
	///
	/// @return aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl  profilCourant(string nom, double vitesse_, double probaDAgirPassivemnt)
	{
		
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) debogConfig(bool debogageActif_, bool debogCollision_, bool debogVitesse_, bool eclairageActif_,bool effetVisuelActif_);
	/// Author : Arthur
	/// Cette fonction permet de envoyer les information sur la configuration de débogage.
	/// déplacement du joueur 2
	///
	/// @return aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl debogConfig(bool debogageActif_, bool debogCollision_, bool debogVitesse_, bool eclairageActif_, bool effetVisuelActif_)
	{
		///std::cout << "helloLuc\n";
		if (debogageActif_) {
			Debug::obtenirInstance().afficherCollision = debogCollision_;
			Debug::obtenirInstance().afficherVitesse = debogVitesse_;
			Debug::obtenirInstance().afficherLumieres = eclairageActif_;
			Debug::obtenirInstance().afficherAttraction = effetVisuelActif_;
		}
		else {
			Debug::obtenirInstance().afficherCollision = false;
			Debug::obtenirInstance().afficherVitesse = false;
			Debug::obtenirInstance().afficherLumieres = false;
			Debug::obtenirInstance().afficherAttraction = false;
		}

		FacadeModele::obtenirInstance()->getConfigDebug()->setOptionsDebug(debogageActif_, debogCollision_,
			debogVitesse_, eclairageActif_, effetVisuelActif_);

	}

	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) void __cdecl changerLumieresActives(bool jLumiereAmbiente, bool kLumiereDirectionnelle, bool jLumiereSpots)
	/// Author : Luc
	/// Cette fonction permet d'envoyer les changements d'activation des lumieres ambiantes.
	///
	/// @return aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changerLumieresActives(bool jLumiereAmbiente, bool kLumiereDirectionnelle, bool jLumiereSpots) {
		if (Debug::obtenirInstance().afficherLumieres) {
			std::string message = "lumiere";
			if (jLumiereAmbiente) {
				Debug::obtenirInstance().lumiereAmbiente = !Debug::obtenirInstance().lumiereAmbiente;
				message += " ambiente ";
				message += Debug::obtenirInstance().lumiereAmbiente ? "ouverte" : "fermee";

			}
			if (kLumiereDirectionnelle) {
				Debug::obtenirInstance().lumiereDirectionnelle = !Debug::obtenirInstance().lumiereDirectionnelle;
				message += " directionnele ";
				message += Debug::obtenirInstance().lumiereDirectionnelle ? "ouverte" : "fermee";
			}
			if (jLumiereSpots) {
				Debug::obtenirInstance().lumiereSpots = !Debug::obtenirInstance().lumiereSpots;
				message += "s des spots ";
				message += Debug::obtenirInstance().lumiereSpots ? "ouvertes" : "fermees";
			}
			Debug::obtenirInstance().afficher(message);
		}
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport) void __cdecl sauvegarderTypeButMax(int nbButMax, bool estHumain)
	/// Author : Luc
	/// Cette fonction permet d'enregistrer des infomation à propos d'un match
	///
	/// @return aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl sauvegarderTypeButMax(int nbButMax, bool estHumain)
	{
		FacadeModele::obtenirInstance()->getConfigJeu()->setOptionsJeu(nbButMax, estHumain);
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn __declspec(dllexport)  void __cdecl sauvegarderProfil(const char* nom, double vitesse, double proba)
	///
	/// Cette fonction permet d'enregistrer un profil
	///
	/// @return aucun
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl sauvegarderProfil(const char* nom, double vitesse, double proba)
	{
		std::string str(nom);
		
		std::cout <<"le nom est:  "<< nom <<"  son vitesse:  " << vitesse << "  proba: " << proba << std::endl;
		
		FacadeModele::obtenirInstance()->getConfigProfils()->setProfil(nom, vitesse, proba);
	}
	
	/// @fn __declspec(dllexport) void createTournoi(const char* nomZone, const int count, const char** nomsJoueurs, const bool* sontHumains, const char** nomProfils)
	/// @brief Permet de créer un tournoi
	/// @param nomZone : Nom de la zone de jeu
	/// @param count : Nombre de joueurs
	/// @param nomsJoueurs : Noms des joueurs
	/// @param sontHumains : Si les joueurs sont humains ou non
	/// @param nomProfils : Si le joueur est virtuel, le nom du profil
	__declspec(dllexport) void createTournoi(const char* nomZone, const int count, const char** nomsJoueurs, const bool* sontHumains, const char** nomProfils) {
		FacadeModele::obtenirInstance()->creerTournoi(nomZone, count, nomsJoueurs, sontHumains, nomProfils);
	}

	/// @fn __declspec(dllexport) void loadTournoi(const char* nomZone, const int count, const char** nomsJoueurs, const bool* sontHumains, const char** nomProfils)
	/// @brief Permet de charger la configuration d'un tournoi
	/// @param nomZone : Nom de la zone de jeu
	/// @param count : Nombre de joueurs
	/// @param nomsJoueurs : Noms des joueurs
	/// @param sontHumains : Si les joueurs sont humains ou non
	/// @param nomProfils : Si le joueur est virtuel, le nom du profil
	__declspec(dllexport) void loadTournoi(char* nomZone, int count, char* nomsJoueurs, bool* sontHumains, char* nomProfils) {
		FacadeModele::obtenirInstance()->loadTournoi(nomZone, count, nomsJoueurs, sontHumains, nomProfils);
	}

	/// @fn __declspec(dllexport) void taillesArbreTournoi(int &nbMatchups, int &tailleChaineArbre)
	/// @brief Permet d'obtenir la taille de l'arbre de tournoi
	/// @param[out] nbMatchups : Nombre de matchups dans l'arbre
	/// @param[out] tailleChaineArbre : Taille maximale à allouer pour le transport des noms des joueurs dans l'arbres
	///TODO: Remove, became unused
	__declspec(dllexport) void taillesArbreTournoi(int nbMatchups, int tailleChaineArbre) {
		std::vector<AdaptateurJoueur> participants = FacadeModele::obtenirInstance()->obtenirTournoi()->obtenirParticipants();
		nbMatchups = FacadeModele::obtenirInstance()->obtenirTournoi()->obtenirTailleArbre();

		int maxLength = 1; //Une chaîne doit minimalement contenir \0
		for (auto participant : participants) {
			// On calcule le \0 additionnel
			int len = participant.getNomJoueur().length() + 1;
			maxLength = (maxLength < len ? len : maxLength);
		}

		tailleChaineArbre = maxLength * nbMatchups;
	}
	
	/// @fn __declspec(dllexport) int nombreMatchupsTournoi()
	/// @brief Permet d'obtenir le nombre de matchups dans le tournoi
	/// @return Le nombre de matchups dans le tournoi
	__declspec(dllexport) int nombreMatchupsTournoi() {
		return FacadeModele::obtenirInstance()->obtenirTournoi()->obtenirTailleArbre();
	}


	/// @fn __declspec(dllexport) int plusLongNomTournoi()
	/// @brief Permet d'obtenir la longeur du plus long nom du tournoi
	/// @return La longeur du plus long nom du tournoi
	__declspec(dllexport) int plusLongNomTournoi() {
		return FacadeModele::obtenirInstance()->obtenirTournoi()->obtenirTailleArbre();
	}

	/// @fn __declspec(dllexport) int loadArbreTournoi(char* nomsJoueurs, int* scores)
	/// @brief Permet d'obtenir l'arbre de tournoi
	/// @param[out] nomsJoueurs : Noms des joueurs
	/// @param[out] scores : Scores associés avec les joueurs
	/// @return Le nombre de participants dans l'arbre
	/// La case 0 représente le gagnant du tournoi. 1 et 2 la finale et ainsi de suite
	__declspec(dllexport) int loadArbreTournoi(char* nomsJoueurs, int* scores) {
		auto arbre = FacadeModele::obtenirInstance()->obtenirTournoi()->obtenirMatchups();
		int iNJLen = 0; //Itérateur sur les noms de joueurs
		int i = 0;
		for (auto scoreEtNomJoueur : arbre) {
			scores[i++] = scoreEtNomJoueur.second;
			int j; std::string nom = scoreEtNomJoueur.first.getNomJoueur();
			for (j = 0; j < nom.length(); j++, iNJLen++)
				nomsJoueurs[iNJLen] = nom[j];
			nomsJoueurs[iNJLen++] = '\0';
		}

		return FacadeModele::obtenirInstance()->obtenirTournoi()->obtenirParticipants().size();
	}

	/// @fn __declspec(dllexport) void preparerProchainMatchTournoi()
	/// @brief Permet de mettre en place les joueurs virtuels pour le match
	__declspec(dllexport) void preparerProchainMatchTournoi() {
		// On considère que le second joueur est le seul à pouvoir être virtuel
		std::pair<AdaptateurJoueur,AdaptateurJoueur> tournoi = FacadeModele::obtenirInstance()->obtenirTournoi()->obtenirProchainMatchup();
		if (tournoi.first.estHumain()) {
			FacadeModele::obtenirInstance()->setjoueurVirtuel(tournoi.second.estHumain());
			FacadeModele::obtenirInstance()->setVitesseVirtuel(tournoi.second.getProfil().getVitesse());
			FacadeModele::obtenirInstance()->setProbabiliteVirtuel(tournoi.second.getProfil().getProbabilite());
		} else {
			FacadeModele::obtenirInstance()->setjoueurVirtuel(tournoi.first.estHumain());
			FacadeModele::obtenirInstance()->setVitesseVirtuel(tournoi.first.getProfil().getVitesse());
			FacadeModele::obtenirInstance()->setProbabiliteVirtuel(tournoi.first.getProfil().getProbabilite());
		}
	}

	/// @fn __declspec(dllexport) bool gagnerMatchVirtuelsTournoi()
	/// @brief Permet de faire gagner un des joueurs virtuels par défaut si deux joueurs virtuels sont assignés
	/// @return Si un match était formé par deux joueurs virtuels
	__declspec(dllexport) bool gagnerMatchVirtuelsTournoi()	{
		// On considère que le second joueur est le seul à pouvoir être virtuel
		std::pair<AdaptateurJoueur, AdaptateurJoueur> tournoi = FacadeModele::obtenirInstance()->obtenirTournoi()->obtenirProchainMatchup();
		if (!tournoi.first.estHumain() && !tournoi.second.estHumain()) {
			ConfigJeu *cfg = FacadeModele::obtenirInstance()->getConfigJeu();
			int score1 = utilitaire::genererScore(cfg->getNombreDeButs());
			int score2 = utilitaire::genererScore(cfg->getNombreDeButs());
			if (score1 > score2) {
				FacadeModele::obtenirInstance()->obtenirTournoi()->affecterScoreProchainMatchup(cfg->getNombreDeButs(), score2);
			} else {
				if (score1 == cfg->getNombreDeButs())
					score1--;
				FacadeModele::obtenirInstance()->obtenirTournoi()->affecterScoreProchainMatchup(score1, cfg->getNombreDeButs());
			}
			return true;
		} else {
			return false;
		}
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 		__declspec(dllexport) void __cdecl jouerSonModeJeu(bool mode)
	/// Author : wajdi
	/// Cette fonction permet de jouer la musique de fond
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl jouerSonModeJeu(bool mode)
	{
		FacadeModele::obtenirInstance()->jouerSonModeJeu(mode);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn void mettrePauseMusique()
	/// Author : wajdi
	/// Cette fonction permet de jouer la musique de fond
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl mettrePauseMusique(bool pause)
	{
		FacadeModele::obtenirInstance()->MettrePauseSonModeJeu(pause);
	}
}

