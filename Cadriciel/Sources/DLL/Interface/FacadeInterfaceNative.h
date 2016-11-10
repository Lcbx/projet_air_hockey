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
	
	// Les fonction qui déplace l'objet vers la gauche, vers la droite, vers le bas et vers le haut
	__declspec(dllexport) void deplacerMaillet(int toucheDeplacementAGauche_, int toucheDeplacementADroite_, int toucheDeplacementEnHaut_, int toucheDeplacementEnBas_);
	__declspec(dllexport) void touches(int toucheDeplacementAGauche_, int toucheDeplacementADroite_, int toucheDeplacementEnHaut_, int toucheDeplacementEnBas_);
	
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

	// Methode pour modifier et enregistrer les touches du joueur 2.
	__declspec(dllexport) void sauvegarderTouches(int haut, int droite, int bas, int gauche);
	// Methode pour obtenir les touches du joueur 2.
	__declspec(dllexport) void obtenirTouches(int *touches);

	// Methode pour modifier et enregistrer les options de jeu
	__declspec(dllexport) void sauvegarderTypeButMax(int nbButMax, bool estVirtuel);
	// Methode pour obtenir les options de jeu
	__declspec(dllexport) struct OptionsJeu* obtenirOptionsJeu();

	__declspec(dllexport) bool objetEstDansLaTable();

	///permet d'initialiser la scene lorsqu'on clic sur nouveau
	__declspec(dllexport) void initialiserScene();


	///ajouter maillets et rondelle a la scene edition
	__declspec(dllexport) void ajouterMailletEtRondelle();

	///ajouter maillets et rondelle a la scene edition
	__declspec(dllexport) void retirerMailletEtRondelle();

	///permert de deplacer le maillet avec les touches de clavier
	__declspec(dllexport) void deplacerMailletAvecClavier(double x, double y);

	///Re-initialiser la partie
	__declspec(dllexport) void reinitialiserPartieCourante();

	///deplacer le maillet du joueur 1 avec souris
	__declspec(dllexport) void deplacerMailletAvecSouris(double x, double y);

	/// Ali
	/// Joueur Virtuel
	__declspec(dllexport) void activerJoueurVirtuel(double vitesse, double probabilite);
	// activer joueur
	__declspec(dllexport) void setjoueurVirtuel(bool activer);
	__declspec(dllexport) bool getjoueurVirtuel();
	// vitesse
	__declspec(dllexport) void setVitesseVirtuel(double vitesse);
	__declspec(dllexport) double getVitesseVirtuel();
	// probabilite
	__declspec(dllexport) void setProbabiliteVirtuel(double probabilite);
	__declspec(dllexport) double getProbabiliteVirtuel();
	///activer ou deactiver le rayon d'attraction
	__declspec(dllexport) void activerRayonAttraction();
	__declspec(dllexport) void deactiverRayonAttraction();
	///afficher ou effacer les points de controle
	__declspec(dllexport) void afficherPointControle();
	__declspec(dllexport) void effacerPointControle();
	// savoir s'il ya un but droit ou gauche
	__declspec(dllexport) bool estButDroite();
	__declspec(dllexport) bool estButGauche();
	// si un joueur marque un but , on remet les 2 a false
	__declspec(dllexport) void setButDroite(bool etat);
	__declspec(dllexport) void setButGauche(bool etat);
	// set/get le nombre de but pour gagner la partie
	__declspec(dllexport) int getNombreButs();
	__declspec(dllexport) void setNombreButs(int nombre);
	// set/get partieRapide
	__declspec(dllexport) bool estPartieRapide();
	__declspec(dllexport) void setPartieRapide(bool activer);
	// activer/deactiver la rondelle - mettre en pause
	__declspec(dllexport) void activerRondelle();
	__declspec(dllexport) void deactiverRondelle();
	__declspec(dllexport) bool estEnPauseRondelle();
	/// Ali 
	__declspec(dllexport) void profilCourant(string nom, double vitesse_, double probaDAgirPassivemnt);
	__declspec(dllexport) void debogConfig(bool debogageActif_, bool debogCollision_, bool debogVitesse_, bool eclairageActif_, bool effetVisuelActif_);
	__declspec(dllexport) void changerLumieresActives(bool jLumiereAmbiente, bool kLumiereDirectionnelle, bool jLumiereSpots);

	__declspec(dllexport) void sauvegarderProfil (const char* nom, double vitesse, double proba);

	// Permet d'envoyer la des informations pour un tournoi
	__declspec(dllexport) void createTournoi(const char* nomZone, const int count, const char** nomsJoueurs, const bool* sontHumains, const char** nomProfils);
} 
#endif // __FACADE_INTERFACE_NATIVE_H__
