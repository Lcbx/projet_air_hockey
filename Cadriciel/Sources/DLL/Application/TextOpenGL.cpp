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
/// @fn bool TextOpenGL::initialiserFreeType()
/// @brief : initialisation de la librairy FreeType
/// @return bool
///
////////////////////////////////////////////////////////////////////////

bool TextOpenGL::initialiserFreeType()
{
	FT_Library ft;
	//if (FT_Init_FreeType(&ft))
	//{
	//	fprintf(stderr, "Could not init freetype library\n");
	//	return false;
	//}
	//FT_Face face;

	//if (FT_New_Face(ft, "../../../../Commun/Externe/calibrii.ttf", 0, &face))
	//{
	//	fprintf(stderr, "Could not open font\n");
	//	return false;
	//}

	return true;
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
/// @fn bool TextOpenGL::afficher()
/// @brief : afficher un texte avec FTGL
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool TextOpenGL::afficher()
{	
	auto facade = FacadeModele::obtenirInstance();

	// Create a pixmap font from a TrueType file.
	FTGLPixmapFont font("media/calibrii.ttf");
	FTGLPixmapFont font2("media/calibrii.ttf");
	// If something went wrong, bail out.
	if (font.Error())
	{
		std::cout << "Font pas trouve'" << std::endl;
		return false;
	}

	
	glm::vec3 positionTable = facade->obtenirArbreRenduINF2990()->getTable()->obtenirPositionRelative();
	FTPoint positionDepart (positionTable.x, positionTable.y, positionTable.z);
	FTPoint positionFin  (positionTable.x + 10, positionTable.y + 10, positionTable.z);
	
	std::string nomJoueur1, nomJoueur2, score1, score2;

	nomJoueur1.assign(facade->getNomJoueurCourant(1));
	nomJoueur2.assign(facade->getNomJoueurCourant(2));

	std::cout << nomJoueur1 << std::endl;

	char * nom1 = new char[nomJoueur1.size() + 1];
	std::copy(nomJoueur1.begin(), nomJoueur1.end(), nom1);
	nom1[nomJoueur1.size()] = '\0'; // don't forget the terminating 0

	char * nom2 = new char[nomJoueur2.size() + 1];
	std::copy(nomJoueur2.begin(), nomJoueur2.end(), nom2);
	nom2[nomJoueur2.size()] = '\0'; // don't forget the terminating 0

	//std::cout << nom1 << std::endl << nom2 << std::endl;
		
	////glPixelTransferf(GL_RED_BIAS, 1);
	////glPixelTransferf(GL_GREEN_BIAS, 0 - 1);
	////glPixelTransferf(GL_BLUE_BIAS, 0 - 1);


	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glColor4f(1, 0, 0, 1);
	font.FaceSize(20);
	//font.Render("score1", -1, FTPoint(positionTable.x + 400, 500, 0));
	//font.Render("score 2", -1, FTPoint(positionTable.x + 200, 500, 0));
	font.Render(nom1, -1, FTPoint(10,10, 0));
	font.Render(nom2, -1, FTPoint(100 +300, 10, 0));

	delete[] nom1;
	delete[] nom2;
	glPopAttrib();

	return true;

}

