///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
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
/// @brief Classe qui représente un le noeud bonus de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
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
	void tracerTable(glm::vec4 couleurTable, glm::vec4 couleurFrontiere, glm::vec4 couleurControle) const;
	// trace un cercle
	void DrawCircle(float cx, float cy, float r, int num_segments) const;

	// pas complet
	// tracer les points de controle
	void tracerPointControle(glm::vec3 point, glm::vec4 couleur);
	//tracer les murs autour de la table
	void tracerMurs();
	
private:
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };

	// la couleur de la table 
	glm::vec4 couleurTable_ = { 1., 1., 1., 1. };
	// couleur frontiere
	glm::vec4 couleurFrontiere_ = { 0.662745, 0.662745, 0.662745, 1.};
	// les 8 points de controle de la table
	//glm::vec3 pointControle_[8] = { {-.8,.8,0}, {-.8,-.8,0}, {0,.8,0}, {0,-.8,0}, {.8,.8,0}, {.8,-.8,0}, {-.8,0,0}, {.8,0,0} };
	glm::vec3 pointControle_[8] = { { -.8,.8,0 },{ -.8,-.8,0 },{ 0,.8,0 },{ 0,-.8,0 },{ .8,.8,0 },{ .8,-.8,0 },{ -.8,0,0 },{ .8,0,0 } };
	// la couleur des points de controle
	glm::vec4 couleurControle_;
	//// les murs autour de la Table
	//NoeudMuret muret_[6];

};


#endif // __ARBRE_NOEUDS_NOEUDTABLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


