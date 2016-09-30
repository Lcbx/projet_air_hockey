///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPORTAIL_H__
#define __ARBRE_NOEUDS_NOEUDPORTAIL_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudMaillet
/// @brief Classe qui représente un le noeud Portail de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudPortail : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudPortail(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPortail();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& vueProjection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);


	//Accepter le visiteur
	virtual void accepter(Visiteur* v);

private:


	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
	


	
};


#endif // __ARBRE_NOEUDS_NOEUDPORTAIL_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


