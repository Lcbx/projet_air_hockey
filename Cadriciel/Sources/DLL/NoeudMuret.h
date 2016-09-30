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
/// @brief Classe qui repr�sente un le noeud muret de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudMuret : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudMuret(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudMuret();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& vueProjection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);

	//Accepter le visiteur
	virtual void accepter(Visiteur* v);

	///Permet d'obtenir la boite de collision pour le muret donn�
	//virtual BoiteCollision obtenirBoiteCollision();

	///Permet d'obtenir la droite directrice du muret
	virtual math::Droite3D obtenirDroiteDirectrice();

	///Permet d'obtenir le rayon du mod�le du muret
	virtual double obtenirRayonModele();
	
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

