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
/// @brief Classe qui représente un le noeud muret de l'arbre de rendu.
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
	virtual void afficherConcret(const glm::mat4& vueProjection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);


	///Accepter le visiteur
	virtual void accepter(Visiteur* v);

private:

	/*
	///dernieres positions valides
	std::list<glm::vec3> dernieresPositions_;
	///ajoute une nouvelle position
	void push_position();
	///charge une ancienne position
	void pop_position();
	*/


	///vecteur vitesse
	glm::vec3 vitesse_ = { 50,30,0 };
	
	///les portails : numero de noeud et active ou non
	std::map<NoeudPortail*, bool> portails_;

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