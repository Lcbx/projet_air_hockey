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
	/// Constructeur de la cam�ra � partir des coordonn�es cart�siennes.
	///
	/// @param[in]  position            : position de la cam�ra.
	/// @param[in]  pointVise           : point vis�.
	/// @param[in]  directionHautCamera : direction du haut de la cam�ra.
	/// @param[in]  directionHautMonde  : direction du haut du monde de la
	///                                   cam�ra.
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
	/// D�place la cam�ra dans le plan perpendiculaire � la direction vis�e
	///
	/// @param[in]  deplacementX : D�placement sur l'axe horizontal du plan de
	///                            la cam�ra.
	/// @param[in]  deplacementY : D�placement sur l'axe vertical du plan de la
	///                            cam�ra.
	/// @param[in]  bougePointVise : Si vrai, le point de vis� est �galement
	///                              d�plac�.
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
	/// D�place la cam�ra dans l'axe de la direction vis�e.
	///
	/// @param[in]  deplacement    : D�placement sur l'axe de la direction vis�e
	/// @param[in]  bougePointVise : Si vrai, le point de vis� est �galement
	///                              d�plac�.
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
	/// Rotation de la cam�ra autour de sa position (et donc d�placement du
	/// point vis� en gardant la position fixe.
	///
	/// @param[in] rotationX        : Modification de l'angle de rotation du
	///                               point vis� par rapport � la position.
	/// @param[in] rotationY        : Modification de l'angle d'�l�vation du
	///                               point vis� par rapport � la position.
	/// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectu�e
	///                               si elle am�nerait une inversion de la
	///                               cam�ra.
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
	/// Rotation de la cam�ra autour de son point de vis� (et donc d�placement
	/// de la position en gardant le point de vis� fixe.
	///
	/// @param[in]  rotationX        : Modification de l'angle de rotation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  rotationY        : Modification de l'angle d'�l�vation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectu�
	///                                si elle am�nerait une inversion de la
	///                                cam�ra.
	///
	///  @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::orbiterXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{

		// Se replace par rapport � la position de base
		position_ = positionDef_;

		// Calcul du nouvel angle d'�l�vation
		if (_angleElev - rotationY < 90 * 0.03)
			_angleElev = 90 * 0.03;
		else if (_angleElev - rotationY > 90 * 0.99)
			_angleElev = 90 * 0.99;
		else
			_angleElev -= rotationY;

		double angleElevRad = _angleElev * PI / 180;

		// Application du nouvel angle d'�l�vation
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

		//  -- FAIT ACTUELLEMENT UNE ROTATION AUTOUR DE X, DOIT ETRE CORRIG� --
		//position_[1] = ((position_[1] - pointVise_[1])*cos(rotationY)) - ((position_[2] - pointVise_[2])*sin(rotationY)) + pointVise_[1];
		//position_[2] = ((position_[1] - pointVise_[1])*sin(rotationY)) + ((position_[2] - pointVise_[2])*cos(rotationY)) + pointVise_[2];

		//position_[1] = ((position_[1])*cos(rotationY)) - ((position_[2])*sin(rotationY));
		//position_[2] = ((position_[1])*sin(rotationY)) + ((position_[2])*cos(rotationY));
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::mat4 Camera::obtenirMatrice() const
	///
	/// Calcule la matrice aidant � positionner la cam�ra dans la sc�ne.
	///
	/// @return Matrice de la cam�ra.
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
