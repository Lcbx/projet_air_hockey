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

// FTGL library
#include "../../../Commun/Externe/FTGL/include/FTGL/ftgl.h"
// Freetype Library
#include "../../../Commun/Externe/FreeType/include/ft2build.h"
#include FT_FREETYPE_H


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
/// @fn bool TextOpenGL::initialiserFreeType()
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
/// @fn void TextOpenGL::test()
/// @brief : initialisation de la librairy FreeType
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool TextOpenGL::test()
{
	// Create a pixmap font from a TrueType file.
	FTGLPixmapFont font("media/calibrii.ttf");

	// If something went wrong, bail out.
	if (font.Error())
	{
		std::cout << "Font pas trouve'" << std::endl;
		return false;
	}

	FTPoint point1 = {10,10,0};
	FTPoint point2 = { 20,20,0 };
	font.FaceSize(72);
	font.BBox("Hello!", -1, point1, point2);
	font.Render("Hello World!");

	//BBox("Hello!",10,10,0,20,20,0);
	// Set the font size and render a small text.
	
	//font.Render("Hello World!");
	return true;

}