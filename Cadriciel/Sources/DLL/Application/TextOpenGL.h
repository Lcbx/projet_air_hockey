///////////////////////////////////////////////////////////////////////////////
/// @file TextOpenGL.h
/// @author Ali
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __TEXTOPENGL_H__
#define __TEXTOPENGL_H__

// FTGL library
#include "../../../Commun/Externe/FTGL/include/FTGL/ftgl.h"
#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class TextOpenGL
/// @brief Cette classe contient les informations et les methodes necessaires
/// pour l'affichage d'un texte en OpenGL
///
/// @autho Ali
/// @date 2016-11-17
///////////////////////////////////////////////////////////////////////////
class TextOpenGL {
public:
	
	/// Constructeur par défaut
	TextOpenGL();
	~TextOpenGL();
	bool initialiserFTGL();
	void afficher();
	bool afficherTextFTGL(std::string Text, FTPoint position, int FontSize);
	void afficherChrono();
	
private:
	// noms des joueurs
	// score 
	// temps
	
};
#endif
