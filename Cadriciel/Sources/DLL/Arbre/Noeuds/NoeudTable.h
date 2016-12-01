///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.h
/// @author Ali
/// @date september 2016
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDTABLE_H__
#define __ARBRE_NOEUDS_NOEUDTABLE_H__


#include "NoeudComposite.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudTable
/// @brief Classe qui représente un le noeud table de l'arbre de rendu.
///
/// @author equipe 10
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudTable : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudTable(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudTable();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& modele, const glm::mat4& vue, const glm::mat4& projection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	///Accepter le visiteur
	virtual void accepter(Visiteur* v);

	// fonctions d'affichage
	/// tracer la table
	void tracerTable(const glm::mat4& vueProjection)  const;
	///si on doit tracer les points de controle
	bool afficherPointsControles = true;
	/// tracer les points de controle
	void tracerPointsControle(const glm::mat4& vueProjection)  const;
	/// tracer un cercle
	void tracerCercle(const glm::mat4& vueProjection,double cx, double cy, double r, int nb_segments) const;
	/// tracer les murs
	void tracerMurs(const glm::mat4& vueProjection) const;
	///tracer un mur entre 2 points
	void tracerMur2Points(const glm::mat4& vueProjection, glm::vec3 p1, glm::vec3 p2, double largeur,bool direction) const;
	///tracer les murs entre 3 points
	void tracerMurs3Points(const glm::mat4& vueProjection,glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) const; 
	///tracer les buts
	void tracerButs(const glm::mat4& vueProjection) const;
	///tracer les buts en fonction de la longueur
	void tracerButs(const glm::mat4& vueProjection, double longueur) const;
	///calcule la distance entre des points
	void calculerPointDistance(glm::vec3 p0, glm::vec3 p1, double longueur, double largeur, glm::vec3 & p2, glm::vec3 & p3, glm::vec3 & p4) const;
	///tracer les lignes decoratives
	void tracerLignesDecoration (const glm::mat4& vueProjection) const;

	/// Calcul la pente de la droite faite par 2 points 
	double calculPente(glm::vec3 P0, glm::vec3 P1) const;
	///calcul de point a partir de la pente
	double calculB(double pente, glm::vec3 P0) const;

	// fonctions get et set pour les points de controle de la table
	/// coordonnees point de controle
	bool getPointControle(int numero, glm::vec3 & pointControle);
	bool setPointControle(int numero, glm::vec3 pointControle);
	bool setPointControles();
	///couleur de la table
	bool getCouleurTable(glm::vec4 & couleur);
	bool setCouleurTable(glm::vec4 couleur);
	/// couleur des murs
	bool getCouleurMurs(glm::vec4 & couleur);
	bool setCouleurMurs(glm::vec4 couleur);
	/// couleur des buts
	bool getCouleurButs(glm::vec4 & couleur);
	bool setCouleurButs(glm::vec4 couleur);
	/// couleur des lignes dans la zone du jeu
	bool getCouleurLignes(glm::vec4 & couleur);
	bool setCouleurLignes(glm::vec4 couleur);
	/// couleur du contour autour de la zone du jeu
	bool getCouleurContour(glm::vec4 & couleur);
	bool setCouleurContour(glm::vec4 couleur);


	///determiner si dans la table
	bool dansTable(glm::dvec3 M);
	/// dans la zone du jeu 
	bool dansZone1(glm::dvec3 M);
	bool dansZone2(glm::dvec3 M);
	/// maillet dans la zone du jeu
	bool mailletDansZone1(glm::dvec3 M, double rayon);
	bool mailletDansZone2(glm::dvec3 M, double rayon);
	/// distance entre un point et une droite
	double distanceEntrePointDroite(glm::dvec3 P1, glm::dvec3 P2, glm::dvec3 P);
	
	/// distance entre 2 pts 
	double distanceEntre2Points(glm::dvec3 P1, glm::dvec3 P2);
	/// point d'intersection entre 2 droites
	bool intersection2Droites(glm::vec3 D1P1, glm::vec3 D1P2, glm::vec3 D2P1, glm::vec3 D2P2, glm::vec3 & pointIntersection); // const;
	/// point appartient a une droite
	bool appartientDroite( glm::dvec3 D1P1, glm::dvec3 D1P2, glm::dvec3 point );
	/// get coordonnes des buts 
	bool getButs(int index, glm::vec3 & pointHaut, glm::vec3 & pointMilieu, glm::vec3 & pointBas);

	glm::vec3 getPc(int i) { return pointControle_[i]; }
	void tracerMur3D(const glm::mat4& vueProjection, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4,float hauteur) const;

private:

	///la largueur des murs 
	double largeur_{ 7 };
	double longueurButs_{ 20 };
	//Livrable 3
	double hauteurMur_{ 20 };
	double hauteurBut_{ 10 };
	/// la hauteur des murs 
	double hauteur_{ 0.0 };
	/// la couleur de la table 
	glm::vec4 couleurTable_ = { 1.f, 1.f, 1.f, 0.f };
	/// la couleur des murs autour de la table
	glm::vec4 couleurMurs_ = { 0.662745f, 0.662745f, 0.662745f, 1.f };
	/// la couleur des 2 buts 
	glm::vec4 couleurButs_{ 1.f,1.f,0.f,0.f };
	/// la couleur des lignes sur le terrain
	glm::vec4 couleurLignes_{ 1.f,0.f,0.f,0.f };
	/// la couleur du contour
	glm::vec4 couleurContour_{ 1.f,0.f,0.f,0.f };

	// les 8 points de controle de la table
	/*
	p0----------p2----------p4
	|						 |
	|						 |
	p6			p8			p7
	|						 |
	|						 |
	p1----------p3----------p5

	*/

	///pour obtenir p0, p1, ... des points de controle
	glm::vec3 p(int i) const { return chercher(i)->obtenirPositionRelative(); }

	///table d'initialisation des points de controle
	glm::vec3 pointControle_[8] = { 
		{  -85,   75,  -0 },	//P0
		{  -85,  -75,  -0 },	//P1
		{  0.,    75,  -0 },	//P2
		{  0.,   -75,  -0 },	//P3
		{  85,    75,  -0 },	//P4
		{  85,   -75,  -0 },	//P5
		{ -85,   0.,   -0 },	//P6
		{  85,   0.,   -0 }		//P7 
	};

};


#endif // __ARBRE_NOEUDS_NOEUDTABLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


