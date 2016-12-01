///////////////////////////////////////////////////////////////////////////////
/// @file Camera.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "Utilitaire.h"
#include "Camera.h"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>

#define PI   3.14159265358979323846264338327950288

namespace vue {


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn Camera::Camera(const glm::dvec3& position, const glm::dvec3& pointVise, const glm::dvec3& directionHautCamera, const glm::dvec3& directionHautMonde)
	///
	/// Constructeur de la caméra à partir des coordonnées cartésiennes.
	///
	/// @param[in]  position            : position de la caméra.
	/// @param[in]  pointVise           : point visé.
	/// @param[in]  directionHautCamera : direction du haut de la caméra.
	/// @param[in]  directionHautMonde  : direction du haut du monde de la
	///                                   caméra.
	///
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////////
	Camera::Camera(const glm::dvec3& position,
		const glm::dvec3& pointVise,
		const glm::dvec3& directionHautCamera,
		const glm::dvec3& directionHautMonde
		)
		: position_{ position },
		pointVise_{ pointVise },
		directionHaut_{ directionHautCamera },
		directionHautMonde_{ directionHautMonde }
	{
		positionDef_ = position_;
		_angleRota = 180;
		_angleElev = 45;
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerXY( double deplacementX, double deplacementY )
	///
	/// Déplace la caméra dans le plan perpendiculaire à la direction visée
	///
	/// @param[in]  deplacementX : Déplacement sur l'axe horizontal du plan de
	///                            la caméra.
	/// @param[in]  deplacementY : Déplacement sur l'axe vertical du plan de la
	///                            caméra.
	/// @param[in]  bougePointVise : Si vrai, le point de visé est également
	///                              déplacé.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerXY(double deplacementX, double deplacementY, bool bougePointVise)
	{
		position_[0] += deplacementX;
		position_[1] += deplacementY;
		if (bougePointVise) {
		//	std::cout << pointVise_[0] << " " << pointVise_[1] << std::endl;
			pointVise_[0] += deplacementX;
			pointVise_[1] += deplacementY;
			//std::cout << pointVise_[0] << " " << pointVise_[1] << std::endl;
		}
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerZ( double deplacement, bool bougePointVise )
	///
	/// Déplace la caméra dans l'axe de la direction visée.
	///
	/// @param[in]  deplacement    : Déplacement sur l'axe de la direction visée
	/// @param[in]  bougePointVise : Si vrai, le point de visé est également
	///                              déplacé.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerZ(double deplacement, bool bougePointVise)
	{
		position_[2] += deplacement;
		if (bougePointVise)pointVise_[2] += deplacement;
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::tournerXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la caméra autour de sa position (et donc déplacement du
	/// point visé en gardant la position fixe.
	///
	/// @param[in] rotationX        : Modification de l'angle de rotation du
	///                               point visé par rapport à la position.
	/// @param[in] rotationY        : Modification de l'angle d'élévation du
	///                               point visé par rapport à la position.
	/// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectuée
	///                               si elle amènerait une inversion de la
	///                               caméra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::tournerXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{
		//TODO TODO TODO ST-TROPEZ
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::orbiterXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la caméra autour de son point de visé (et donc déplacement
	/// de la position en gardant le point de visé fixe.
	///
	/// @param[in]  rotationX        : Modification de l'angle de rotation de la
	///                                position par rapport au point de visé.
	/// @param[in]  rotationY        : Modification de l'angle d'élévation de la
	///                                position par rapport au point de visé.
	/// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectué
	///                                si elle amènerait une inversion de la
	///                                caméra.
	///
	///  @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::orbiterXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{

		// Se replace par rapport à la position de base
		position_ = positionDef_;

		// Calcul du nouvel angle d'élévation
		if (_angleElev - rotationY < 90 * 0.03)
			_angleElev = 90 * 0.03;
		else if (_angleElev - rotationY > 90 * 0.99)
			_angleElev = 90 * 0.99;
		else
			_angleElev -= rotationY;

		double angleElevRad = _angleElev * PI / 180;

		// Application du nouvel angle d'élévation
		position_[1] = ((position_[1])*cos(angleElevRad)) + ((position_[2])*sin(angleElevRad));
		position_[2] = ((position_[1])*sin(angleElevRad)) + ((position_[2])*cos(angleElevRad));

		// Calcul du nouvel angle de rotation
		_angleRota = fmod(_angleRota - rotationX, 360);

		double angleRotaRad = _angleRota * PI / 180;

		// Application du nouvel angle de rotation
		position_[0] = ((position_[0])*cos(angleRotaRad)) + ((position_[1])*sin(angleRotaRad));
		position_[1] = ((position_[0])*sin(angleRotaRad)) + ((position_[1])*cos(angleRotaRad));


		// Rotation autour de z
		//position_[0] = ((position_[0] - pointVise_[0])*cos(rotationX)) - ((position_[1] - pointVise_[1])*sin(rotationX)) + pointVise_[0];
		//position_[1] = ((position_[0] - pointVise_[0])*sin(rotationX)) + ((position_[1] - pointVise_[1])*cos(rotationX)) + pointVise_[1];

		//position_[0] = ((position_[0])*cos(rotationX)) - ((position_[1])*sin(rotationX));
		//position_[1] = ((position_[0])*sin(rotationX)) + ((position_[1])*cos(rotationX));

		//  -- FAIT ACTUELLEMENT UNE ROTATION AUTOUR DE X, DOIT ETRE CORRIGÉ --
		//position_[1] = ((position_[1] - pointVise_[1])*cos(rotationY)) - ((position_[2] - pointVise_[2])*sin(rotationY)) + pointVise_[1];
		//position_[2] = ((position_[1] - pointVise_[1])*sin(rotationY)) + ((position_[2] - pointVise_[2])*cos(rotationY)) + pointVise_[2];

		//position_[1] = ((position_[1])*cos(rotationY)) - ((position_[2])*sin(rotationY));
		//position_[2] = ((position_[1])*sin(rotationY)) + ((position_[2])*cos(rotationY));
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::mat4 Camera::obtenirMatrice() const
	///
	/// Calcule la matrice aidant à positionner la caméra dans la scène.
	///
	/// @return Matrice de la caméra.
	///
	////////////////////////////////////////////////////////////////////////
	glm::mat4 Camera::obtenirMatrice() const
	{
		return glm::lookAt(position_,pointVise_, directionHaut_);
	}


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
