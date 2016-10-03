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
{}

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

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0,// left
	//	1.0,   // right
	//	0.0,   // bottom
	//	1.0,   // top
	//	1.0,  // near
	//	-1.0);  // far


	glLoadIdentity();
	// deactiver les textures (la table ne prend plus la texture des autres noeuds)
	glDisable(GL_TEXTURE_2D);
	// desactiver le test de profondeur
	glDisable(GL_DEPTH_TEST);

	glVertex3fv( glm::value_ptr(  glm::vec3(0,0,0) ) );

	//multiplication par la matrice de proj
#define PROJvec(arg) glm::value_ptr(glm::vec3(vueProjection * glm::vec4(arg, 0)))
#define PROJ(arg) glm::value_ptr(glm::vec3(vueProjection * glm::vec4(p(arg), 0)))
#define vecPROJ(arg) glm::vec3(vueProjection * glm::vec4(p(arg), 0))
#define PROJ8 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(obtenirPositionRelative(), 0) ) )
#define vecPROJ8 glm::vec3(vueProjection * glm::vec4(obtenirPositionRelative(), 0) )


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
	glColor4fv(glm::value_ptr(couleurTable_));
	glBegin(GL_TRIANGLE_FAN);
	{

		glVertex3fv(PROJ8);
		glVertex3fv(PROJ(0));
		glVertex3fv(PROJ(6));
		glVertex3fv(PROJ(1));
		glVertex3fv(PROJ(3));
		glVertex3fv(PROJ(5));
		glVertex3fv(PROJ(7));
		glVertex3fv(PROJ(4));
		glVertex3fv(PROJ(2));
		glVertex3fv(PROJ(0));
	}
	glEnd();

	
	// tracer les murs 
	
	// tracer murs
	glColor4fv(glm::value_ptr(couleurMurs_));
	glBegin(GL_QUADS);
	{
		// mur p0p6
		glVertex3fv(PROJ(0));
		glVertex3fv(PROJvec(glm::vec3(p(0).x - largeur_, p(0).y, p(0).z))) ;
		glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_, p(6).y, p(6).z)));
		glVertex3fv(PROJvec(glm::vec3(p(6).x, p(6).y, p(6).z)));

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
		glVertex3f(pointControle_[4].x, pointControle_[4].y, pointControle_[4].z);
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


	// tracer les buts 
	//tracerButs();

	// tracer les lignes de decoration 
	// tracer le contour
	glColor4fv(glm::value_ptr(couleurContour_));
	glLineWidth(2.);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3fv(PROJ(0));
		glVertex3fv(PROJ(2)); 
		glVertex3fv(PROJ(4)); 
		glVertex3fv(PROJ(7)); 
		glVertex3fv(PROJ(5)); 
		glVertex3fv(PROJ(3));
		glVertex3fv(PROJ(1));
		glVertex3fv(PROJ(6));
	}
	glEnd();

	// tracer les lignes du terrain
	glLineWidth(5.);
	glColor4fv(glm::value_ptr(couleurLignes_));
	glBegin(GL_LINES);
	{
		glVertex3fv(PROJ(2)); 
		glVertex3fv(PROJ(3)); 
	}
	glEnd();




	// tracer un cercle au milieu du terrain
	glLineWidth(3.);
	glColor4f(1., 1., 0., 1.);
	double rayon = 0.2;
	double distance = abs( (vecPROJ(2)).y - (vecPROJ(3)).y );
	//double distance = sqrt( pow(1,2) + pow(1,2) );
	double coeff = 0.4;
	rayon = distance / 2 * coeff;
	//tracerCercle(double(pointControle_[8][0]),double(pointControle_[8][1]),rayon,100);
	tracerCercle( (vecPROJ8).x, (vecPROJ8).y, rayon, 100);

#undef PROJ(arg)
#undef PROJ8
#undef vecPROJ8

	//Activer le test de profondeur
	glEnable(GL_DEPTH_TEST);
	// activer le test de profondeur
	glEnable(GL_TEXTURE_2D);

	//pour afficher les noeuds composites
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
			std::cout << "enfant n" << i << "\t" <<p(i).x << "\t" << p(i).y  << "\t" << p(i).z << "\n";
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
	bool reponse = glm::round(glm::degrees(angleTot)) == 360;
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

	return MdansTriangleABC(p(0), p(2), p(6), M)
		|| MdansTriangleABC(p(1), p(3), p(6), M)
		|| MdansTriangleABC(p(2), p(3), p(6), M)
		|| MdansTriangleABC(p(2), p(3), p(7), M)
		|| MdansTriangleABC(p(2), p(4), p(7), M)
		|| MdansTriangleABC(p(3), p(5), p(7), M);
}