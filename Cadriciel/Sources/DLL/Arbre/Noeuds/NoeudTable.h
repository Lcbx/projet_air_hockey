///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.h
/// @author equipe10
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
	virtual void afficherConcret(const glm::mat4& vueProjection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	//Accepter le visiteur
	virtual void accepter(Visiteur* v);

	// fonctions d'affichage
	void tracerTable(const glm::mat4& vueProjection)  const; // tracer la table
	void tracerPointsControle(const glm::mat4& vueProjection)  const; // tracer les points de Controle
	void tracerCercle(const glm::mat4& vueProjection,double cx, double cy, double r, int nb_segments) const; // tracer la table
	void tracerMurs(const glm::mat4& vueProjection) const; //tracer les murs autour de la table
	//tracer un mur entre 2 points
	void tracerMur2Points(const glm::mat4& vueProjection, glm::vec3 p1, glm::vec3 p2, double largeur,bool direction) const;
	//tracer les murs entre 3 points
	void tracerMurs3Points(const glm::mat4& vueProjection,glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) const; 
	//tracer les buts
	void tracerButs(const glm::mat4& vueProjection) const;
	void tracerButs(const glm::mat4& vueProjection, double longueur) const;
	void tracerLignesDecoration (const glm::mat4& vueProjection) const; //tracer les lignes de decoration

	// Calcul la pente de la droite faite par 2 points 
	double calculPente(glm::vec3 P0, glm::vec3 P1) const;
	double calculB(double pente, glm::vec3 P0) const;

	// fonctions get et set pour les points de controle de la table
	// coordonnees point de controle
	bool getPointControle(int numero, glm::vec3 & pointControle);
	bool setPointControle(int numero, glm::vec3 pointControle);
	bool setPointControles();
	// couleur de la table
	bool getCouleurTable(glm::vec4 & couleur);
	bool setCouleurTable(glm::vec4 couleur);
	// couleur des murs
	bool getCouleurMurs(glm::vec4 & couleur);
	bool setCouleurMurs(glm::vec4 couleur);
	// couleur des buts
	bool getCouleurButs(glm::vec4 & couleur);
	bool setCouleurButs(glm::vec4 couleur);
	// couleur des lignes dans la zone du jeu
	bool getCouleurLignes(glm::vec4 & couleur);
	bool setCouleurLignes(glm::vec4 couleur);
	// couleur du contour autour de la zone du jeu
	bool getCouleurContour(glm::vec4 & couleur);
	bool setCouleurContour(glm::vec4 couleur);


	//determiner si dans la table
	/// angle
	double calculerAngle3D(glm::dvec3 A, glm::dvec3 B, glm::dvec3 C);
	double calculerAngle2D(glm::dvec3 A, glm::dvec3 B, glm::dvec3 C);
	/// dansTriangle
	bool MdansTriangleABC(glm::dvec3 A, glm::dvec3 B, glm::dvec3 C, glm::dvec3 M);
	/// dansTable
	bool dansTable(glm::dvec3 M);

private:

	//la largueur des murs 
	double largeur_{ 7 };
	// la hauteur des murs 
	double hauteur_{ 0.0 };
	// la couleur de la table 
	glm::vec4 couleurTable_ = { 1., 1., 1., 1. };
	// la couleur des murs autour de la table
	glm::vec4 couleurMurs_ = { 0.662745, 0.662745, 0.662745, 1. };
	// la couleur des 2 buts 
	glm::vec4 couleurButs_{ 1.,1.,0.,1. };
	// la couleur des lignes sur le terrain
	glm::vec4 couleurLignes_{ 1.,0.,0.,1. };
	// la couleur du contour
	glm::vec4 couleurContour_{ 1.,0.,0.,1. };

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

	//pour obtenir p0, p1, ... des points de controle
	glm::vec3 p(int i) const { return chercher(i)->obtenirPositionRelative(); }

	glm::vec3 pointControle_[8] = { 
		{  -50,   50,  -0 },	//P0
		{  -50,  -50,  -0 },	//P1
		{  0.,    50,  -0 },	//P2
		{  0.,   -50,  -0 },	//P3
		{  50,    50,  -0 },	//P4
		{  50,   -50,  -0 },	//P5
		{ -50,   0.,   -0 },	//P6
		{  50,   0.,   -0 }		//P7
	};

};


#endif // __ARBRE_NOEUDS_NOEUDTABLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


