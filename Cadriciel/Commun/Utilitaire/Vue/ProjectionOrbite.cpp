////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrbite.cpp
/// @author Arthur
/// @date 2016-11-24
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "ProjectionOrbite.h"
#include <glm/gtc/matrix_transform.inl>
#include <iostream>
#include "../../Sources/DLL/Application/FacadeModele.h"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrbite::ProjectionOrbite(int largeurCloture, int hauteurCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double largeurFenetre, double hauteurFenetre)
	///
	/// Constructeur d'une projection orbite.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] largeurCloture   : dimension en @a X de la clôture.
	/// @param[in] hauteurCloture   : dimension en @a Y de la clôture.
	/// @param[in] zAvant			: distance du plan avant (en @a z).
	/// @param[in] zArriere			: distance du plan arrière (en @a z).
	/// @param[in] zoomInMax		: facteur de zoom in maximal.
	/// @param[in] zoomOutMax		: facteur de zoom out maximal.
	/// @param[in] incrementZoom	: increment du facteur de zoom.
	/// @param[in] largeurFenetre	: dimension en @a X de la fenêtre
	///								  virtuelle.
	/// @param[in] hauteurFenetre	: dimension en @a Y de la fenêtre
	///								  virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionOrbite::ProjectionOrbite(int largeurCloture, int hauteurCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double largeurFenetre, double hauteurFenetre) :
		Projection{ largeurCloture, hauteurCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, false },
		largeurFenetre_{ largeurFenetre },
		hauteurFenetre_{ hauteurFenetre }
	{
		ajusterRapportAspect();
		zoomActuel_ = 1;
		largeurFenetreInit_ = largeurFenetre;
		hauteurFenetreInit_ = hauteurFenetre;
	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrbite::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrbite::zoomerIn()
	{
		zoomerIn(incrementZoom_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrbite::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incrément de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrbite::zoomerOut()
	{
		zoomerOut(incrementZoom_);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrbite::zoomerIn(double facteur)
	///
	/// Permet de faire un zoom in avec un incrément spécifié.
	/// 
	/// @param[in] facteur	: incrément du zoom
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrbite::zoomerIn(double facteur)
	{
		zoomerTo(zoomActuel_ + facteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrbite::zoomerOut(double facteur)
	///
	/// Permet de faire un zoom out avec un décrément spécifié.
	///
	/// @param[in] facteur	: décrément du zoom
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrbite::zoomerOut(double facteur)
	{
		zoomerTo(zoomActuel_ - facteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrbite::zoomerTo(double zoomFacteur)
	///
	/// Permet de zoomer jusqu'a un facteur donné.
	///
	/// @param[in] zoomFacteur	: facteur auquel zoomer
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrbite::zoomerTo(double zoomFacteur)
	{
		// Si le facteur de zoom est en dehors de l'intervalle possible, le mettre au point de l'intervalle le plus proche
		if (zoomFacteur > zoomInMax_) zoomFacteur = zoomInMax_;
		else if (zoomFacteur < zoomOutMax_) zoomFacteur = zoomOutMax_;

		zoomActuel_ = zoomFacteur;

		// Modifier la fenetre virtuelle pour produire l'effet de zoom
		largeurFenetre_ = largeurFenetreInit_ * (1 / zoomFacteur);
		hauteurFenetre_ = hauteurFenetreInit_ * (1 / zoomFacteur);


	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrbite::redimensionnerFenetre( double largeur, double hauteur )
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// L'agrandissement de la fenêtre virtuelle est proportionnel à
	/// l'agrandissement de la clotûre afin que les objets gardent la même
	/// grandeur apparente lorsque la fenêtre est redimensionnée.
	///
	/// @param[in]  largeur : largeur de la nouvelle clôture
	/// @param[in]  hauteur : hauteur de la nouvelle clôture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrbite::redimensionnerFenetre(int largeur, int hauteur)
	{
		//largeur = max(largeur, 100);
		//hauteur = max(hauteur, 100);

		{
			hauteurFenetre_ += (largeurFenetre_ / largeurCloture_)*hauteur - hauteurFenetre_;//calculer l'ajout à ajouter à la hauteur ancienne de la  fenêtre
			largeurFenetre_ += (largeurFenetre_ / largeurCloture_)*largeur - largeurFenetre_;////calculer l'ajout à ajouter à la largeur ancienne de la  fenêtre

			hauteurFenetreInit_ = hauteurFenetre_;
			largeurFenetreInit_ = largeurFenetre_;

			largeurCloture_ = largeur;// la cloture prend la nouvelle largeur 
			hauteurCloture_ = hauteur;// la cloture prend la nouvelle hauteur


			obtenirMatrice();//  redimensionner ma fenetre virtuelle avec les nouvelles valeurs (matrice de projection)
			ajusterRapportAspect();
		}

	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::mat4 ProjectionOrbite::obtenirMatrice() const
	///
	/// Cette fonction permet de retourner la fenêtre virtuelle en appelant les
	/// fonctions de glm selon le type de projection et les propriétés de la
	/// fenêtre.
	///
	/// @return Matrice de projection.
	///
	////////////////////////////////////////////////////////////////////////
	glm::mat4 ProjectionOrbite::obtenirMatrice() const
	{
		return glm::ortho(-largeurFenetre_ / 2, largeurFenetre_ / 2,
			-hauteurFenetre_ / 2, hauteurFenetre_ / 2,
			zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrbite::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// de la clôture de façon à ce que le rapport d'aspect soit respecté.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrbite::ajusterRapportAspect()
	{
		// À IMPLANTER.
		glMatrixMode(GL_PROJECTION); // La matrice courante est la matrice de projection
		glLoadIdentity();
		glViewport(0, 0, (GLsizei)(largeurCloture_), (GLsizei)(hauteurCloture_)); // ajuster ma cloture aux nouvelles dimensions
		glMatrixMode(GL_MODELVIEW);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double obtenirZoomActuel()
	///
	/// Cette fonction retourne le facteur de zoom actuel
	///
	/// @return l'attribut zoomActuel_
	///
	////////////////////////////////////////////////////////////////////////
	double ProjectionOrbite::obtenirZoomActuel()
	{
		return zoomActuel_;
	}

}; // Fin du namespace vue.


   ///////////////////////////////////////////////////////////////////////////
   /// @}
   ///////////////////////////////////////////////////////////////////////////
