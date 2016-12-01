///////////////////////////////////////////////////////////////////////////////
/// @file TextOpenGL.h
/// @author Ali
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "TextOpenGL.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"
//#include "CompteurAffichage.h"

#include "../ArbreRenduINF2990.h"
#include "GL/glew.h"
#include <string>
// FTGL library
#include "../../../Commun/Externe/FTGL/include/FTGL/ftgl.h"


// Freetype Library
//#include "../../../Commun/Externe/FreeType/include/ft2build.h"
//#include FT_FREETYPE_H


////////////////////////////////////////////////////////////////////////
///
/// @fn TextOpenGL::TextOpenGL()
/// @brief : constructeur par default
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
TextOpenGL::TextOpenGL() { }
////////////////////////////////////////////////////////////////////////
///
/// @fn TextOpenGL::~TextOpenGL()
/// @brief : destructeur
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
TextOpenGL::~TextOpenGL()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool TextOpenGL::initialiserFTGL()
/// @brief : initialisation de la librairy FTGL
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool TextOpenGL::initialiserFTGL()
{
	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TextOpenGL::afficherChrono()
/// @brief : afficher le chronometre en FTGL  eh format 00:00:00
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void TextOpenGL::afficherChrono()
{
	auto facade = FacadeModele::obtenirInstance();

	glm::vec2 WH = facade->obtenirVue()->obtenirProjection().obtenirDimensionCloture();
	float W = WH.x;
	float H = WH.y;
	afficherTextFTGL(facade->getChrono(), FTPoint(W / 2, H - H / 20, 0), 20);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TextOpenGL::afficher()
/// @brief : afficher un texte avec FTGL 
/// affiche les noms des joueurs, le score et le temps ecoule'
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void TextOpenGL::afficher()
{	
	auto facade = FacadeModele::obtenirInstance();

	glm::vec2 WH = facade->obtenirVue()->obtenirProjection().obtenirDimensionCloture();
	float W = WH.x;
	float H = WH.y;

	//Player 2
	//Name
	afficherTextFTGL(facade->getNomJoueurCourant(2), FTPoint(50, 10, 0), 30, 4);
	//Score
	afficherTextFTGL(std::to_string(facade->getScoreCourant(2)), FTPoint(75, 50, 0), 30, 4);
	//Player 1
	//Name
	afficherTextFTGL(facade->getNomJoueurCourant(1), FTPoint(W - 150, 10, 0), 30, 4);
	//Score
	afficherTextFTGL(std::to_string(facade->getScoreCourant(1)), FTPoint(W - 125, 50, 0), 30, 4);
	
	// Time
	afficherTextFTGL(facade->getChrono(), FTPoint(W/20, H - H/10, 0), 40);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void TextOpenGL::afficherTextFTGL(std::string Text, FTPoint position, int FontSize)
/// @Author : Ali
/// @brief : permet d'afficher un text en FTGL a partir d'une position
/// @param[in] : std::string Text : le text a afficher
///				 FTPoint position : la position a afficher
///				 int FontSize : la taille du texte affiche'
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool TextOpenGL::afficherTextFTGL(std::string Text, FTPoint position, int FontSize)
{
	// Create a pixmap font from a TrueType file.
	FTGLPixmapFont	font("media/calibrii.ttf");
	//FTGLTextureFont  font("media/calibrii.ttf");
	
	//if something goes wrong like can't find the font file
	if (font.Error())
	{
		std::cout << "Font pas trouve'" << std::endl;
		return false;
	}
	char * chaine = new char[Text.size() + 1];
	std::copy(Text.begin(), Text.end(), chaine);
	chaine[Text.size()] = '\0'; // always add a '\0' if you want to convert from string to  char*
	

	font.FaceSize(FontSize);

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	// color doesn't work for now
	//glColor3f(1.0, 0., 0.);
	
	
	glPixelTransferf(GL_RED_BIAS, 1);
	glPixelTransferf(GL_GREEN_BIAS, 1);
	glPixelTransferf(GL_BLUE_BIAS, 1);

	font.Render(chaine, -1, position);
	
	glPopAttrib();
	delete[] chaine;
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void TextOpenGL::afficherTextFTGL(std::string Text, FTPoint position, int FontSize, int Red, int Green, int Blue)
/// @Author : Ali
/// @brief : permet d'afficher un text en FTGL a partir d'une position avec couleur
/// @param[in] : std::string Text : le text a afficher
///				 FTPoint position : la position a afficher
///				 int FontSize : la taille du texte affiche'
///				 float Red, Green, Blue : couleur RGB
///				 
/// @return bool
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TextOpenGL::afficherTextFTGL(std::string Text, FTPoint position, int FontSize,float Red, float Green, float Blue)
{
	// Create a pixmap font from a TrueType file.
	FTGLPixmapFont	font("media/calibrii.ttf");
	//FTGLTextureFont  font("media/calibrii.ttf");

	//if something goes wrong like can't find the font file
	if (font.Error())
	{
		std::cout << "Font pas trouve'" << std::endl;
		return false;
	}
	char * chaine = new char[Text.size() + 1];
	std::copy(Text.begin(), Text.end(), chaine);
	chaine[Text.size()] = '\0'; // always add a '\0' if you want to convert from string to  char*


	font.FaceSize(FontSize);

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	
	glPixelTransferf(GL_RED_BIAS, Red);
	glPixelTransferf(GL_GREEN_BIAS, Green);
	glPixelTransferf(GL_BLUE_BIAS, Blue);

	font.Render(chaine, -1, position);

	glPopAttrib();
	delete[] chaine;
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void TextOpenGL::afficherTextFTGL(std::string Text, FTPoint position,int FontSize, int nombreShadow)
/// @Author : Ali
/// @brief : permet d'afficher un text en FTGL a partir d'une position en blanc avec ombrage noir
/// @param[in] : std::string Text : le text a afficher
///				 FTPoint position : la position a afficher
///				 int FontSize : la taille du texte affiche'
///				 int shadow : epaisseur du shadow ex: 5 va afficher le text 5 fois en noir et 1 fois en blanc
///				 
/// @return bool
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TextOpenGL::afficherTextFTGL(std::string Text, FTPoint position, int FontSize, int shadow)
{
	// Create a pixmap font from a TrueType file.
	FTGLPixmapFont	font("media/calibrii.ttf");
	//FTGLTextureFont  font("media/calibrii.ttf");

	//if something goes wrong like can't find the font file
	if (font.Error())
	{
		std::cout << "Font pas trouve'" << std::endl;
		return false;
	}
	char * chaine = new char[Text.size() + 1];
	std::copy(Text.begin(), Text.end(), chaine);
	chaine[Text.size()] = '\0'; // always add a '\0' if you want to convert from string to  char*


	font.FaceSize(FontSize);

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// shadow
	glPixelTransferf(GL_RED_BIAS, -1);
	glPixelTransferf(GL_GREEN_BIAS, -1);
	glPixelTransferf(GL_BLUE_BIAS, -1);

	for (int i = 1; i <= shadow ; ++i)
		font.Render(chaine, -1, FTPoint (position.X() - i, position.Y() - i, position.Z() ) );
	
	//White Text
	glPixelTransferf(GL_RED_BIAS, 1);
	glPixelTransferf(GL_GREEN_BIAS, 1);
	glPixelTransferf(GL_BLUE_BIAS, 1);

	font.Render(chaine, -1, position);

	glPopAttrib();
	delete[] chaine;
	return true;
}