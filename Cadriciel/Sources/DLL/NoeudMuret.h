///////////////////////////////////////////////////////////////////////////
/// @file NoeudMuret.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDMURET_H__
#define __ARBRE_NOEUDS_NOEUDMURET_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"
#include "BoiteCollision.h"



///////////////////////////////////////////////////////////////////////////
/// @class NoeudMuret
/// @brief Classe qui représente un le noeud muret de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudMuret : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudMuret(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudMuret();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& vueProjection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);

	//Accepter le visiteur
	virtual void accepter(Visiteur* v);

	///Permet d'obtenir la boite de collision pour le muret donné
	//virtual BoiteCollision obtenirBoiteCollision();

	///Permet d'obtenir la droite directrice du muret
	virtual math::Droite3D obtenirDroiteDirectrice();
		
	///Permet de changer le redimensionnement du muret
	virtual void setScale(const glm::dvec3& scale) {
		scale_ = { scale.x, 2.0, 2.0 };
	};

	///Permet d'obtenir le rayon minimal du modèle
	inline virtual double obtenirRayonModele() const;

private:
	
	/*
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
	*/
};


#endif // __ARBRE_NOEUDS_NOEUDMURET_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////