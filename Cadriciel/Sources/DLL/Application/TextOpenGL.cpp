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

bool TextOpenGL::initialiser()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		fprintf(stderr, "Could not init freetype library\n");
		return false;
	}
	FT_Face face;

	if (FT_New_Face(ft, "../../../../Commun/Externe/calibrii.ttf", 0, &face))
	{
		fprintf(stderr, "Could not open font\n");
		return false;
	}


}
