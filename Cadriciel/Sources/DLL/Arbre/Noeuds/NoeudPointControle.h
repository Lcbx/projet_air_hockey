//////////////////////
/////////////////////////////////////////////////////
/// @file NoeudPointControle.h
/// @date 2016
/// @version 1.0
///
/// @addtogroup inf2990-10
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPOINTCONTROLE_H__
#define __ARBRE_NOEUDS_NOEUDPOINTCONTROLE_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudPointControle
/// @brief Classe qui représente un le noeud point de control de la table
///
/// author : inf2990-10
/// @date 2016
///////////////////////////////////////////////////////////////////////////
class NoeudPointControle : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudPointControle(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPointControle();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& vueProjection) const;

	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	
	//Accepter le visiteur
	virtual void accepter(Visiteur* v);

	// fonctions get et set de la couleur du point
	bool setCouleur(glm::vec4 couleur);
	bool getCouleur(glm::vec4 & couleur);

private:
	// la couleur du point de controle
	glm::vec4 couleur_{ 0.,0.,1.,0. }; // couleur bleu par default
	// la longueur du cote' du carre' du point de controle
	double delta_{ 0.05 };
};


#endif // __ARBRE_NOEUDS_NOEUDPOINTCONTROLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


