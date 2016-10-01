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
	void tracerTable()  const; // tracer la table
	void tracerCercle(double cx, double cy, double r, int nb_segments) const; // tracer la table
	void tracerMurs() const; //tracer les murs autour de la table
	void tracerButs() const; //tracer les buts
	// Calcul la pente de la droite faite par 2 points 
	double calculPente(glm::vec3 P0 , glm::vec3 P1);
	// fonctions get et set pour les points de controle de la table
	// coordonnees point de controle
	bool getPointControle(int numero, glm::vec3 & pointControle);
	bool setPointControle(int numero,glm::vec3 pointControle);
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
private:
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
	
	//la largueur des murs 
	double largeur_{ 0.1 };
	// la hauteur des murs 
	double hauteur_{ 0.0 };
	// la couleur de la table 
	glm::vec4 couleurTable_ = { 1., 1., 1., 1. };
	// la couleur des murs autour de la table
	glm::vec4 couleurMurs_ = { 0.662745, 0.662745, 0.662745, 1.};
	// la couleur des 2 buts 
	glm::vec4 couleurButs_{ 0.,0.,1.,1. };
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
	glm::vec3 pointControle_[8] = { 
		{ -.5,  .5,  -0.25 },	//P0
		{ -.5, -.5,  -0.25 },	//P1
		{  0.,  .5,  -0.25 },	//P2
		{  0., -.5,  -0.25 },	//P3
		{  .5,  .5,  -0.25 },	//P4
		{  .5, -.5,  -0.25 },	//P5
		{ -.5,  0.,  -0.25 },	//P6
		{  .5,  0.,  -0.25 }	//P7
	};

};


#endif // __ARBRE_NOEUDS_NOEUDTABLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


