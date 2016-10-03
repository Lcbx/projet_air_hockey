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
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::NoeudTable(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::~NoeudTable()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
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
///					transformer le mod�le � sa position voulue.
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::afficherConcret(const glm::mat4& vueProjection) const
{
	// tracer la table en opengl
	tracerTable();
	NoeudComposite::afficherConcret(vueProjection);
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
/// @fn void NoeudTable::tracerTable()
///
/// @param[in] Aucun.
///
/// Cette fonction trace la Table et la zone du jeu
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerTable() const
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0,// left
	//	1.0,   // right
	//	0.0,   // bottom
	//	1.0,   // top
	//	1.0,  // near
	//	-1.0);  // far
	

	glPushMatrix();
	glEnable(GL_NORMALIZE);
	// Affichage du mod�le.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// deactiver les textures (la table ne prend plus la texture des autres noeuds)
	glDisable(GL_TEXTURE_2D);
	// deactiver les lumieres
	glDisable(GL_LIGHTING);
	// desactiver le test de profondeur
	glDisable(GL_DEPTH_TEST);
	
	

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
#define p8x (pointControle_[6].x + pointControle_[7].x)/2
#define p8y (pointControle_[2].y + pointControle_[3].y)/2

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
	glColor4f(couleurTable_[0], couleurTable_[1], couleurTable_[2], couleurTable_[3]);
	glBegin(GL_QUADS);
	{
		glVertex3f(p0);glVertex3f(p6);glVertex3f(p8);glVertex3f(p2);
		glVertex3f(p2);glVertex3f(p8);glVertex3f(p7);glVertex3f(p4);
		glVertex3f(p6);glVertex3f(p1);glVertex3f(p3);glVertex3f(p8);
		glVertex3f(p8);glVertex3f(p3);glVertex3f(p5);glVertex3f(p7);
	}
	glEnd();

	// tracer les murs 
	tracerMurs();
	// tracer les buts 
	tracerButs();
	// tracer les lignes de decoration 
	// tracer le contour
	glColor4f(couleurContour_[0], couleurContour_[1], couleurContour_[2], couleurContour_[3]);
	glLineWidth(2.);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(p0);glVertex3f(p2);glVertex3f(p4);glVertex3f(p7);
		glVertex3f(p5);glVertex3f(p3);glVertex3f(p1);glVertex3f(p6);
	}
	glEnd();

	// tracer les lignes du terrain
	glLineWidth(5.);
	glColor4f(couleurLignes_[0], couleurLignes_[1], couleurLignes_[2], couleurLignes_[3]);
	glBegin(GL_LINES);
	{		
		glVertex3f(p2);glVertex3f(p3);
	}
	glEnd();
	// tracer un cercle au milieu du terrain
	glLineWidth(3.);
	glColor4f(1.,1.,0.,1.);
	double rayon = 0.2;
	double distance = abs( pointControle_[2].y - pointControle_[3].y ); 
	//double distance = sqrt( pow(1,2) + pow(1,2) );
	double coeff = 0.4;
	rayon = distance/2*coeff;
	//tracerCercle(double(pointControle_[8][0]),double(pointControle_[8][1]),rayon,100);
	tracerCercle(p8x,p8y, rayon, 100);
	

#undef p0
#undef p1
#undef p2
#undef p3
#undef p4
#undef p5
#undef p6
#undef p7
#undef p8
#undef p8x
#undef p8y


   //Activer le test de profondeur
	glEnable(GL_DEPTH_TEST);
	// activer le test de profondeur
	//glEnable(GL_TEXTURE_2D);
	glPopMatrix();	
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
void NoeudTable::tracerMurs() const
{
	// tracer murs
	glColor4f(couleurMurs_[0], couleurMurs_[1], couleurMurs_[2],couleurMurs_[3]);
	glBegin(GL_QUADS);
	{			
		// mur p0p6
		glVertex3f(pointControle_[0].x, pointControle_[0].y, pointControle_[0].z);
		glVertex3f(pointControle_[0].x - largeur_, pointControle_[0].y, pointControle_[0].z);
		glVertex3f(pointControle_[6].x - largeur_, pointControle_[6].y, pointControle_[6].z);
		glVertex3f(pointControle_[6].x, pointControle_[6].y, pointControle_[6].z);
		// mur p6p1
		glVertex3f(pointControle_[6].x, pointControle_[6].y, pointControle_[6].z);
		glVertex3f(pointControle_[6].x - largeur_, pointControle_[6].y, pointControle_[6].z);
		glVertex3f(pointControle_[1].x - largeur_, pointControle_[1].y, pointControle_[1].z);
		glVertex3f(pointControle_[1].x, pointControle_[1].y, pointControle_[1].z);
		// mur p0p2
		glVertex3f(pointControle_[2].x, pointControle_[2].y, pointControle_[2].z);
		glVertex3f(pointControle_[2].x, pointControle_[2].y + largeur_, pointControle_[2].z);
		glVertex3f(pointControle_[0].x, pointControle_[0].y + largeur_, pointControle_[0].z);
		glVertex3f(pointControle_[0].x, pointControle_[0].y, pointControle_[0].z);
		// mur p2p4
		glVertex3f(pointControle_[4].x, pointControle_[4].y, pointControle_[4].z);
		glVertex3f(pointControle_[4].x, pointControle_[4].y + largeur_, pointControle_[4].z);
		glVertex3f(pointControle_[2].x, pointControle_[2].y + largeur_, pointControle_[2].z);
		glVertex3f(pointControle_[2].x, pointControle_[2].y, pointControle_[2].z);
		// mur p4p7
		glVertex3f(pointControle_[4].x + +largeur_, pointControle_[4].y, pointControle_[4].z);
		glVertex3f(pointControle_[4].x , pointControle_[4].y, pointControle_[4].z);
		glVertex3f(pointControle_[7].x, pointControle_[7].y, pointControle_[7].z);
		glVertex3f(pointControle_[7].x + largeur_, pointControle_[7].y, pointControle_[7].z);
		// mur p7p5		
		glVertex3f(pointControle_[7].x + largeur_, pointControle_[7].y, pointControle_[7].z);
		glVertex3f(pointControle_[7].x, pointControle_[7].y, pointControle_[7].z);		
		glVertex3f(pointControle_[5].x, pointControle_[5].y, pointControle_[5].z);
		glVertex3f(pointControle_[5].x + largeur_, pointControle_[5].y, pointControle_[5].z);
		// mur p5p3
		glVertex3f(pointControle_[5].x, pointControle_[5].y - largeur_, pointControle_[5].z);
		glVertex3f(pointControle_[5].x, pointControle_[5].y, pointControle_[5].z);
		glVertex3f(pointControle_[3].x, pointControle_[3].y, pointControle_[3].z);
		glVertex3f(pointControle_[3].x, pointControle_[3].y - largeur_, pointControle_[3].z);
		// mur p3p1
		glVertex3f(pointControle_[3].x, pointControle_[3].y - largeur_, pointControle_[3].z);
		glVertex3f(pointControle_[3].x, pointControle_[3].y, pointControle_[3].z);
		glVertex3f(pointControle_[1].x, pointControle_[1].y, pointControle_[1].z);
		glVertex3f(pointControle_[1].x, pointControle_[1].y - largeur_, pointControle_[1].z);		
	}
	glEnd();
	
	
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudTable::calculPente(glm::vec3 P0, glm::vec3 P1)
///
/// @param[in] 
///		P0 : le premier point de la droite
///		P1 : le 2eme point de la droite
/// Cette fonction calcul la pente de la droite forme' par 2 points
///
/// @return double
///
////////////////////////////////////////////////////////////////////////
double NoeudTable::calculPente(glm::vec3 P0, glm::vec3 P1)
{
	if ((P0.x - P1.x) == 0)
		return (double)P0.x;
	else
		if ((P0.y - P1.y) == 0)
			return (double)P0.y;

		else
			return (double) (P0.y - P1.y) / (P0.x - P1.x);
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
void NoeudTable::tracerButs() const
{
	// tracez le 1er but
	//// pente de la droite p6p0
	//double a60 = (pointControle_[0].y - pointControle_[6].y) / (pointControle_[0].x - pointControle_[6].x);
	//double b60 = pointControle_[6].y - a60 * pointControle_[6].x;
	double longueurP6P0 = sqrt(pow((pointControle_[0].x - pointControle_[6].x),2)+pow(pointControle_[0].y - pointControle_[6].y,2));
	
	
	glColor4f(couleurButs_[0], couleurButs_[1], couleurButs_[2], couleurButs_[3]);
	glBegin(GL_QUADS);
	{	
		//1er but
		// 1er morceau
		glVertex3f(pointControle_[6].x, pointControle_[6].y, pointControle_[6].z);
		glVertex3f(pointControle_[6].x, pointControle_[6].y + longueurP6P0/4, pointControle_[6].z);
		glVertex3f(pointControle_[6].x - largeur_, pointControle_[6].y + longueurP6P0/4, pointControle_[6].z);
		glVertex3f(pointControle_[6].x - largeur_, pointControle_[6].y, pointControle_[6].z);
		// 2eme morceau
		glVertex3f(pointControle_[6].x, pointControle_[6].y, pointControle_[6].z);
		glVertex3f(pointControle_[6].x - largeur_, pointControle_[6].y, pointControle_[6].z);
		glVertex3f(pointControle_[6].x - largeur_, pointControle_[6].y - longueurP6P0/4, pointControle_[6].z);
		glVertex3f(pointControle_[6].x , pointControle_[6].y - longueurP6P0/4, pointControle_[6].z);
		
		//2eme but
		// 1ere morceau
		glVertex3f(pointControle_[7].x + largeur_, pointControle_[7].y, pointControle_[7].z);
		glVertex3f(pointControle_[7].x + largeur_, pointControle_[7].y + longueurP6P0 / 4, pointControle_[7].z);
		glVertex3f(pointControle_[7].x, pointControle_[7].y + longueurP6P0 / 4, pointControle_[7].z);
		glVertex3f(pointControle_[7].x, pointControle_[7].y, pointControle_[7].z);
				
		// 2eme morceau
		glVertex3f(pointControle_[7].x + largeur_, pointControle_[7].y, pointControle_[7].z);
		glVertex3f(pointControle_[7].x, pointControle_[7].y, pointControle_[7].z);
		glVertex3f(pointControle_[7].x, pointControle_[7].y - longueurP6P0 / 4, pointControle_[7].z);
		glVertex3f(pointControle_[7].x + largeur_, pointControle_[7].y - longueurP6P0 / 4, pointControle_[7].z);
								
	}
	glEnd();

	// tracer le 2eme but 
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
void NoeudTable::tracerCercle(double cx, double cy, double r, int nb_segments) const
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < nb_segments; ii++)
	{
		double theta = 2.0f * 3.1415926f * double(ii) / double(nb_segments);//l'angle courant

		double x = r * cosf(theta);
		double y = r * sinf(theta);

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
/// @fn bool NoeudTable::setPointControle( int numero, glm::vec3 pointControle)
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
		for (int i = 0; i < obtenirNombreEnfants(); i++) {
			chercher(i)->assignerPositionRelative(pointControle_[i]);
			std::cout << "enfant n" << i << "\n";
		}
			
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


//determiner si dans la table
/// angle
double NoeudTable::calculerAngle3D(const glm::dvec3 A, const glm::dvec3 B, const glm::dvec3 C) {
	// theta = arcos( u.v/(|u|.|v|) )
	double angle;
	glm::dvec3 u(A - B);
	glm::dvec3 v(C - B);
	angle = glm::acos(glm::dot(u, v) / (glm::length(u)*glm::length(v)));
	return angle;
}

double NoeudTable::calculerAngle2D(const glm::dvec3 A, const glm::dvec3 B, const glm::dvec3 C) {
	//on ignore la composante en z
	glm::dvec3 D(A.x, A.y, 0);
	glm::dvec3 E(B.x, B.y, 0);
	glm::dvec3 F(C.x, C.y, 0);
	return calculerAngle3D(D, E, F);
}

/// dansTriangle
bool NoeudTable::MdansTriangleABC(glm::dvec3 A, glm::dvec3 B, glm::dvec3 C, glm::dvec3 M) {
	//			B.							B.
	//		   / \		. M     ou 		   /  \	
	//		  /   \						  / .M \
	//      A.______.C			         A.______.C
	// -> M est dans ABC si la somme des angles AMC+AMB+BMC == 360
	if (M == A || M == B || M == C) return true;
	double angleTot = calculerAngle2D(A, M, B) + calculerAngle2D(B, M, C) + calculerAngle2D(C, M, A);
	bool reponse = glm::degrees(angleTot) == 360;
	return reponse;
}

/// dansTable
bool NoeudTable::dansTable(glm::dvec3 M) {
	/*
		etapes du check :
	p0----------p2----------p4
	| 1  ______/ | \_____ 5	 |
	|___/		 |		 \__ |
	p6		3	p8	 4	  __ p7
	| \____		 |	  ___/	 |
	|	2  \__	 | __/	  6	 |
	p1----------p3----------p5
	*/

	return MdansTriangleABC(pointControle_[0], pointControle_[2], pointControle_[6], M)
		|| MdansTriangleABC(pointControle_[1], pointControle_[3], pointControle_[6], M)
		|| MdansTriangleABC(pointControle_[2], pointControle_[3], pointControle_[6], M)
		|| MdansTriangleABC(pointControle_[2], pointControle_[3], pointControle_[7], M)
		|| MdansTriangleABC(pointControle_[2], pointControle_[4], pointControle_[7], M)
		|| MdansTriangleABC(pointControle_[3], pointControle_[5], pointControle_[7], M);
}