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
	__declspec(dllexport) void __cdecl clickCurrent(int x, int y)
	{
		Souris::obtenirInstance()->currentClick(x, y);
	}
	__declspec(dllexport) void __cdecl clickEnd(int x, int y)
	{
		Souris::obtenirInstance()->endClick(x, y);
	}
	__declspec(dllexport) void __cdecl positionSouris(int x, int y)
	{
		Souris::obtenirInstance()->sourisPostition(x, y);
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


	__declspec(dllexport) void escEnfonce(bool escTouche) 
	{
		//prend un bool en param (touche esc est enfonce ou pas)
		FacadeModele::obtenirInstance()->supprimerPortail(escTouche);

	}


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
	/// @fn __declspec(dllexport) void __cdecl ajouterMuret()
	///
	/// Cette fonction ajoute le muret dans la table
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void ajouterMuret(int x1, int y1, int x2, int y2)
	{
		FacadeModele::obtenirInstance()->ajouterMuret(x1, y1, x2, y2);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ajouterMurFantome()
	///
	/// Cette fonction simule a quoi resemblera le mur si le deuxieme click est fait.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void __cdecl ajouterMuretFantome(int corXin, int corYin, int corX, int corY)
	{

		FacadeModele::obtenirInstance()->ajouterMurFantome(corXin, corYin, corX, corY);
	}


}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
