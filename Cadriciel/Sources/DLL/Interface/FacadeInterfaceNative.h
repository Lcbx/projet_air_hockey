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
	__declspec(dllexport) void ajouterBonus(int x, int y);
	
	
	
	__declspec(dllexport) void ajouterPortail(int x1, int y1);
	__declspec(dllexport) void ajouterPortailDeux(int x2, int y2);


	__declspec(dllexport) void ajouterMuret(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void ajouterMuretFantome(int corXin, int corYin, int corX, int corY);



	//Click
	__declspec(dllexport) void clickStart(int x, int y);
	__declspec(dllexport) void clickCurrent(int x, int y);
	__declspec(dllexport) void clickEnd(int x, int y);
	__declspec(dllexport) void etatDelaSouris(int etat);
	__declspec(dllexport) void positionSouris(int x, int y);
	//touche control
	__declspec(dllexport) void toucheControl(bool presse);
	//touche escape
	__declspec(dllexport) void escEnfonce();
}
#endif // __FACADE_INTERFACE_NATIVE_H__
