///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudTable.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "Utilitaire.h"

#include <../Visiteur.h>
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::NoeudTable(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::NoeudTable(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	// positionner les points de control selon la position relative
	for (int i = 0 ; i <8; i++)
		for (int j = 0; j <3; j++)
			pointControle_[i][j] = obtenirPositionRelative().x + pointControle_[i][j];
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::~NoeudTable()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
//
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::~NoeudTable()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::afficherConcret() const
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::afficherConcret(const glm::mat4& vueProjection) const
{
	// tracer la table en opengl
	tracerTable(couleurTable_, couleurMurs_, couleurButs_);
	
	
	//// Révolution autour du centre.
	//auto modele = glm::rotate(transformationRelative_, angleRotation_, glm::vec3(0, 0, 1));
	////// Affichage du modèle.
	//vbo_->dessiner(vueProjection* modele);
	//

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::animer(float temps)
{

}

////////////////////////////////////////////////
/// @}
/// @}VISITEUR
////////////////////////////////////////////////

void NoeudTable::accepter(Visiteur* v)
{
	v->visiter(this);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerTable(glm::vec4 couleurTable, glm::vec4 couleurMurs, glm::vec4 couleurButs)
///
/// @param[in] couleurTable : La couleur de la Table
///			   couleurMurs : la couleur des murs autour de la table
///            couleurButs : la couleur des buts
/// Cette fonction trace la Table et la zone du jeu
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerTable(glm::vec4 couleurTable, glm::vec4 couleurMurs, glm::vec4 couleurButs) const
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0,// left
	//	1.0,   // right
	//	0.0,   // bottom
	//	1.0,   // top
	//	1.0,  // near
	//	-1.0);  // far
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 

	//quelques transformations bidons
	//glTranslatef(-.5,-.5,0);
	//glScaled(1.25, 1.25, 1.25);

	// deactiver les textures (la table ne prend plus la texture des autres noeuds)
	glDisable(GL_TEXTURE_2D); 
	// desactiver le test de profondeur
	glDisable(GL_DEPTH_TEST);
	// activer l'anticrenelage - aucun effet a l'instant
	glEnable(GL_MULTISAMPLE);
/////////////////////////////////////////////////////////////////////////////////////////////
// tracage de la table avec les vao et les vbo -- pas fini! (on laisse tomber a l'instant)
/////////////////////////////////////////////////////////////////////////////////////////////
	//GLuint vao;
	//GLuint vbo[2];
	//// Charger le modele 
	//// les sommets : 8 sommets * 3 coord.(x,y,z)
	///*GLfloat sommets[] = { p0,p1,p2,p3,p4,p5,p6,p7 }; */
	//GLfloat sommets[] = { -.8,0,0 , -.8,.4,0 , 0,.4,0 , .8,.4,0 , .8,0,0 , .8,-.4,0 , 0,-.4,0 , -.8,-.4,0  };
	//// la connectivité : 6 faces * 3 indices
	//GLuint connect[] = { 1,0,7, 3,2,1, 5,4,3, 5,6,7, 3,7,1, 3,7,5  }; 
	///*GLuint connect[] = {3,7,1};*/
	//GLfloat couleur[] = {1.,0.,0.};
	//// allouer les objets openGL
	//glGenVertexArrays(1,&vao);
	//glGenBuffers(3, vbo);
	////initialiser le vao
	//glBindVertexArray(vao);
	//// charger le vbo de sommets
	//glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(sommets), sommets, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);
	//// charger le VBO pour les couleurs
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(couleur), couleur, GL_STATIC_DRAW);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(3);
	//// charger le VBO pour la connectivité
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(connect), connect, GL_STATIC_DRAW);
	//glBindVertexArray(0);
	//// Défaire tous les liens
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindVertexArray(vao);         // sélectionner le second VAO
	//glDrawElements(GL_TRIANGLES, 6*3, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);              // désélectionner le VAO
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

#define p0 pointControle_[0].x, pointControle_[0].y, pointControle_[0].z
#define p1 pointControle_[1].x, pointControle_[1].y, pointControle_[1].z
#define p2 pointControle_[2].x, pointControle_[2].y, pointControle_[2].z
#define p3 pointControle_[3].x, pointControle_[3].y, pointControle_[3].z
#define p4 pointControle_[4].x, pointControle_[4].y, pointControle_[4].z
#define p5 pointControle_[5].x, pointControle_[5].y, pointControle_[5].z
#define p6 pointControle_[6].x, pointControle_[6].y, pointControle_[6].z
#define p7 pointControle_[7].x, pointControle_[7].y, pointControle_[7].z
// besoin pour tracage
#define p8 (pointControle_[6].x + pointControle_[7].x)/2, (pointControle_[2].y + pointControle_[3].y)/2,pointControle_[0].z

	/*
	p0----------p2----------p4
	|						 |
	|						 |
	p6			p8			p7
	|						 |
	|						 |
	p1----------p3----------p5
	*/
	// tracer la table (zone du jeur)
	glColor4f(couleurTable[0], couleurTable[1], couleurTable[2], couleurTable[3]);
	glBegin(GL_QUADS);
	{
		glVertex3f(p0);glVertex3f(p6);glVertex3f(p8);glVertex3f(p2);
		glVertex3f(p2);glVertex3f(p8);glVertex3f(p7);glVertex3f(p4);
		glVertex3f(p6);glVertex3f(p1);glVertex3f(p3);glVertex3f(p8);
		glVertex3f(p8);glVertex3f(p3);glVertex3f(p5);glVertex3f(p7);
	}
	glEnd();

//	// tracer murs 
//	glColor4f(couleurMurs[0], couleurMurs[1], couleurMurs[2], couleurMurs[3]);
//	glBegin(GL_QUADS);
//	{			
//		glVertex3f(p0);
//		glVertex3f(p1);
//		glVertex3f(p5);
//		glVertex3f(p4);		
//	}
//	glEnd();
//	
//#undef p0
//#undef p1
//#undef p2
//#undef p3
//#undef p4
//#undef p5
//#undef p6
//#undef p7
//
//	//tracer la table
//#define delta 0.05
//	glColor4f(couleurTable[0], couleurTable[1], couleurTable[2], couleurTable[3]);
//	glBegin(GL_QUAD_STRIP);
//	{
//		glVertex3f(GLfloat(pointControle_[0][0] + delta), GLfloat(pointControle_[0][1] - delta), GLfloat(pointControle_[0][2]) );
//		glVertex3f(GLfloat(pointControle_[1][0] + delta), GLfloat(pointControle_[1][1] + delta), GLfloat(pointControle_[1][2]) );
//		glVertex3f(GLfloat(pointControle_[2][0]), GLfloat(pointControle_[2][1] - delta), GLfloat(pointControle_[2][2]) );
//		glVertex3f(GLfloat(pointControle_[3][0]), GLfloat(pointControle_[3][1] + delta), GLfloat(pointControle_[3][2]) );
//		glVertex3f(GLfloat(pointControle_[4][0] - delta), GLfloat(pointControle_[4][1] - delta), GLfloat(pointControle_[4][2]) );
//		glVertex3f(GLfloat(pointControle_[5][0] - delta), GLfloat(pointControle_[5][1] + delta), GLfloat(pointControle_[5][2]) );
//	}
//	glEnd();
//	// tracer les lignes du terrain
//	glLineWidth(5.);
//	glColor4f(couleurLignes_[0], couleurLignes_[1], couleurLignes_[2], couleurLignes_[3]);
//	glBegin(GL_LINES);
//	{		
//		glVertex3f(GLfloat(pointControle_[2][0]), GLfloat(pointControle_[2][1] - delta), GLfloat(pointControle_[2][2]));
//		glVertex3f(GLfloat(pointControle_[3][0]), GLfloat(pointControle_[3][1] + delta), GLfloat(pointControle_[3][2]));
//	}
//	glEnd();
//#undef delta
//	// tracer un cercle au milieu du terrain
//	tracerCercle(float(0.),float(0.),float(.2),100);


	 //Activer le test de profondeur
	glEnable(GL_DEPTH_TEST);
	 //Desactiver l'anticrenelage
	glDisable(GL_MULTISAMPLE);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerMurs()
///
/// @param[in] : aucun
/// Cette fonction trace les murs autour de la table
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerMurs()
{
	// tracer murs 
	// probleme  gerer les jonctions lors du changement du placement des points de controle
	glColor4f(couleurMurs_.x, couleurMurs_.y, couleurMurs_.z, couleurMurs_.w);
	/*glBegin(GL_QUADS);
	{			
		glVertex3f(p0);
		glVertex3f(p1);
		glVertex3f(p5);
		glVertex3f(p4);		
	}
	glEnd();*/
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerButs(float longueur)
///
/// @param[in] 
/// longueur : la longueur des buts
/// Cette fonction trace les but avec une certaine longueur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerButs(float longueur)
{
	// trouvez l'equation des droites p6p0 et p6p1 pour le 1er but 

	// trouvez l'equation des droites p7p4 et p7p5 pour le 2eme but 

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerCercle(float cx, float cy, float r, int nb_segments)
///
/// @param[in] 
///			 cx : x du centre du cercle
///			 cy : y du centre du cercle
///			 r : rayon du cercle
///			nb_segments : nombre des segments utilises pour tracer le cercle
/// Cette fonction trace un cercle de centre C (cx,cy) et de rayon r
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerCercle(float cx, float cy, float r, int nb_segments) const
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < nb_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(nb_segments);//l'angle courant

		float x = r * cosf(theta);
		float y = r * sinf(theta);

		glVertex2f(x + cx, y + cy);

	}
	glEnd();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::getPointControle(int numero,glm::vec3 & pointControle)
///
/// Cette fonction permet d'obtenir les coordonnes d'un certain point de controle de la table
/// elle retourne true s'il a reussi , false sinon
/// @param[in] 
///		numero : le numero du point de controle
///		pointControle : la valeur du point de controle a recuperer
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::getPointControle(int numero, glm::vec3 & pointControle)
{
	if (numero < 0 || numero >7)
		return false;
	else {
		pointControle = pointControle_[numero];
		return true;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::setPointControle( glm::vec3 pointControle, int numero)
///
/// Cette fonction modifie les coordonnes d'un des 8 points de controle de la table
///
/// @param[in] temps : 
///			pointControle : le nouveau point de controle
///			numero : le numero du point de controle auquel on doit modifier sa valeur
///
/// @return bool.
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::setPointControle(int numero, glm::vec3 pointControle)
{
	if (numero < 0 || numero >7)
		return false;
	else {
		pointControle_[numero] = pointControle;
		return true;
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::setCouleurTable(glm::vec4 couleur)
///
/// Cette fonction permet de modifier la couleur de la zone du jeu (table)
///  @param[in] 
///			couleur : la nouvelle couleur de la table
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::setCouleurTable(glm::vec4 couleur)
{
	couleurTable_ = couleur;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::getCouleurTable(glm::vec4 & couleur)
///
/// Cette fonction permet d'obtenir la couleur courante de la table
///  @param[in] 
///		couleur : la couleur courante de la table
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::getCouleurTable(glm::vec4 & couleur)
{
	couleur = couleurTable_;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::setCouleurMurs(glm::vec4 couleur)
///
/// Cette fonction permet de modifier la couleur des murs autour de la table
///  @param[in] 
///			couleur : la nouvelle couleur des murs
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::setCouleurMurs(glm::vec4 couleur)
{
	couleurMurs_ = couleur;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::getCouleurMurs(glm::vec4 & couleur)
///
/// Cette fonction permet d'obtenir la couleur courante des murs
///  @param[in] 
///		couleur : la couleur courante des murs
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::getCouleurMurs(glm::vec4 & couleur)
{
	couleur = couleurMurs_;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::setCouleurButs(glm::vec4 couleur)
///
/// Cette fonction permet de modifier la couleur des buts
///  @param[in] 
///			couleur : la nouvelle couleur des buts
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::setCouleurButs(glm::vec4 couleur)
{
	couleurButs_ = couleur;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::getCouleurButs(glm::vec4 & couleur)
///
/// Cette fonction permet d'obtenir la couleur courante des buts
///  @param[in] 
///		couleur : la couleur courante des buts
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::getCouleurButs(glm::vec4 & couleur)
{
	couleur = couleurButs_;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::setCouleurLignes(glm::vec4 couleur)
///
/// Cette fonction permet de modifier la couleur des lignes du terrain
///  @param[in] 
///			couleur : la nouvelle couleur des lignes
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::setCouleurLignes(glm::vec4 couleur)
{
	couleurLignes_ = couleur;
	return true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::getCouleurLignes(glm::vec4 & couleur)
///
/// Cette fonction permet d'obtenir la couleur courante des lignes
///  @param[in] 
///		couleur : la couleur courante des lignes
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::getCouleurLignes(glm::vec4 & couleur)
{
	couleur = couleurLignes_;
	return true;
}
