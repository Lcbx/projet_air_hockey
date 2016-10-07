///////////////////////////////////////////////////////////////////////////
/// @file NoeudRondelle.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDRONDELLE_H__
#define __ARBRE_NOEUDS_NOEUDRONDELLE_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudRondelle
/// @brief Classe qui repr�sente un le noeud muret de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudRondelle : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudRondelle(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRondelle();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& vueProjection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);


	///Accepter le visiteur
	virtual void accepter(Visiteur* v);

private:


	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };

};


#endif // __ARBRE_NOEUDS_NOEUDMURET_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////