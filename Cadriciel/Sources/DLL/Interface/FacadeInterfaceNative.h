////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#ifndef __FACADE_INTERFACE_NATIVE_H__
#define __FACADE_INTERFACE_NATIVE_H__

#include <string.h>
#include <iostream>


using namespace std;

extern "C" {

	__declspec(dllexport) void initialiserOpenGL(int * handle);
	__declspec(dllexport) void libererOpenGL();
	__declspec(dllexport) void dessinerOpenGL();
	__declspec(dllexport) void redimensionnerFenetre(int largeur, int hauteur);
	__declspec(dllexport) void animer(double temps);
	__declspec(dllexport) void zoomIn();
	__declspec(dllexport) void zoomOut();
	__declspec(dllexport) int obtenirAffichagesParSeconde();
	__declspec(dllexport) bool executerTests();
	
	
	
	__declspec(dllexport) void ajouterPortail(int x1, int y1);
	//__declspec(dllexport) void escEnfonce(bool esc);
	__declspec(dllexport) void ajouterPortailDeux(int x2, int y2);



	//Afficher les positions d'un objet 
	__declspec(dllexport) double getPosX();
	__declspec(dllexport) double getPosY();


	//supprimer un objet de la table
	__declspec(dllexport) void supprimerObjet();




	//Click
	__declspec(dllexport) void clickStart(int x, int y);
	__declspec(dllexport) bool clickCurrent(int x, int y);
	__declspec(dllexport) void clickEnd(int x, int y);
	__declspec(dllexport) void etatDelaSouris(int etat);
	__declspec(dllexport) bool positionSouris(int x, int y);

	__declspec(dllexport) void rightClick(bool presse);
	//touche control
	__declspec(dllexport) void toucheControl(bool presse);
	//touche alt
	__declspec(dllexport) void toucheAlt(bool presse);
	//touche escape
	__declspec(dllexport) void escEnfonce();


	//Deplacer un objet avec la boite de configuration
	__declspec(dllexport) void configurerObjet(double x, double y,double angle, double scale);
	
	// fonction bidon test
	__declspec(dllexport) void test();
	// fonctions de test pour les noeuds de controle
	__declspec(dllexport) void deplacerPointHaut(int index);

	//verifier le nombre d'objet sur la table
	__declspec(dllexport) int nombreObjetSelectionne();

	//obtenir l'Angle d'un objet
	__declspec(dllexport) double getAngle();

	//verifier le scale d'un objet 
	__declspec(dllexport) double getScale();


	// Methode DeplacerXY de la camera, pour les touches de directions
	__declspec(dllexport) void deplacerVueXY(double deplacementX, double deplacementY);

	/// Permet de changer les coefficients de la table de jeu
	__declspec(dllexport) void setCoefficient(double friction, double rebond, double acceleration);
	/// Permet d'obtenir le coefficient de friction
	__declspec(dllexport) double getCoefficientFriction();
	/// Permet d'obtenir le coefficient de rebond
	__declspec(dllexport) double getCoefficientRebond();
	/// Permet d'obtenir le coefficient d'accélération
	__declspec(dllexport) double getCoefficientAcceleration();
	// Methode pour sauvegarder la zone de jeu
	__declspec(dllexport) void enregistrerZoneJeu(char *fichierZoneJeu);

	// Methode pour charger la zone de jeu
	__declspec(dllexport) void chargerZoneJeu(char *fichierZoneJeu);

	__declspec(dllexport) bool objetEstDansLaTable();


}
#endif // __FACADE_INTERFACE_NATIVE_H__
