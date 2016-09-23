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
	tracerTable(couleurTable_, couleurFrontiere_,couleurControle_);
	//// Révolution autour du centre.
	//auto modele = glm::rotate(transformationRelative_, angleRotation_, glm::vec3(0, 0, 1));
	
	////// Affichage du modèle.
	//vbo_->dessiner(vueProjection* modele);
	//

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::animer(float temps)
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
/// @fn void NoeudTable::tracerPointControle(glm::vec3 point, glm::vec4 couleur) 
///
/// @param[in] point : Le point de controle a afficher
///			   couleur : la couleur du point de controle
/// Cette fonction trace un carre autour du point de controle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerPointControle(glm::vec3 point, glm::vec4 couleur)
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerTable(glm::vec4 couleurTable, glm::vec4 couleurControle)
///
/// @param[in] couleurTable : La couleur de la Table
///			   couleurControle : la couleur des points de controle
/// Cette fonction trace la Table et la zone du jeu
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerTable(glm::vec4 couleurTable, glm::vec4 couleurFrontiere, glm::vec4 couleurControle) const
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

	/*glTranslatef(-.5,-.5,0);
	glScaled(1.25, 1.25, 1.25);*/

	// deactiver les textures (la table ne prend plus la texture des autres noeuds)
	glDisable(GL_TEXTURE_2D); 
	// desactiver le test de profondeur
	glDisable(GL_DEPTH_TEST);

	// activer l'anticrenelage
	glEnable(GL_MULTISAMPLE);
	
	// tracer la frontiere	
#define p0 pointControle_[0][0], pointControle_[0][1], pointControle_[0][2]
#define p1 pointControle_[1][0], pointControle_[1][1], pointControle_[1][2]
#define p2 pointControle_[2][0], pointControle_[2][1], pointControle_[2][2]
#define p3 pointControle_[3][0], pointControle_[3][1], pointControle_[3][2]
#define p4 pointControle_[4][0], pointControle_[4][1], pointControle_[4][2]
#define p5 pointControle_[5][0], pointControle_[5][1], pointControle_[5][2]
#define p6 pointControle_[6][0], pointControle_[6][1], pointControle_[6][2]
#define p7 pointControle_[7][0], pointControle_[7][1], pointControle_[7][2]
	/*
	p0----------p2----------p4
	|						 |
	|						 |
	p6						p7
	|						 |
	|						 |
	p1----------p3----------p5
	*/

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

	glBegin(GL_QUADS);
	{	
		glColor4f(couleurFrontiere[0], couleurFrontiere[1], couleurFrontiere[2], couleurFrontiere[3]);
		glVertex3f(p0);
		glVertex3f(p1);
		glVertex3f(p5);
		glVertex3f(p4);		
	}
	glEnd();
	
#undef p0
#undef p1
#undef p2
#undef p3
#undef p4
#undef p5
#undef p6
#undef p7

	//tracer la table
#define delta 0.05
	glBegin(GL_QUAD_STRIP);
	{
		glColor4f(couleurTable[0], couleurTable[1], couleurTable[2], couleurTable[3]);
		glVertex3f(GLfloat(pointControle_[0][0] + delta), GLfloat(pointControle_[0][1] - delta), GLfloat(pointControle_[0][2]) );
		glVertex3f(GLfloat(pointControle_[1][0] + delta), GLfloat(pointControle_[1][1] + delta), GLfloat(pointControle_[1][2]) );
		glVertex3f(GLfloat(pointControle_[2][0]), GLfloat(pointControle_[2][1] - delta), GLfloat(pointControle_[2][2]) );
		glVertex3f(GLfloat(pointControle_[3][0]), GLfloat(pointControle_[3][1] + delta), GLfloat(pointControle_[3][2]) );
		glVertex3f(GLfloat(pointControle_[4][0] - delta), GLfloat(pointControle_[4][1] - delta), GLfloat(pointControle_[4][2]) );
		glVertex3f(GLfloat(pointControle_[5][0] - delta), GLfloat(pointControle_[5][1] + delta), GLfloat(pointControle_[5][2]) );
	}
	glEnd();
	// tracer la ligne du milieu 
	glLineWidth(5.);
	glBegin(GL_LINES);
	{
		glColor4f(1., 0., 0., 1.);
		glVertex3f(GLfloat(pointControle_[2][0]), GLfloat(pointControle_[2][1] - delta), GLfloat(pointControle_[2][2]));
		glVertex3f(GLfloat(pointControle_[3][0]), GLfloat(pointControle_[3][1] + delta), GLfloat(pointControle_[3][2]));
	}
	glEnd();
#undef delta
	// tracer un cercle au milieu du terrain
	DrawCircle(float(0),float(0),float(.2),100);
	 //Activer le test de profondeur
	glEnable(GL_DEPTH_TEST);
	 //Desactiver l'anticrenelage
	glDisable(GL_MULTISAMPLE);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerMurs()
///
/// @param[in] 
/// Cette fonction trace les murs autour de la table
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerMurs()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::DrawCircle(float cx, float cy, float r, int num_segments)
///
/// @param[in] 
/// Cette fonction trace un cercle de centre C (cx,cy) et de rayon r
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::DrawCircle(float cx, float cy, float r, int num_segments) const
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	}
	glEnd();
}