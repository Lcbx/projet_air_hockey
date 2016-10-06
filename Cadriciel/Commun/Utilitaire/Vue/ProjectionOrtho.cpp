////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "ProjectionOrtho.h"
#include <glm/gtc/matrix_transform.inl>
#include <iostream>
#include "../../Sources/DLL/Application/FacadeModele.h"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int largeurCloture, int hauteurCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double largeurFenetre, double hauteurFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
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
	ProjectionOrtho::ProjectionOrtho(int largeurCloture, int hauteurCloture,
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
	/// @fn void ProjectionOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn()
	{
		zoomerIn(incrementZoom_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incrément de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut()
	{
		zoomerOut(incrementZoom_);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn(double facteur)
	///
	/// Permet de faire un zoom in avec un incrément spécifié.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn(double facteur)
	{
		zoomerTo(zoomActuel_ + facteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut(double facteur)
	///
	/// Permet de faire un zoom out avec un décrément spécifié.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut(double facteur)
	{
		zoomerTo(zoomActuel_ - facteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerTo(double zoomFacteur)
	///
	/// Permet de zoomer jusqu'a un facteur donné.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerTo(double zoomFacteur)
	{
		if (zoomFacteur > zoomInMax_) zoomFacteur = zoomInMax_;
		else if (zoomFacteur < zoomOutMax_) zoomFacteur = zoomOutMax_;

		std::cout << "zoomFacteur :" << std::endl;
		std::cout << zoomActuel_ << std::endl;
		zoomActuel_ = zoomFacteur;
		std::cout << zoomActuel_ << std::endl;

		largeurFenetre_ = largeurFenetreInit_ * (1/zoomFacteur);
		hauteurFenetre_ = hauteurFenetreInit_ * (1/zoomFacteur);


	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::redimensionnerFenetre( double largeur, double hauteur )
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
	void ProjectionOrtho::redimensionnerFenetre(int largeur, int hauteur)
	{
		//largeur = max(largeur, 100);
		//hauteur = max(hauteur, 100);

		{
			hauteurFenetre_ += (largeurFenetre_ / largeurCloture_)*hauteur - hauteurFenetre_;//calculer l'ajout à ajouter à la hauteur ancienne de la  fenêtre
		   largeurFenetre_ += (largeurFenetre_ / largeurCloture_)*largeur - largeurFenetre_;////calculer l'ajout à ajouter à la largeur ancienne de la  fenêtre

			largeurCloture_ = largeur;// la cloture prend la nouvelle largeur 
			hauteurCloture_ = hauteur;// la cloture prend la nouvelle hauteur


		obtenirMatrice();//  redimensionner ma fenetre virtuelle avec les nouvelles valeurs (matrice de projection)
		ajusterRapportAspect();
		}
	
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::mat4 ProjectionOrtho::obtenirMatrice() const
	///
	/// Cette fonction permet de retourner la fenêtre virtuelle en appelant les
	/// fonctions de glm selon le type de projection et les propriétés de la
	/// fenêtre.
	///
	/// @return Matrice de projection.
	///
	////////////////////////////////////////////////////////////////////////
	glm::mat4 ProjectionOrtho::obtenirMatrice() const
	{
		return glm::ortho(-largeurFenetre_ / 2, largeurFenetre_ / 2, 
			-hauteurFenetre_ / 2, hauteurFenetre_ / 2,	
			zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// de la clôture de façon à ce que le rapport d'aspect soit respecté.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect()
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
	double ProjectionOrtho::obtenirZoomActuel()
	{
		return zoomActuel_;
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
