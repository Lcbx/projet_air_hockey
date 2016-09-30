///////////////////////////////////////////////////////////////////////////
/// @file NoeudBonus.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBONUS_H__
#define __ARBRE_NOEUDS_NOEUDBONUS_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBonus
/// @brief Classe qui repr�sente le noeud bonus de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudBonus : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudBonus(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudBonus();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& vueProjection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);


	//Accepter le visiteur
	virtual void accepter(Visiteur* v);
	
};


#endif // __ARBRE_NOEUDS_NOEUDBONUS_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


