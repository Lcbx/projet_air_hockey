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
	/// @param[in] largeurCloture   : dimension en @a X de la cl�ture.
	/// @param[in] hauteurCloture   : dimension en @a Y de la cl�ture.
	/// @param[in] zAvant			: distance du plan avant (en @a z).
	/// @param[in] zArriere			: distance du plan arri�re (en @a z).
	/// @param[in] zoomInMax		: facteur de zoom in maximal.
	/// @param[in] zoomOutMax		: facteur de zoom out maximal.
	/// @param[in] incrementZoom	: increment du facteur de zoom.
	/// @param[in] largeurFenetre	: dimension en @a X de la fen�tre
	///								  virtuelle.
	/// @param[in] hauteurFenetre	: dimension en @a Y de la fen�tre
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
	/// Permet de faire un zoom in selon l'incr�ment de zoom.
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
	/// Permet de faire un zoom out selon l'incr�ment de zoom.
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
	/// Permet de faire un zoom in avec un incr�ment sp�cifi�.
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
	/// Permet de faire un zoom out avec un d�cr�ment sp�cifi�.
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
	/// Permet de zoomer jusqu'a un facteur donn�.
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
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// d'un redimensionnement de la fen�tre.
	///
	/// L'agrandissement de la fen�tre virtuelle est proportionnel �
	/// l'agrandissement de la clot�re afin que les objets gardent la m�me
	/// grandeur apparente lorsque la fen�tre est redimensionn�e.
	///
	/// @param[in]  largeur : largeur de la nouvelle cl�ture
	/// @param[in]  hauteur : hauteur de la nouvelle cl�ture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::redimensionnerFenetre(int largeur, int hauteur)
	{
		//largeur = max(largeur, 100);
		//hauteur = max(hauteur, 100);

		{
			hauteurFenetre_ += (largeurFenetre_ / largeurCloture_)*hauteur - hauteurFenetre_;//calculer l'ajout � ajouter � la hauteur ancienne de la  fen�tre
		   largeurFenetre_ += (largeurFenetre_ / largeurCloture_)*largeur - largeurFenetre_;////calculer l'ajout � ajouter � la largeur ancienne de la  fen�tre

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
	/// Cette fonction permet de retourner la fen�tre virtuelle en appelant les
	/// fonctions de glm selon le type de projection et les propri�t�s de la
	/// fen�tre.
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
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// de la cl�ture de fa�on � ce que le rapport d'aspect soit respect�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect()
	{
		// � IMPLANTER.
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
