//////////////////////////////////////////////////////////////////////////////
/// @file VueOrbite.h
/// @author Arthur Daniel-Adde
/// @date 2016-11-18
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUEORBITE_H__
#define __UTILITAIRE_VUEORBITE_H__


#include "Vue.h"
#include "Camera.h"
#include "ProjectionOrbite.h"

namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class VueOrbite
	/// @brief Classe concr�te de vue orbite.
	///
	/// Cette classe implante le comportement attendu d'une vue orbite.
	///
	/// @author Arthur Daniel-Adde
	/// @date 2016-11-18
	////////////////////////////////////////////////////////////////////////
	class VueOrbite : public Vue
	{
	public:
		/// Constructeur de la vue orbite
		VueOrbite(Camera const& camera, ProjectionOrbite const& projection);

		/// Obtention de la projection.
		virtual const ProjectionOrbite& obtenirProjection() const;

		/// Modification de la clot�re.
		virtual void redimensionnerFenetre(int largeur, int hauteur);

		/// Zoom in, c'est-�-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-�-dire un rapetissement.
		virtual void zoomerOut();
		/// Zoom in �lastique. (Ne fait rien en vue orbite)
		virtual void zoomerInElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);
		/// Zoom out �lastique. (Ne fait rien en vue orbite)
		virtual void zoomerOutElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);

		/// D�placement dans le plan XY par rapport � la vue.
		virtual void deplacerXY(double deplacementX, double deplacementY);
		/// D�placement dans le plan XY par rapport � la vue.
		virtual void deplacerXY(const glm::ivec2& deplacement);
		/// D�placement selon l'axe des Z par rapport � la vue.
		virtual void deplacerZ(double deplacement);
		/// Rotation selon les axes des X et des Y par rapport � la vue.
		virtual void rotaterXY(double rotationX, double rotationY);
		/// Rotation selon les axes des X et des Y par rapport � la vue.
		virtual void rotaterXY(const glm::ivec2& rotation);
		/// Rotation selon l'axe des Z par rapport � la vue.
		virtual void rotaterZ(double rotation);


	private:
		/// Projection utilis�e pour cette vue.
		ProjectionOrbite projection_;

	};


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUEORBITE_H__


   ///////////////////////////////////////////////////////////////////////////
   /// @}
   ///////////////////////////////////////////////////////////////////////////
