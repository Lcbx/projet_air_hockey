///////////////////////////////////////////////////////////////////////////
/// @file SkyBox.h
/// @author Luc Courbariaux
/// @date 2016-11-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#pragma once


#include "NoeudAbstrait.h"
#include "../Utilitaire/OpenGL/BoiteEnvironnement.h"


///////////////////////////////////////////////////////////////////////////
/// @class SkyBox
/// @brief Classe qui représente le noeud de la skybox.
///
/// @author Luc Courbariaux
/// @date 2016-11-14
///////////////////////////////////////////////////////////////////////////
class SkyBox : public NoeudAbstrait
{
	///la boite d'environnement sous-jacente, tirée du namespace utilitaire
	mutable utilitaire::BoiteEnvironnement boite_{ 
		"media/TropicalSunnyDay/TropicalSunnyDayLeft2048.png",
		"media/TropicalSunnyDay/TropicalSunnyDayRight2048.png",
		"media/TropicalSunnyDay/TropicalSunnyDayUp2048.png",
		"media/TropicalSunnyDay/TropicalSunnyDayDown2048.png",
		"media/TropicalSunnyDay/TropicalSunnyDayFront2048.png",
		"media/TropicalSunnyDay/TropicalSunnyDayBack2048.png",
		2048 };
public:

	/// Ce constructeur crait un noeud héritant de la classe noeudAbstrait
	SkyBox();

	/// Ce destructeur appelle les destructeurs de noeudAbstrait et BoiteEnvironnement
	//~SkyBox();

	/// Cette fonction affiche tout simplement la boîte d'environnement.
	virtual void afficherConcret(const glm::mat4& modele, const glm::mat4& vue, const glm::mat4& projectionn) const;
	
	/// Cette fonction ne fait rien (pas d'animation de la boite d'environnment)
	//virtual void animer(float temps);

	/// Cette fonction ne fait rien (pas de traitement sur la boite d'environnment)
	virtual void accepter(Visiteur* v);
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
