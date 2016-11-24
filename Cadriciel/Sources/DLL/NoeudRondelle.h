///////////////////////////////////////////////////////////////////////////
/// @file NoeudRondelle.h
/// @author Wajdi Gharsalli
/// @date 2016-10-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDRONDELLE_H__
#define __ARBRE_NOEUDS_NOEUDRONDELLE_H__


#include "NoeudAbstrait.h"
#include "NoeudPortail.h"
#include "GL/glew.h"
#include <list>
#include <map>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudRondelle
/// @brief Classe qui représente un la rondelle de l'arbre de rendu.
///
/// @author Wajdi Gharsalli
/// @date 2016-10-19
///////////////////////////////////////////////////////////////////////////
class NoeudRondelle : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudRondelle(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRondelle();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& modele, const glm::mat4& vue, const glm::mat4& projection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	///applique ue modification à la vitesse en fonction d'une collision avec un maillet
	void collisionMailletExterne(glm::vec3 vitesseMaillet, glm::vec3 normale);


	///Accepter le visiteur
	virtual void accepter(Visiteur* v);

private:

	///vecteur vitesse
	glm::vec3 vitesse_{0.1,0,0};
	
	///les portails : numero de noeud et active ou non
	//std::map<NoeudAbstrait*, bool> portails_;

	///si a deja ete affecte par un bonus
	bool affecteParBonus_ = false;

	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
};


#endif


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////