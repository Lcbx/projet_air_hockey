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
#include "CompteurAffichage.h"

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
/// affiche les noms des joueurs, le score et le temps ecoule'
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool TextOpenGL::afficher()
{	
	auto facade = FacadeModele::obtenirInstance();

	glm::vec2 WH = facade->obtenirVue()->obtenirProjection().obtenirDimensionCloture();
	float W = WH.x;
	float H = WH.y;

	//std::cout <<"W = "<<WH.x << "H = " << WH.y << std::endl;
		
	// Create a pixmap font from a TrueType file.
	FTGLPixmapFont	font("media/calibrii.ttf");
	//FTGLTextureFont  font("media/calibrii.ttf");
	// If something went wrong, bail out.
	if (font.Error())
	{
		std::cout << "Font pas trouve'" << std::endl;
		return false;
	}

	
	glm::vec3 positionTable = facade->obtenirArbreRenduINF2990()->getTable()->obtenirPositionRelative();
	FTPoint positionDepart (positionTable.x, positionTable.y, positionTable.z);
	FTPoint positionFin  (positionTable.x + 10, positionTable.y + 10, positionTable.z);
	
	//TODO -- create a method for that
	std::string nomJoueur1, nomJoueur2, scoreJoueur1, scoreJoueur2;

	nomJoueur1.assign(facade->getNomJoueurCourant(1));
	nomJoueur2.assign(facade->getNomJoueurCourant(2));
	scoreJoueur1.assign(std::to_string(facade->getScoreCourant(1)));
	scoreJoueur2.assign(std::to_string(facade->getScoreCourant(2)));

	char * nom1 = new char[nomJoueur1.size() + 1];
	std::copy(nomJoueur1.begin(), nomJoueur1.end(), nom1);
	nom1[nomJoueur1.size()] = '\0'; // don't forget the terminating 0

	char * nom2 = new char[nomJoueur2.size() + 1];
	std::copy(nomJoueur2.begin(), nomJoueur2.end(), nom2);
	nom2[nomJoueur2.size()] = '\0'; // don't forget the terminating 0

	char * score1 = new char[scoreJoueur1.size() + 1];
	std::copy(scoreJoueur1.begin(), scoreJoueur1.end(), score1);
	score1[scoreJoueur1.size()] = '\0'; // don't forget the terminating 0

	char * score2 = new char[scoreJoueur2.size() + 1];
	std::copy(scoreJoueur2.begin(), scoreJoueur2.end(), score2);
	score2[scoreJoueur2.size()] = '\0'; // don't forget the terminating 0

	
	// Taille du texte
	font.FaceSize(30);

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	////glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glColor3f(1.0, 0., 0.);

	// TODO 
	// 3) afficher le chronometre (temps ecoule' des le debt de la partie
	// bug
	// 1) changer le nom du joueur 2 a player2 quand on sort de mode partie rapide -> virtuel
	// 2) reset aussi le score affiche' en opengl qd on pese sur la touche espace


	// afficher les noms des joueurs	
	// joueur a gauche
	font.Render(nom2, -1, FTPoint(50, 10, 0));
	font.Render(score2, -1, FTPoint(75, 50, 0));
	// joeur a droite
	font.Render(nom1, -1, FTPoint(W-150, 10, 0));
	font.Render(score1, -1, FTPoint(W - 125, 50, 0));

	//TODO --  afficher temps
	//afficherChrono();

	glPopAttrib();

	// release memory
	delete[] nom1;
	delete[] nom2;
	delete[] score1;
	delete[] score2;

	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fnvoid TextOpenGL::afficherChrono()
/// @brief : afficher le temps ecoule' depuis le debut de la partie
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void TextOpenGL::afficherChrono()
{
	// compteur
	auto compteur = utilitaire::CompteurAffichage::obtenirInstance();
	//compteur->reinitialiser();
	compteur->signalerAffichage();
	// if
	std::cout << "Nombre affichage seconde = " << compteur->obtenirAffichagesSeconde() << std::endl;

}