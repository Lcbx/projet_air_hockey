///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.cpp
/// @author equipe 10
/// @date september 2016
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
	// tracer la table
	tracerTable(vueProjection);
	//pour afficher les noeuds composites -- points de controle
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
void NoeudTable::tracerTable(const glm::mat4& vueProjection) const
{
	glLoadIdentity();
	// deactiver les textures (la table ne prend plus la texture des autres noeuds)
	glDisable(GL_TEXTURE_2D);
	// desactiver le test de profondeur
	glDisable(GL_DEPTH_TEST);
	

	//multiplication par la matrice de proj
#define PROJvec(arg)	glm::value_ptr(	glm::vec3(vueProjection * glm::vec4(arg, 1)))
#define PROJ(arg)		glm::value_ptr(	glm::vec3(vueProjection * glm::vec4(p(arg), 1)))
#define vecPROJ(arg)					glm::vec3(vueProjection * glm::vec4(p(arg), 1))
#define PROJ8			glm::value_ptr(	glm::vec3(vueProjection * glm::vec4(obtenirPositionRelative(), 1) ) )
#define vecPROJ8						glm::vec3(vueProjection * glm::vec4(obtenirPositionRelative(), 1) )
#define vecPROJvec(arg)					glm::vec3(vueProjection * glm::vec4(arg, 1))


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
	tracerMurs(vueProjection);
	// tracer les buts 
	tracerButs(vueProjection);
	// tracer les lignes de decoration 
	tracerLignesDecoration(vueProjection);
	// tracer les points de Controle 
	tracerPointsControle(vueProjection);

	// test 
	//tracerMur2Points(vueProjection, { 0,0,0 }, { 20,20,0 });


	//Activer le test de profondeur
	glEnable(GL_DEPTH_TEST);
	// activer le test de profondeur
	glEnable(GL_TEXTURE_2D);	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void tracerPointsControle(const glm::mat4& vueProjection) const
///
/// @param[in] : vueProjection
/// Cette fonction trace les points de controle de la zone du jeu 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerPointsControle(const glm::mat4& vueProjection) const {
	//affiche les points de controle, seul moyen que j'ai trouvé de bien les afficher
	//désolé, Luc
	for (int i = 0; i < obtenirNombreEnfants(); i++) {
		//point de controle
		auto pControl = (NoeudPointControle*)chercher(i);
		double delta; pControl->getDelta(delta);
		glm::vec4 couleur; pControl->getCouleur(couleur);
		glm::vec3 p0{ p(i).x - delta / 2, p(i).y + delta / 2, p(i).z };
		glm::vec3 p1{ p(i).x - delta / 2, p(i).y - delta / 2, p(i).z };
		glm::vec3 p2{ p(i).x + delta / 2, p(i).y - delta / 2, p(i).z };
		glm::vec3 p3{ p(i).x + delta / 2, p(i).y + delta / 2, p(i).z };

		glColor4fv(glm::value_ptr(couleur));
		glBegin(GL_QUADS);
		{
			glVertex3fv(PROJvec(p0));
			glVertex3fv(PROJvec(p1));
			glVertex3fv(PROJvec(p2));
			glVertex3fv(PROJvec(p3));
		}
		glEnd();	
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void tracerLignesDecoration(const glm::mat4& vueProjection) const
///
/// @param[in] : vueProjection
/// Cette fonction trace les lignes de decoration dans la zone du jeu 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerLignesDecoration(const glm::mat4& vueProjection) const
{
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
#undef min
	double distance = std::min({ glm::distance(vecPROJ(2), vecPROJ8),
								 glm::distance(vecPROJ(6), vecPROJ8),
								 glm::distance(vecPROJ(0), vecPROJ8),
								 glm::distance(vecPROJ(1), vecPROJ8) });
	double coeff = 0.4;
	double rayon = distance  * coeff;
	tracerCercle((vecPROJ8).x, (vecPROJ8).y, rayon, 100);


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerMur2Points(const glm::mat4& vueProjection, glm::vec3 p1, glm::vec3 p2) const
///
/// @param[in] : vueProjection
///					p1,p2
/// Cette fonction trace un mur entre 2 points donnees 
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
double NoeudTable::Delta(double A, double B, double C) const
{
	return (pow(B, 2) - 4 * A*C);
}
void NoeudTable::tracerMur2Points(const glm::mat4& vueProjection, glm::vec3 A, glm::vec3 B) const
{
	//					
	//  A--------------B	
	//	|			   | 
	//  |			   |  
	//	----------------	
	// tracer un muret entre A et B revient a tracer un quad P1P2P3P4 telque P1P4 = AB et P1P2 = largeur_
	glm::vec3 P1, P2, P3, P4;

	glm::vec3 C, D;
	// P1------------P4
	// |			  |
	// |			  |
	// P2------------P3
	if (A.x == B.x)
	{
		if (A.y > B.y)
		{
			P1 = A; P2 = B;
			P3 = { B.x + largeur_,B.y,B.z };
			P4 = { A.x + largeur_,A.y,A.z };
		}
		else
		{
			P1 = B; P2 = A;
			P3 = { A.x + largeur_,A.y,A.z };
			P4 = { B.x + largeur_,B.y,B.z };
		}
	}
	else
	{
		if (A.y == B.y)
		{
			if (A.x > B.x)
			{
				P1 = B; P2 = A; 
				P3 = { A.x, A.y - largeur_, A.z };
				P4 = { B.x, B.y - largeur_, B.z };
			}
			else
			{
				P1 = A; P2 = B;
				P3 = { B.x, B.y - largeur_, B.z };
				P4 = { A.x, A.y - largeur_, A.z };
			}
		}
		else // cas general
		{
			// caluler la pente de la droite (AB)
			double penteAB = calculPente(A, B);
			// pente de la droite perpendiculaire a (AB)
			double pentePerp = ( (penteAB != 0 )? -1/penteAB : 1);
			double b = calculB(pentePerp, A);
//#define Delta(A,B,C) pow(B,2)-4*A*C
			double bx = (b - A.y) / pentePerp - A.x;
			double cx = pow((b - A.y) / pentePerp, 2) - pow(largeur_, 2);
			double delta = Delta(1,bx ,cx  );
			double x1 = (-bx - sqrt(delta)) / 2;
			double x2 = (-bx + sqrt(delta)) / 2;
			double y1 = pentePerp*x1 +b;
			double y2 = pentePerp*x2 + b;
		//	C= { x1,y1,0. };
			std::cout << "A(" << A.x << "," << A.y << ") B(" << B.x << "," << B.y << ") C1(" << x1 << "," << y1 << ") C2(" << x2 << "," << y2 << ")" << std::endl;
//#undef Delta
		}
	}

	glColor4fv(glm::value_ptr(couleurMurs_));
	glBegin(GL_LINE);
	{
		glVertex3fv(PROJvec(A));
		glVertex3fv(PROJvec(B));
		glVertex3fv(PROJvec(C));
	}
	glEnd();
	////tracer le mur
	//glColor4fv(glm::value_ptr(couleurMurs_));
	//glBegin(GL_QUADS);
	//{
	//	glVertex3fv(PROJvec(P1));
	//	glVertex3fv(PROJvec(P2));
	//	glVertex3fv(PROJvec(P3));
	//	glVertex3fv(PROJvec(P4));
	//}
	//glEnd();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn void NoeudTable::tracerMurs3Points(const glm::mat4& vueProjection,glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) const
///
/// @param[in] : vueProjection
///					p1,p2,p3
/// Cette fonction trace les murs autour des trois points donnees 
///
/// @return Aucune.
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerMurs3Points(const glm::mat4& vueProjection, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) const
{


}
///////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerMurs(const glm::mat4& vueProjection) const
///
/// @param[in] : vueProjection
/// Cette fonction trace les murs autour de la table
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerMurs(const glm::mat4& vueProjection) const
{
	// tracer murs
	glColor4fv(glm::value_ptr(couleurMurs_));
	glBegin(GL_QUADS);
	{
		// mur p0p6
		glVertex3fv(PROJ(0));
		glVertex3fv(PROJvec(glm::vec3(p(0).x - largeur_, p(0).y, p(0).z)));
		glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_, p(6).y, p(6).z)));
		glVertex3fv(PROJ(6));
		// mur p6p1
		glVertex3fv(PROJ(6));
		glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_, p(6).y, p(6).z)));
		glVertex3fv(PROJvec(glm::vec3(p(1).x - largeur_, p(1).y, p(1).z)));
		glVertex3fv(PROJ(1));
		// mur p0p2
		glVertex3fv(PROJ(2));
		glVertex3fv(PROJvec(glm::vec3(p(2).x, p(2).y + largeur_, p(2).z)));
		glVertex3fv(PROJvec(glm::vec3(p(0).x, p(0).y + largeur_, p(0).z)));
		glVertex3fv(PROJ(0));
		// mur p2p4
		glVertex3fv(PROJ(4));
		glVertex3fv(PROJvec(glm::vec3(p(4).x, p(4).y + largeur_, p(4).z)));
		glVertex3fv(PROJvec(glm::vec3(p(2).x, p(2).y + largeur_, p(2).z)));
		glVertex3fv(PROJ(2));
		// mur p4p7
		glVertex3fv(PROJvec(glm::vec3(p(4).x + largeur_, p(4).y, p(4).z)));
		glVertex3fv(PROJ(4));
		glVertex3fv(PROJ(7));
		glVertex3fv(PROJvec(glm::vec3(p(7).x + largeur_, p(7).y, p(7).z)));
		// mur p7p5		
		glVertex3fv(PROJvec(glm::vec3(p(7).x + largeur_, p(7).y, p(7).z)));
		glVertex3fv(PROJ(7));
		glVertex3fv(PROJ(5));
		glVertex3fv(PROJvec(glm::vec3(p(5).x + largeur_, p(5).y, p(5).z)));
		// mur p5p3
		glVertex3fv(PROJvec(glm::vec3(p(5).x, p(5).y - largeur_, p(5).z)));
		glVertex3fv(PROJ(5));
		glVertex3fv(PROJ(3));
		glVertex3fv(PROJvec(glm::vec3(p(3).x, p(3).y - largeur_, p(7).z)));
		// mur p3p1
		glVertex3fv(PROJvec(glm::vec3(p(3).x, p(3).y - largeur_, p(3).z)));
		glVertex3fv(PROJ(3));
		glVertex3fv(PROJ(1));
		glVertex3fv(PROJvec(glm::vec3(p(1).x, p(1).y - largeur_, p(1).z)));
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
double NoeudTable::calculPente(glm::vec3 P0, glm::vec3 P1) const
{
	if (P0.x == P1.x)
		return 1.;
	else
		if (P0.y == P1.y) 
			return 0.;
		else
			return (double) (P0.y - P1.y) / (P0.x - P1.x);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudTable::calculB(double pente, glm::vec3 point) const
///
/// @param[in] 
///		point : un point de la droite
///		pente : la pente de la droite
/// Cette fonction calcul le parametre b  de la droite  y = a*x +b
///
/// @return double
///
////////////////////////////////////////////////////////////////////////
double NoeudTable::calculB(double pente, glm::vec3 point) const
{
	if (pente == 0.)
		return point.y;
	else
		if (pente == 1.)
			return point.x;
		else
			return (point.y - pente*point.x);	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerButs(const glm::mat4& vueProjection) const
///
/// @param[in]  vueProjection
//
/// Cette fonction trace les but avec une certaine longueur selon la projection
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerButs(const glm::mat4& vueProjection) const
{
#define delta 2
	glColor4f(couleurButs_[0], couleurButs_[1], couleurButs_[2], couleurButs_[3]);
	glBegin(GL_QUADS);
	{	
		//1er but
		// 1er morceau P6P0
		glm::vec3 point = { (p(6).x + (p(6).x + p(0).x) / 2) / 2, (p(6).y + (p(6).y + p(0).y) / 2) / 2, (p(6).z +(p(6).z + p(0).z) / 2) / 2 };
		glVertex3fv(PROJvec(glm::vec3( p(6).x + delta, p(6).y, p(6).z)));
		glVertex3fv(PROJvec(glm::vec3(point.x + delta, point.y, point.z)));
		glVertex3fv(PROJvec(glm::vec3(point.x - largeur_-delta, point.y, point.z)));
		glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_-delta, p(6).y, p(6).z)));
		//glVertex3fv(PROJ(6));
		//glVertex3fv(PROJvec(glm::vec3( point ) ) );
		//glVertex3fv(PROJvec(glm::vec3(point.x - largeur_,point.y, point.z)));
		//glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_, p(6).y, p(6).z)));
		// 2eme morceau P1P6
		point = { (p(6).x + (p(6).x + p(1).x) / 2) / 2, (p(6).y + (p(6).y + p(1).y) / 2) / 2, (p(6).z + (p(6).z + p(1).z) / 2) / 2 };
		glVertex3fv(PROJvec(glm::vec3(p(6).x + delta, p(6).y, p(6).z)));
		glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_-delta, p(6).y, p(6).z)));
		glVertex3fv(PROJvec(glm::vec3(point.x - largeur_-delta, point.y, point.z)));
		glVertex3fv(PROJvec(glm::vec3(point.x + delta, point.y, point.z)));
		//glVertex3fv(PROJ(6));
		//glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_, p(6).y, p(6).z)));
		//glVertex3fv(PROJvec(glm::vec3(point.x - largeur_, point.y, point.z)));
		//glVertex3fv(PROJvec(glm::vec3(point)));
		//2eme but
		// 1ere morceau P7P4
		point = { (p(7).x + (p(7).x + p(4).x) / 2) / 2, (p(7).y + (p(7).y + p(4).y) / 2) / 2, (p(7).z + (p(7).z + p(4).z) / 2) / 2 };
		//glVertex3fv(PROJ(7));
		//glVertex3fv(PROJvec(glm::vec3(p(7).x + largeur_, p(7).y, p(7).z)));
		//glVertex3fv(PROJvec(glm::vec3(point.x + largeur_, point.y, point.z)));
		//glVertex3fv(PROJvec(glm::vec3(point)));
		glVertex3fv(PROJvec(glm::vec3(p(7).x - delta, p(7).y, p(7).z)));
		glVertex3fv(PROJvec(glm::vec3(p(7).x + largeur_+delta, p(7).y, p(7).z)));
		glVertex3fv(PROJvec(glm::vec3(point.x + largeur_+delta, point.y, point.z)));
		glVertex3fv(PROJvec(glm::vec3(point.x - delta, point.y, point.z)));
		//2eme morceau P7P5
		point = { (p(7).x + (p(7).x + p(5).x) / 2) / 2, (p(7).y + (p(7).y + p(5).y) / 2) / 2, (p(7).z + (p(7).z + p(5).z) / 2) / 2 };
		glVertex3fv(PROJvec(glm::vec3(p(7).x - delta, p(7).y, p(7).z)));
		glVertex3fv(PROJvec(glm::vec3(point.x - delta, point.y, point.z)));
		glVertex3fv(PROJvec(glm::vec3(point.x + largeur_ + delta, point.y, point.z)));
		glVertex3fv(PROJvec(glm::vec3(p(7).x + largeur_ + delta, p(7).y, p(7).z)));
		//glVertex3fv(PROJ(7));
		//glVertex3fv(PROJvec(glm::vec3(point)));
		//glVertex3fv(PROJvec(glm::vec3(point.x + largeur_, point.y, point.z)));
		//glVertex3fv(PROJvec(glm::vec3(p(7).x + largeur_, p(7).y, p(7).z)));
	}
	glEnd();

#undef delta 2

	//// tracez le 1er but
	////// pente de la droite p6p0
	//double a60 = calculPente(p(0),p(6));
	//double b60 = calculB(a60, p(0));
	//double longueur = sqrt(pow((pointControle_[0].x - pointControle_[6].x),2)+pow(pointControle_[0].y - pointControle_[6].y,2));
	//
	//float dx = p(0).x - p(6).x;
	//float dy = p(0).y - p(6).y;
	//GLfloat angle = glm::atan(dx / dy);
	////std::cout << "dx = " << dx <<" dy = "<<dy<< std::endl;
	////std::cout << "angle = " << angle << std::endl;
	////////////////////////////////////
	////				|				//
	//// 2eme 		|   1er			//
	//// Quadrant		|	Quadrant	//
	////				|				//
	////------------------------------//
	////				|				//	
	////	3eme		|	4eme		//
	////	Quadrant	|	Quadrant	//
	////				|				//
	////////////////////////////////////
	//glm::mat4 Vp = vueProjection;
	//glColor4f(couleurButs_[0], couleurButs_[1], couleurButs_[2], couleurButs_[3]);
	//if (dx > 0)
	//{
	//	if (dy > 0)
	//	{
	//		glm::rotate(Vp, angle, p(0));
	//		//1er quadrant
	//		glBegin(GL_QUADS);
	//		{
	//			// 1er morceau P0P6
	//			glVertex3fv(PROJ(6));
	//			glVertex3fv(PROJvec(glm::vec3(p(6).x, p(6).y + longueur / 4, p(6).z)));
	//			glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_, p(6).y + longueur / 4, p(6).z)));
	//			glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_, p(6).y, p(6).z)));

	//		}
	//		glEnd();
	//	

	//	}
	//	else
	//	{
	//		//4eme quadrant
	//	}
	//}
	//else
	//{
	//	if (dy > 0)
	//	{
	//		//2eme quadrant
	//	}
	//	else
	//	{
	//		//3eme quadrant
	//	}
	//}
	//
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

		glm::vec3 point(x+cx, y+cy, 0);

		glVertex2f(point.x, point.y);

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
	if (numero < 0 || numero >9)
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
/// @param[in] 	pointControle : le nouveau point de controle
///				numero : le numero du point de controle auquel on doit modifier sa valeur
///
/// @return bool.
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::setPointControle(int numero, glm::vec3 pointControle)
{
	if (numero < 0 || numero >9)
		return false;
	else
	{
		pointControle_[numero] = pointControle;
		return true;
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::setPointControles()
///
/// Cette fonction modifie les coordonnes d'un des 8 points de controle de la table
///
/// @param[in] 
///
/// @return bool.
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::setPointControles()
{
	for (int i = 0; i < obtenirNombreEnfants(); i++) 
	{
		chercher(i)->assignerPositionRelative(pointControle_[i]);
		std::cout << "enfant n" << i << "\t" <<p(i).x << "\t" << p(i).y  << "\t" << p(i).z << "\n";
	}
	return true;
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
	| \___  1	 | 2    ___/ |
	|	8 \____  |  ___/  3  |
	p6 ________\p8 /________ p7
	|  7  _____/ |\____	  4  |
	| ___/	6	 |  5  \____ |
	p1----------p3----------p5

	*/

	glm::vec3 p8(p(2).x, obtenirPositionRelative().y, obtenirPositionRelative().z);

	return MdansTriangleABC(p8, p(0), p(2), M)
		|| MdansTriangleABC(p8, p(2), p(4), M)
		|| MdansTriangleABC(p8, p(4), p(7), M)
		|| MdansTriangleABC(p8, p(7), p(5), M)
		|| MdansTriangleABC(p8, p(5), p(3), M)
		|| MdansTriangleABC(p8, p(3), p(1), M)
		|| MdansTriangleABC(p8, p(1), p(6), M)
		|| MdansTriangleABC(p8, p(6), p(0), M);
}