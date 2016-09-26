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
	// tracer la table
	void tracerTable(glm::vec4 couleurTable, glm::vec4 couleurMurs, glm::vec4 couleurButs)  const;
	// trace un cercle
	void NoeudTable::tracerCercle(float cx, float cy, float r, int nb_segments) const;
	//tracer les murs autour de la table
	void tracerMurs();
	//tracer les buts
	void tracerButs(float longueur);
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
	// couleurs des lignes
	bool getCouleurLignes(glm::vec4 & couleur);
	bool setCouleurLignes(glm::vec4 couleur);
private:
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
	
	// la couleur de la table 
	glm::vec4 couleurTable_ = { 1., 1., 1., 1. };
	// la couleur des murs autour de la table
	glm::vec4 couleurMurs_ = { 0.662745, 0.662745, 0.662745, 1.};
	// la couleur des 2 buts 
	glm::vec4 couleurButs_{ 0.,0.,1.,1. };
	// la couleur des lignes sur le terrain
	glm::vec4 couleurLignes_{ 1.,0.,0.,1. };
	// les 8 points de controle de la table
	glm::vec3 pointControle_[8] = { 
		{ -.8,  .8,  0. },	//P0
		{ -.8, -.8,  0. },	//P1
		{  0.,  .8,  0. },	//P2
		{  0., -.8,  0. },	//P3
		{  .8,  .8,  0. },	//P4
		{  .8, -.8,  0. },	//P5
		{ -.8,  0.,  0. },	//P6
		{  .8,  0.,  0. }	//P7
	};

};


#endif // __ARBRE_NOEUDS_NOEUDTABLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


