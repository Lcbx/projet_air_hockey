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
	/// Cette fonction initialise un contexte OpenGL dans la fen�tre
	/// identifi�e par le handle pass� en param�tre.  Cette fonction doit
	/// �tre la premi�re � �tre appel�e, car la cr�ation de l'objet du mod�le
	/// C++ s'attend � avoir un contexte OpenGL valide.
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
	/// Cette fonction lib�re le contexte OpenGL. Cette fonction doit �tre la
	/// derni�re � �tre appel�e, car elle lib�re �galement l'objet du mod�le
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();
		

		// D�sinitialisation de la fa�ade.  Le fait de le faire apr�s la
		// d�sinitialisation du contexte OpenGL aura pour cons�quence que la
		// lib�ration des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
		// meme chose avec souris
		Souris::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la sc�ne.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		// Affiche la sc�ne.
		FacadeModele::obtenirInstance()->afficher();

		// Temporaire: pour d�tecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit �tre appel�e lorsque la fen�tre est
	/// redimensionn�e afin d'ajuster les param�tres de la machine � �tats
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fen�tre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fen�tre.
	/// @param[in] hauteur : La nouvelle hauteur de la fen�tre.
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
	/// Cette fonction effectue les diff�rents calculs d'animations
	/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
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
	/// Cette fonction applique un zoom avant sur le pr�sent volume de vision.
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
	/// Cette fonction applique un zoom arri�re sur le pr�sent volume de vision.
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
	/// Cette fonction permet d'ex�cuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont r�ussi, 1 si au moins un test a �chou�
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
	/// entr�es dans la boite config
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
	/// @return Le nombre d'objets selectionn�es
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
	///    perpendiculaire � la direction regard�e
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
	/// Permet de changer les coefficients de la table � travers l'objet de transport des coefficients
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
	/// Permet d'obtenir le coefficient d'acc�l�ration
	///
	/// @return Le coefficient d'acc�l�ration de la table
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
	/// @fn 	__declspec(dllexport) bool setButDroite()
	/// Author : Ali
	/// Cette fonction permet de modifier la varriable butDroite_ 
	/// dans facade modele 
	/// on l'utilise lorsque un des 2 joueurs marque un but 
	///
	/// @return bool
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool setButDroite(bool etat)
	{
		FacadeModele::obtenirInstance()->setButDroite(etat);
		return etat;
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 	__declspec(dllexport) bool setButGauche()
	/// Author : Ali
	/// Cette fonction permet de modifier la varriable butGauche_ 
	/// dans facade modele 
	/// on l'utilise lorsque un des 2 joueurs marque un but 
	/// @return bool
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool setButGauche(bool etat)
	{
		 FacadeModele::obtenirInstance()->setButGauche(etat);
		 return etat;
	}
	////////////////////////////////////////////////////////////////////////
	/// @fn 		__declspec(dllexport) void sauvegarderTouches();
	/// Author : Arthur
	/// Cette fonction permet de modifier et enregistrer les touches de
	/// d�placement du joueur 2
	///
	/// @return rien
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl sauvegarderTouches(int haut, int droite, int bas, int gauche)
	{
		FacadeModele::obtenirInstance()->enregistrerTouches(haut, droite, bas, gauche);
	}

	////////////////////////////////////////////////////////////////////////
	/// @fn 		__declspec(dllexport) int[] obtenirTouches();
	/// Author : Arthur
	/// Cette fonction permet de charger les touches de
	/// d�placement du joueur 2
	///
	/// @return int[4] : [haut, droite, bas, gauche]
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl obtenirTouches(int *touches)
	{
		FacadeModele::obtenirInstance()->obtenirTouches(touches);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
