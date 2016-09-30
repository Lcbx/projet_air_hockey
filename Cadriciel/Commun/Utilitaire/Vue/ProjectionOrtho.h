////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_PROJECTIONORTHO_H__
#define __UTILITAIRE_PROJECTIONORTHO_H__

#define LARGEUR_FENETREV_DEFAUT 200
#define HAUTEUR_FENETREV_DEFAUT 200

#define LARGEUR_CLOTURE_DEFAUT 200
#define HAUTEUR_CLOTURE_DEFAUT 200

#include "Projection.h"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class ProjectionOrtho
	/// @brief Classe implantant une projection orthogonale.
	///
	/// Cette classe implante l'interface de projection définie par la
	/// classe de base Projection et ajoute certaines fonctionnalitées
	/// spécifiques à la projection orthogonale, comme le zoom autour d'un
	/// point en particulier et le zoom élastique.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
	////////////////////////////////////////////////////////////////////////
	class ProjectionOrtho : public Projection
	{
	public:
		/// Constructeur.
		ProjectionOrtho(int largeurCloture, int hauteurCloture,
			double zAvant, double zArriere,
			double zoomInMax, double zoomOutMax,
			double incrementZoom,
			double largeurFenetre, double hauteurFenetre);


		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerTo(double zoomFacteur);
		/// Modification de la clôture.
		virtual void redimensionnerFenetre(int largeur, int hauteur);
		/// Obtention de la matrice de projection.
		virtual glm::mat4 obtenirMatrice() const;

		/// Obtenir les nnées de la fenêtre virtuelle.
		inline glm::dvec2 obtenirDimensionFenetreVirtuelle() const;


	private:
		/// Ajuste la fenêtre virtuelle pour respecter le rapport d'aspect.
		void ajusterRapportAspect();

		/// Largeur de la fenêtre virtuelle.
		double largeurFenetre_;
		/// Hauteur de la fenêtre virtuelle.
		double hauteurFenetre_;
		/// Largeur initiale de la fenêtre virtuelle.
		double largeurFenetreInit_;
		/// Hauteur initiale de la fenêtre virtuelle.
		double hauteurFenetreInit_;

		/// Facteur de zoom actuel
		double zoomActuel_;

	};




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void ProjectionOrtho::obtenirCoordonneesFenetreVirtuelle(double& xMin, double& xMax, double& yMin, double& yMax) const
	///
	/// Cette fonction retourne les coordonnées de la fenêtre virtuelle
	/// associée à cette projection.
	///
	/// @param[out]  xMin : La variable qui contiendra l'abcsisse minimale.
	/// @param[out]  xMax : La variable qui contiendra l'abcsisse maximale.
	/// @param[out]  yMin : La variable qui contiendra l'ordonnée minimale.
	/// @param[out]  yMax : La variable qui contiendra l'ordonnée maximale.
	///
	/// @return Les coordonnées de la fenêtre virtuelle.
	///
	////////////////////////////////////////////////////////////////////////
	inline glm::dvec2 ProjectionOrtho::obtenirDimensionFenetreVirtuelle() const
	{
		return glm::dvec2(largeurFenetre_, hauteurFenetre_);
	}


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_PROJECTIONORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
