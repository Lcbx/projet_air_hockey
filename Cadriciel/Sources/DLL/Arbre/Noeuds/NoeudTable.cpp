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
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"
#include "GL/glew.h"

#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "Utilitaire.h"

#include <../Visiteur.h>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "OpenGL_Nuanceur.h"
#include "OpenGL_Programme.h"
#include "Modele3D.h"
#include "AideGL.h"
#include "Utilitaire.h"

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
void NoeudTable::afficherConcret(const glm::mat4& modele, const glm::mat4& vue, const glm::mat4& projection) const
{
	//dessiner la table
	vbo_->dessiner(modele, vue, projection);
	vbo_->dessiner(modele, vue, projection);

	glm::mat4x4 const& m{ projection * vue * modele };

	// Appliquer le nuanceur
	opengl::Programme::Start(vbo_->programme_);
	vbo_->programme_.assignerUniforme("modelViewProjection", m);
	//vbo_->programme_.assignerUniforme("colorIn", glm::vec4(1.f,1.f,1.f,0.f));

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// tracer la table
	tracerTable(glm::mat4(1.f));



	opengl::Programme::Stop(vbo_->programme_);

	//pour afficher les noeuds composites -- points de controle
	//NoeudComposite::afficherConcret(modele, vue, projection);
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
	// on ne veut pas de traitment sur la table
	//v->visiter(this);
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
	//glDisable(GL_DEPTH_TEST);
	

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
	//vbo_->programme_.assignerUniforme("colorIn", couleurTable_);
	//glBegin(GL_TRIANGLE_FAN);
	//{
	//	glVertex3fv(PROJ8);
	//	glVertex3fv(PROJ(0));
	//	glVertex3fv(PROJ(6));
	//	glVertex3fv(PROJ(1));
	//	glVertex3fv(PROJ(3));
	//	glVertex3fv(PROJ(5));
	//	glVertex3fv(PROJ(7));
	//	glVertex3fv(PROJ(4));
	//	glVertex3fv(PROJ(2));
	//	glVertex3fv(PROJ(0));
	//}
	//glEnd();
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// tracer pt intersection
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//glm::vec3 PI;
	//intersection2Droites(p(2), p(3), p(4), p(7), PI);
	//{
	//	glColor3f(0, 1, 1);
	//	glPointSize(10);
	//	glBegin(GL_POINTS);
	//	glVertex3fv(PROJvec(PI));
	//	glEnd();
	//}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// tracer les murs 
	tracerMurs(vueProjection);
	// tracer les buts 
	tracerButs(vueProjection,longueurButs_);
	// tracer les lignes de decoration 
	tracerLignesDecoration(vueProjection);
	
	// tracer les points de Controle 
	glDisable(GL_DEPTH_TEST);
	if (afficherPointsControles)
		tracerPointsControle(vueProjection);
	glEnable(GL_DEPTH_TEST);
	//// get point du but gauche
	//glm::vec3  pointHaut, pointMilieu, pointBas;
	//getbuts(2, pointHaut, pointMilieu, pointBas);
	//glColor3f(1, 0, 1);
	//glPointSize(10);
	//glBegin(GL_POINTS);
	//{
	//	glVertex3fv(PROJvec(pointHaut));
	//	glVertex3fv(PROJvec(pointMilieu));
	//	glVertex3fv(PROJvec(pointBas));

	//}
	//glEnd();
	//getbuts(1, pointHaut, pointMilieu, pointBas);
	//glColor3f(0, 1, 1);
	//glBegin(GL_POINTS);
	//{
	//	glVertex3fv(PROJvec(pointHaut));
	//	glVertex3fv(PROJvec(pointMilieu));
	//	glVertex3fv(PROJvec(pointBas));

	//}
	//glEnd();

	// test 
	//tracerMur2Points(vueProjection, { 0,0,0 }, { 20,20,0 },largeur_,true);
	
	//Activer le test de profondeur
	//glEnable(GL_DEPTH_TEST);
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

		//vbo_->programme_.assignerUniforme("colorIn", couleur);
		vbo_->programme_.assignerUniforme("colorIn", glm::vec4{ 0.,1.,0.,1. });
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
	vbo_->programme_.assignerUniforme("colorIn", glm::vec4{ 1.,1.,0.,1. });
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
	//vbo_->programme_.assignerUniforme("colorIn", couleurLignes_);
	vbo_->programme_.assignerUniforme("colorIn", glm::vec4{ 1.,1.,0.,1. });
	glBegin(GL_LINES);
	{
		glVertex3fv(PROJ(2));
		glVertex3fv(PROJ(3));
	}
	glEnd();

	// tracer un cercle au milieu du terrain
	glLineWidth(3.);
	vbo_->programme_.assignerUniforme("colorIn", glm::vec4(1.f, 1.f, 0.f, 1.f));

#undef min
	double distance = std::min({ glm::distance(p(2), vecPROJ8),
								 glm::distance(p(6), vecPROJ8),
								 glm::distance(p(0), vecPROJ8),
								 glm::distance(p(1), vecPROJ8) });
	double coeff = 0.4;
	double rayon = distance  * coeff;
	tracerCercle(vueProjection,vecPROJ8.x, vecPROJ8.y, rayon, 50);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerMur2Points(const glm::mat4& vueProjection, glm::vec3 A, glm::vec3 B,
///										  double largeur,bool direction) const
///
/// @param[in] : vueProjection
///				A,B : les 2 points 
///				largeur : la largeur du mur
///				direction : true vers la droite, false vers la gauche
/// Cette fonction trace un mur entre 2 points donnees 
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerMur2Points(const glm::mat4& vueProjection, glm::vec3 A, glm::vec3 B, double largeur, bool direction) const
{
	//					
	//  A--------------B	
	//	|			   | 
	//  |			   |  
	//	D--------------C	
	// tracer un muret entre A et B revient a tracer un quad ABCD telque CD = largeur
	glm::vec3 P1,P2,P3,P4,C,D;
	
	if (A.x == B.x)
	{
		if (A.y > B.y)
		{
			if (direction)
			{
				P1 = A; P2 = B;
				P3 = { B.x + largeur_,B.y,B.z };
				P4 = { A.x + largeur_,A.y,A.z };
			}
			else
			{
				P1 = A; P2 = B;
				P3 = { B.x - largeur_,B.y,B.z };
				P4 = { A.x - largeur_,A.y,A.z };
			}
		}
		else
		{
			if (direction)
			{
				P1 = B; P2 = A;
				P3 = { A.x + largeur_,A.y,A.z };
				P4 = { B.x + largeur_,B.y,B.z };
			}
			else
			{
				P1 = B; P2 = A;
				P3 = { A.x - largeur_,A.y,A.z };
				P4 = { B.x - largeur_,B.y,B.z };			
			}
			
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
#define Delta(A,B,C) pow(B,2)-4*A*C
			double bx = (b - A.y) / pentePerp - A.x;
			double cx = pow((b - A.y) / pentePerp, 2) - pow(largeur_, 2);
			double delta = Delta(1,bx ,cx  );
			double x1 = (-bx - sqrt(delta)) / 2;
			double x2 = (-bx + sqrt(delta)) / 2;
			double y1 = pentePerp*x1 +b;
			double y2 = pentePerp*x2 + b;
			C= { x1,y1,0. };
			D = {(B.x-A.x)+C.x,(B.y - A.y)+C.y ,0};
			//std::cout << "A(" << A.x << "," << A.y << ") B(" << B.x << "," << B.y << ") C1(" << x1 << "," << y1 << ") C2(" << x2 << "," << y2 << ")" << std::endl;
#undef Delta
		}
	}

	vbo_->programme_.assignerUniforme("colorIn", couleurMurs_);
	glBegin(GL_QUADS);
	{
		glVertex3fv(PROJvec(A));
		glVertex3fv(PROJvec(B));
		glVertex3fv(PROJvec(D));
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
/// Cette fonction trace les murs autour des trois points donnees -- gestion des jonctions
///
/// @return Aucune.
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerMurs3Points(const glm::mat4& vueProjection, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) const
{


}

/////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerMur(const glm::mat4& vueProjection, 
///		glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4) const
/// @ Author Ali
/// @param[in] : vueProjection
/// Cette fonction permet de tracer un seul mur en 3D  parmis les murs autour de la Table
/// Livrable 3
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerMur(const glm::mat4& vueProjection, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4) const
{
	// tracer les 6 Quads de la boite representant le mur
	glBegin(GL_QUADS);
	{
		// Quad 1
		glVertex3fv(PROJvec(point1));
		glVertex3fv(PROJvec(point2));
		glVertex3fv(PROJvec(point3));
		glVertex3fv(PROJvec(point4));
		//Quad 2 
		glVertex3fv(PROJvec( glm::vec3( point1.x,point1.y,hauteurMur_)));
		glVertex3fv(PROJvec(glm::vec3(point2.x, point2.y, hauteurMur_)));
		glVertex3fv(PROJvec(glm::vec3(point3.x, point3.y, hauteurMur_)));
		glVertex3fv(PROJvec(glm::vec3(point4.x, point4.y, hauteurMur_)));
		//Quad 3
		glVertex3fv(PROJvec(glm::vec3(point1.x, point1.y, hauteurMur_)));
		glVertex3fv(PROJvec(glm::vec3(point2.x, point2.y, hauteurMur_)));
		glVertex3fv(PROJvec(point2));
		glVertex3fv(PROJvec(point1));
		//Quad 4
		glVertex3fv(PROJvec(point4));
		glVertex3fv(PROJvec(point3));
		glVertex3fv(PROJvec(glm::vec3(point3.x, point3.y, hauteurMur_)));
		glVertex3fv(PROJvec(glm::vec3(point4.x, point4.y, hauteurMur_)));
		//Quad 5
		glVertex3fv(PROJvec(point1));
		glVertex3fv(PROJvec(point4));
		glVertex3fv(PROJvec(glm::vec3(point4.x, point4.y, hauteurMur_)));
		glVertex3fv(PROJvec(glm::vec3(point1.x, point1.y, hauteurMur_)));
		//Quad 6
		glVertex3fv(PROJvec(point2));
		glVertex3fv(PROJvec(point3));
		glVertex3fv(PROJvec(glm::vec3(point3.x, point3.y, hauteurMur_)));
		glVertex3fv(PROJvec(glm::vec3(point2.x, point2.y, hauteurMur_)));
		
	}
	glEnd();
}



///////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerMurs(const glm::mat4& vueProjection) const
///
/// @param[in] : vueProjection
/// Cette fonction trace les murs autour de la table
/// version 0 
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerMurs(const glm::mat4& vueProjection) const
{
	// tracer murs
		vbo_->programme_.assignerUniforme("colorIn", glm::vec4{ (109.f / 255) , (7.f / 255), (26.f / 255), 0.5f });
		//glEnable(GL_BLEND);
		// test aficher mur p0p6
		tracerMur(vueProjection, p(0), glm::vec3(p(0).x - largeur_, p(0).y, p(0).z), glm::vec3(p(6).x - largeur_, p(6).y, p(6).z), p(6));
		tracerMur(vueProjection, p(6), glm::vec3(p(6).x - largeur_, p(6).y, p(6).z), glm::vec3(p(1).x - largeur_, p(1).y, p(1).z), p(1));
		tracerMur(vueProjection, p(2), glm::vec3(p(2).x, p(2).y + largeur_, p(2).z), glm::vec3(p(0).x, p(0).y + largeur_, p(0).z), p(0));
		tracerMur(vueProjection, p(4), glm::vec3(p(4).x, p(4).y + largeur_, p(4).z), glm::vec3(p(2).x, p(2).y + largeur_, p(2).z), p(2));
		
		tracerMur(vueProjection, glm::vec3(p(4).x + largeur_, p(4).y, p(4).z), p(4), p(7), glm::vec3(p(7).x + largeur_, p(7).y, p(7).z));


		//glDisable(GL_BLEND);

	glBegin(GL_QUADS);
	{
		//// mur p0p6
		//glVertex3fv(PROJ(0));
		//glVertex3fv(PROJvec(glm::vec3(p(0).x - largeur_, p(0).y, p(0).z)));
		//glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_, p(6).y, p(6).z)));
		//glVertex3fv(PROJ(6));
		// mur p6p1
		/*glVertex3fv(PROJ(6));
		glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_, p(6).y, p(6).z)));
		glVertex3fv(PROJvec(glm::vec3(p(1).x - largeur_, p(1).y, p(1).z)));
		glVertex3fv(PROJ(1));*/
		//// mur p0p2
		//glVertex3fv(PROJ(2));
		//glVertex3fv(PROJvec(glm::vec3(p(2).x, p(2).y + largeur_, p(2).z)));
		//glVertex3fv(PROJvec(glm::vec3(p(0).x, p(0).y + largeur_, p(0).z)));
		//glVertex3fv(PROJ(0));
		//// mur p2p4
		//glVertex3fv(PROJ(4));
		//glVertex3fv(PROJvec(glm::vec3(p(4).x, p(4).y + largeur_, p(4).z)));
		//glVertex3fv(PROJvec(glm::vec3(p(2).x, p(2).y + largeur_, p(2).z)));
		//glVertex3fv(PROJ(2));
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
	return (point.y - pente*point.x);	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerButs(const glm::mat4& vueProjection) const
///
/// @param[in]  vueProjection
/// version 0
/// Cette fonction trace les but avec une certaine longueur qui 
/// varie en proportion de la longueur du mur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerButs(const glm::mat4& vueProjection) const 
{
#define delta 2
	vbo_->programme_.assignerUniforme("colorIn", couleurButs_);
	glBegin(GL_QUADS);
	{	
		//1er but
		// 1er morceau P6P0
		glm::vec3 point = { (p(6).x + (p(6).x + p(0).x) / 2) / 2, (p(6).y + (p(6).y + p(0).y) / 2) / 2, (p(6).z + (p(6).z + p(0).z) / 2) / 2 };
		glVertex3fv(PROJvec(glm::vec3(p(6).x + delta, p(6).y, p(6).z)));
		glVertex3fv(PROJvec(glm::vec3(point.x + delta, point.y, point.z)));
		glVertex3fv(PROJvec(glm::vec3(point.x - largeur_ - delta, point.y, point.z)));
		glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_ - delta, p(6).y, p(6).z)));
		// 2eme morceau P1P6
		point = { (p(6).x + (p(6).x + p(1).x) / 2) / 2, (p(6).y + (p(6).y + p(1).y) / 2) / 2, (p(6).z + (p(6).z + p(1).z) / 2) / 2 };
		glVertex3fv(PROJvec(glm::vec3(p(6).x + delta, p(6).y, p(6).z)));
		glVertex3fv(PROJvec(glm::vec3(p(6).x - largeur_ - delta, p(6).y, p(6).z)));
		glVertex3fv(PROJvec(glm::vec3(point.x - largeur_ - delta, point.y, point.z)));
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
		glVertex3fv(PROJvec(glm::vec3(p(7).x + largeur_ + delta, p(7).y, p(7).z)));
		glVertex3fv(PROJvec(glm::vec3(point.x + largeur_ + delta, point.y, point.z)));
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

#undef delta 
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void  NoeudTable::calculerPointDistance(glm::vec3 p0, glm::vec3 p1, 
///		double longueur, double largeur, glm::vec3 & p2, glm::vec3 & p3, glm::vec3 & p4) const
///
/// @param[in]  veProjection
///				longueur: la longueur du but
//
/// Cette fonction donne les quatres points du quadrilateur de la moitie-but a tracer selon une longueur et une largeur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void  NoeudTable::calculerPointDistance(glm::vec3 p0, glm::vec3 p1, double longueur, double largeur, glm::vec3 & p2, glm::vec3 & p3, glm::vec3 & p4) const
{
#define delta 2	
#define Delta(A,B,C) pow(B,2)-4*A*C
	glm::vec3 P;
	if (p0.x == p1.x) 
	{
		if (p0.y > p1.y)
		{
			p2.x = p1.x;
			p2.y = p1.y + longueur;
			p3.x = p2.x - largeur_;
			p3.y = p2.y;
			p4.x = p1.x - largeur_;
			p4.y = p1.y;
		}
		else
		{
			p2.x = p1.x;
			p2.y = p1.y - longueur;
			p3.x = p2.x - largeur_;
			p3.y = p2.y;
			p4.x = p1.x - largeur_;
			p4.y = p1.y;
		}
		
	}
	else
	{
		if (p0.y == p1.y)
		{
			if (p0.x > p1.x)
			{
				p2.y = p1.y;
				p2.x = p1.x + longueur;
				p3.y = p2.y - largeur_;
				p3.x = p2.x;
				p4.y = p1.y - largeur_;
				p4.x = p1.x;
			}
			else
			{
				p2.y = p1.y;
				p2.x = p1.x - longueur;
				p3.y = p2.y - largeur_;
				p3.x = p2.x;
				p4.y = p1.y - largeur_;
				p4.x = p1.x;
			}
			
		}
		else
		{
			double dx = p0.x - p1.x;
			double dy = p0.y - p1.y;
			if (dy>0) 
			{
				double norme = glm::distance(p0, p1);
				glm::vec3 u = { (p0.x - p1.x) / norme ,(p0.y - p1.y) / norme,(p0.z - p1.z) / norme };
				glm::vec3 p1p2 = { longueur*u.x, longueur*u.y, longueur*u.z };
				p2 = p1p2 + p1;
				p3.x = p2.x - largeur; p3.y = p2.y;
				p4.x = p1.x - largeur; p4.y = p1.y;
			}
			else
			{
				double norme = glm::distance(p0, p1);
				glm::vec3 u = { (p0.x - p1.x) / norme ,(p0.y - p1.y) / norme,(p0.z - p1.z) / norme };
				glm::vec3 p1p2 = { longueur*u.x, longueur*u.y, longueur*u.z };
				p2 = p1p2 + p1;
				p3.x = p2.x - largeur; p3.y = p2.y;
				p4.x = p1.x - largeur; p4.y = p1.y;

			}
			
		}
		
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn bool getbuts(int index, glm::vec3 & pointHaut, glm::vec3 & pointMilieu, glm::vec3 & pointBas)
///
/// Cette fonction permet de recuperer les coordonnes des buts
///  @param[in] 
///		int index : 1 pour le but de droite, 2 pour celui du gauche
///	 @param[out]
///		pointHaut : le point haut de la ligne du but
///		pointMilieu : le point milieu du but
///		pointBas : point bas de la ligne du but
/// @return bool : true s'il a reussi a trouver les coordonnees , false sinon
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoeudTable::getButs(int index, glm::vec3 & pointHaut, glm::vec3 & pointMilieu, glm::vec3 & pointBas) 
{
	glm::vec3 point1, point2, point3, point4;
	if (index == 2) // but a gauche
	{
		calculerPointDistance(p(0), p(6), longueurButs_, largeur_, point2, point3, point4);
		pointHaut = point2;
		pointMilieu = p(6);
		calculerPointDistance(p(1), p(6), longueurButs_, largeur_, point2, point3, point4);
		pointBas = point2;

		return true;
	}
	else 
	{
		if (index == 1) // but a droite
		{	
			calculerPointDistance(p(4), p(7), longueurButs_, largeur_, point2, point3, point4);
			pointHaut = point2;
			pointMilieu = p(7);
			calculerPointDistance(p(5), p(7), longueurButs_, largeur_, point2, point3, point4);
			pointBas = point2;
			return true;
		}
		else
			return false;
	}	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerButs(const glm::mat4& vueProjection, double longueur) const
///
/// @param[in]  vueProjection
///				longueur: la longueur du but
//
/// Cette fonction trace les but avec une  longueur fixe! 
///
/// version1
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::tracerButs(const glm::mat4& vueProjection, double longueur) const
{
	glm::vec3 point1, point2, point3, point4, point5;
	//glColor4f(couleurButs_[0], couleurButs_[1], couleurButs_[2], couleurButs_[3]);
	//Luc : les nuanceurs ne permettent qu'une couleur par set de points envoyés
	vbo_->programme_.assignerUniforme("colorIn", glm::vec4(0.f, 0.f, 1.f, 0.f)); //vert
	glBegin(GL_QUADS);
	//glPointSize(5);
	//glBegin(GL_POINTS);
	{
		//1er but
		point1 = p(6);
		calculerPointDistance(p(0), p(6), longueur, largeur_, point2, point3, point4);
		// 1er morceau P6P0
		glVertex3fv(PROJvec(glm::vec3(point1.x + delta , point1.y, point1.z)));
		glVertex3fv(PROJvec(glm::vec3(point2.x + delta , point2.y, point2.z)));
		glVertex3fv(PROJvec(glm::vec3(point3.x - delta, point3.y, point3.z)));
		glVertex3fv(PROJvec(glm::vec3(point4.x - delta, point4.y, point4.z)));
		// 2eme morceau P1P6
		calculerPointDistance(p(1), p(6), longueur, largeur_, point2, point3, point4);
		glVertex3fv(PROJvec(glm::vec3(point1.x + delta, point1.y, point1.z)));
		glVertex3fv(PROJvec(glm::vec3(point4.x - delta, point4.y, point4.z)));
		glVertex3fv(PROJvec(glm::vec3(point3.x - delta, point3.y, point3.z)));
		glVertex3fv(PROJvec(glm::vec3(point2.x + delta, point2.y, point2.z)));
	
		//2eme but
		point1 = p(7);
		// 1ere morceau P7P4
		calculerPointDistance(p(4), p(7), longueur, largeur_, point2, point3, point4);
		glVertex3fv(PROJvec(glm::vec3(point1.x - delta, point1.y, point1.z)));
		glVertex3fv(PROJvec(glm::vec3(point4.x + delta + 2 * largeur_, point4.y, point4.z)));
		glVertex3fv(PROJvec(glm::vec3(point3.x + delta + 2*largeur_, point3.y, point3.z)));
		glVertex3fv(PROJvec(glm::vec3(point2.x - delta, point2.y, point2.z)));
		//2eme morceau 
		calculerPointDistance(p(5), p(7), longueur, largeur_, point2, point3, point4);
		glVertex3fv(PROJvec(glm::vec3(point1.x - delta, point1.y, point1.z)));
		glVertex3fv(PROJvec(glm::vec3(point2.x - delta, point2.y, point2.z)));
		glVertex3fv(PROJvec(glm::vec3(point3.x + delta + 2 * largeur_, point3.y, point3.z)));
		glVertex3fv(PROJvec(glm::vec3(point4.x + delta + 2 * largeur_, point4.y, point4.z)));
	}
	glEnd();
#undef Delta
#undef delta 

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::tracerCercle(const glm::mat4& vueProjection,float cx, float cy, float r, int nb_segments)
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
void NoeudTable::tracerCercle(const glm::mat4& vueProjection,double cx, double cy, double r, int nb_segments) const
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < nb_segments; ii++)
	{
		double theta = 2.0f * 3.1415926f * double(ii) / double(nb_segments); //l'angle courant
		double x = r * cosf(theta);
		double y = r * sinf(theta);
		glm::vec3 point{ x + cx, y + cy, 0 };
		glVertex2f(vecPROJvec(point).x, vecPROJvec(point).y);
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
	else
	{
		if (numero == 8)
			pointControle = obtenirPositionRelative();
		else
			pointControle = pointControle_[numero];
		//std::cout << "pointControle[" << numero << "]" << "= (" << pointControle[0] << "," << pointControle[1] << "," << pointControle[2] << ")" << std::endl;
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
		if (numero = 8)
			pointControle_[numero] = obtenirPositionRelative();
		else
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
		//std::cout << "enfant n" << i << "\t" <<p(i).x << "\t" << p(i).y  << "\t" << p(i).z << "\n";
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


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::dansTable(glm::dvec3 M
///
/// Cette fonction permet de savoir si un point est dans la table
///  @param[in] 
///		point M
/// @return bool
///
////////////////////////////////////////////////////////////////////////
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
	bool result =  utilitaire::MdansTriangleABC(p8, p(0), p(2), M)
		|| utilitaire::MdansTriangleABC(p8, p(2), p(4), M)
		|| utilitaire::MdansTriangleABC(p8, p(4), p(7), M)
		|| utilitaire::MdansTriangleABC(p8, p(7), p(5), M)
		|| utilitaire::MdansTriangleABC(p8, p(5), p(3), M)
		|| utilitaire::MdansTriangleABC(p8, p(3), p(1), M)
		|| utilitaire::MdansTriangleABC(p8, p(1), p(6), M)
		|| utilitaire::MdansTriangleABC(p8, p(6), p(0), M);
	//std::cout << "\nresult " << (result? "dans" : "hors") << "\n";
	return result;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::dansZone1(glm::dvec3 M
///
/// Cette fonction permet de savoir si un point est dans la zone1
/// (zone gauche de la table)
///  @param[in] 
///		point M
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::dansZone1(glm::dvec3 M)
{
	/*
	etapes du check :
	p0----------p2----------p4
	| \___  1	 |			 |
	|	2 \____  |			 |
	p6 ________\p8			 p7
	|  3  _____/ |			 |
	| ___/	4	 |			 |
	p1----------p3----------p5

	*/

	glm::vec3 p8(p(2).x, obtenirPositionRelative().y, obtenirPositionRelative().z);
	bool result = utilitaire::MdansTriangleABC(p8, p(0), p(2), M)
		|| utilitaire::MdansTriangleABC(p8, p(6), p(0), M)
		|| utilitaire::MdansTriangleABC(p8, p(1), p(6), M)
		|| utilitaire::MdansTriangleABC(p8, p(3), p(1), M);
		
	return result;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::dansZone2(glm::dvec3 M
///
/// Cette fonction permet de savoir si un point est dans la zone2
/// (zone droite)
///  @param[in] 
///		point M
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::dansZone2(glm::dvec3 M)
{
	/*
	etapes du check :
	p0----------p2----------p4
	|			 | 1    ___/ |
	|			 |  ___/  2  |
	p6			p8 /________ p7
	|			 |\____	  3  |
	|			 |  4  \____ |
	p1----------p3----------p5

	*/

	glm::vec3 p8(p(2).x, obtenirPositionRelative().y, obtenirPositionRelative().z);
	bool result = utilitaire::MdansTriangleABC(p8, p(2), p(4), M)
		|| utilitaire::MdansTriangleABC(p8, p(4), p(7), M)
		|| utilitaire::MdansTriangleABC(p8, p(7), p(5), M)
		|| utilitaire::MdansTriangleABC(p8, p(5), p(3), M);
	return result;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::mailletDansZone2(glm::dvec3 M,double rayon)
///
/// Cette fonction permet de savoir si un point est dans la zone2 
///  (zone droite) mais a une distance des murs
/// pour que le maillet ne depasse pas les murs
///  @param[in] 
///		point M
///		double rayon : rayon du maillet
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::mailletDansZone2(glm::dvec3 M,double rayon) 
{
	if (dansZone2(M))
	{
		double dist;
		//tester les distance entre le centre du maillet et les droites (murs) de la table
		dist = distanceEntrePointDroite(p(2), p(3), M);
		if (dist < rayon) // distance entre mur P2P3
			return false;

		else  // distance entre mur P2P4
		{
			dist = distanceEntrePointDroite(p(4), p(2), M);
			if (dist < rayon) 
			{
				if (p(4).y >= p(2).y) 
					return false;					
				else
					if (M.y >= p(4).y) 
						return false;
			}
				
			else // distance entre mur P4P7 			
			{
				dist = distanceEntrePointDroite(p(4), p(7), M);
				if ((dist < rayon) && (M.y >= p(7).y))
					if (p(4).x >= p(7).x)
						return false;
					else
						if (p(4).y > p(2).y)
							return false;
						else
						{
							glm::vec3 PI;
							intersection2Droites(p(2), p(3), p(4), p(7), PI);
							if (PI.y > p(2).y)
								return false;
						}
				else // distance entre mur P7P5					
				{
					dist = distanceEntrePointDroite(p(5), p(7), M);
					if ( (dist < rayon) && (M.y <= p(7).y) )
						if (p(5).x >= p(7).x)
							return false;
						else
							if (p(5).y < p(3).y)
								return false;
							else
							{
								glm::vec3 PI;
								intersection2Droites(p(2), p(3), p(5), p(7), PI);
								if (PI.y < p(3).y)
									return false;
							}
					
					else // distance entre mur P3P5
					{
						dist = distanceEntrePointDroite(p(5), p(3), M);
						if (dist < rayon) 
						{
							if (p(5).y <= p(3).y) 
								return false;
							else
								if (M.y < p(5).y) 
									return false;							
						}
						else
							return true;
					}
				}
			}
			

		}
			
		
	}
	else // pas dans la zone
		return false;
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::mailletDansZone1(glm::dvec3 M,double rayon)
///
/// Cette fonction permet de savoir si un point est dans la zone1 
///  (zone gauche) mais a une distance des murs 
/// pour que le maillet ne depasse pas les murs
/// utilise pour maillet touche et virtuel
///  @param[in] 
///		point M
///		double rayon : rayon du maillet
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::mailletDansZone1(glm::dvec3 M, double rayon)
{

	if (dansZone1(M))
	{
		double dist;
		//tester les distance entre le centre du maillet et les droites (murs) de la table
		dist = distanceEntrePointDroite(p(2), p(3), M);
		if (dist < rayon) // distance entre mur P2P3
			return false;

		else  // distance entre mur P2P0
		{
			dist = distanceEntrePointDroite(p(0), p(2), M);
			if (dist < rayon)
			{
				if (p(0).y >= p(2).y)
					return false;
				else
					if (M.y >= p(0).y)
						return false;
			}

			else // distance entre mur P0P6 			
			{
				dist = distanceEntrePointDroite(p(0), p(6), M);
				if ((dist < rayon) && (M.y >= p(6).y))
					if (p(0).x <= p(6).x)
						return false;
					else
						if (p(0).y >= p(2).y)
							return false;
						else
						{
							glm::vec3 PI;
							intersection2Droites(p(2), p(3), p(0), p(6), PI);
							if (PI.y > p(2).y)
								return false;
						}
				else // distance entre mur P6P1					
				{
					dist = distanceEntrePointDroite(p(6), p(1), M);
					if ((dist < rayon) && (M.y <= p(6).y))
						if (p(1).x <= p(6).x)
							return false;
						else
							if (p(1).y < p(3).y)
								return false;
							else
							{
								glm::vec3 PI;
								intersection2Droites(p(2), p(3), p(6), p(1), PI);
								if (PI.y < p(3).y)
									return false;
							}

					else // distance entre mur P3P1
					{
						dist = distanceEntrePointDroite(p(1), p(3), M);
						if (dist < rayon)
						{
							if (p(1).y <= p(3).y)
								return false;
							else
								if (M.y < p(1).y)
									return false;
						}
						else
							return true;
					}
				}
			}
		}
	}
	else // pas dans la zone
		return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudTable::distanceEntrePointDroite(glm::dvec3 P1, glm::dvec3 P2, glm::dvec3 P)
///
/// Cette fonction calcule la distance entre un point P et la droite (P1P2) forme' par les points P1 et P2
///  @param[in] 
///		glm::vec3 P1,P2,P 
///		
/// @return double
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double NoeudTable::distanceEntrePointDroite(glm::dvec3 P1, glm::dvec3 P2, glm::dvec3 P)
{
	double numer = (P2.y - P1.y)*P.x - (P2.x - P1.x)*P.y + P2.x*P1.y - P2.y*P1.x;
	//std::cout << "num = " << numer << std::endl;
	double denum = sqrt(pow((P2.y-P1.y), 2) + pow((P2.x-P1.x), 2));
	//std::cout << "denum = " << denum << std::endl;
	return  fabs(numer ) / (denum);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudTable::distanceEntre2Points(glm::dvec3 P1, glm::dvec3 P2)
///
/// Cette fonction calcule la distance entre 2 points P1 et P2
///  @param[in] 
///		glm::vec3 P1,P2 
///		
/// @return double
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double NoeudTable::distanceEntre2Points(glm::dvec3 P1, glm::dvec3 P2)
{
	return sqrt(pow((P2.y - P1.y), 2) + pow((P2.x - P1.x), 2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::intersection2Droites(glm::vec3 D1P1, glm::vec3 D1P2, glm::vec3 D2P1, glm::vec3 D2P2, glm::vec3 & pointIntersection)
///
/// Cette fonction permet de trouve le point d'intersection entre 2 droites
///
///  @param[in] 
///		glm::vec3 D1P1,D1P2,D2P1,D2P2 : les points qui forment les 2 droites 
///	 @param[out] : glm::vec3 pointIntersection : les coord. du point d'intersection
/// @return bool : true si s'intersectent , false paralleles
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoeudTable::intersection2Droites(glm::vec3 D1P1, glm::vec3 D1P2, glm::vec3 D2P1, glm::vec3 D2P2, glm::vec3 & pointIntersection) //const
{
	float a1 = calculPente(D1P1, D1P2);
	float b1 = calculB(a1, D1P1);

	//std::cout << "P1(" << D1P1.x << "," << D1P1.y << ") P2(" << D1P2.x << "," << D1P2.y << ")" << std::endl;
	//std::cout << "a1=" << a1 << " b1=" << b1 << std::endl;
	
	float a2 = calculPente(D2P1, D2P2);
	float b2 = calculB(a2, D2P1);

	//std::cout << "P1(" << D2P1.x << "," << D2P1.y << ") P2(" << D2P2.x << "," << D2P2.y << ")" << std::endl;
	//std::cout << "a2=" << a2 << " b2=" << b2 << std::endl;

	if (D1P1.x == D1P2.x)  // mon cas -- TODO les autres cas
	{
		pointIntersection.y = a2*D1P1.x + b2;
		pointIntersection.x = D1P1.x;
		return true;
	}
	
	if ((a1 - a2) == 0)
		return false;
	else
	{
		
		pointIntersection.x = (b2 - b1) / (a1 - a2);
		pointIntersection.y = a1*pointIntersection.x + b1;
		//std::cout << "PointIntersection(" << pointIntersection.x << "," << pointIntersection.y << ")" << std::endl;
		return true;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::appartientDroite(glm::dvec3 point, glm::dvec3 D1P1, glm::dvec3 D1P2)
///
/// Cette fonction permet de savoir si un tel point appartient a la droite
///
///  @param[in] 
///		glm::vec3 D1P1,D1P2 : les points qui forment la droite
///		glm::vec3 point : le point a verifier
///		
/// @return bool
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool NoeudTable::appartientDroite( glm::dvec3 D1P1, glm::dvec3 D1P2, glm::dvec3 point)
{
	if (distanceEntrePointDroite(D1P1, D1P2, point) == 0)
		return true;
	else
		return false;
}