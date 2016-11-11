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
/// @class NoeudPortail
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

	void tracerCercle(const glm::mat4& vueProjection, double cx, double cy, double r, int nb_segments) const;

	///Accepter le visiteur
	virtual void accepter(Visiteur* v);

	////////////////////////////////////////////////////////////////////////
	/// @fn double NoeudPortail::obtenirRayon()
	/// Permet d'obtenir le rayon de la forme en fonction du rayon du modèle
	/// @return Le rayon de l'objet
	////////////////////////////////////////////////////////////////////////
	virtual double obtenirRayon() const { return obtenirRayonModele() * getScale().x; };

	///pour l'attraction
	bool attracte_ = true;

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


