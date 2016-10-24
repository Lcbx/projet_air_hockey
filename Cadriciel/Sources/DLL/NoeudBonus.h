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
#include "BoiteCollision.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBonus
/// @brief Classe qui représente le noeud bonus de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudBonus : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudBonus(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudBonus();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& vueProjection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);


	///Accepter le visiteur
	virtual void accepter(Visiteur* v);

	/// Permet d'obtenir la droite directrice du noeud bonus
	math::Droite3D obtenirDroiteDirectrice();

	///permet d'obtenir la boite de collision du bonus
	virtual std::array<glm::vec3, 4> obtenirBoiteCollision();

	///Permet d'obtenir le rayon minimal du modèle
	inline virtual double obtenirRayonModele() const;
};


#endif // __ARBRE_NOEUDS_NOEUDBONUS_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


