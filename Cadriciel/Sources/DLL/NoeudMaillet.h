///////////////////////////////////////////////////////////////////////////
/// @file NoeudMaillet.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDMAILLET_H__
#define __ARBRE_NOEUDS_NOEUDMAILLET_H__


#include "NoeudAbstrait.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudMaillet
/// @brief Classe qui repr�sente un le noeud maillet de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudMaillet : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudMaillet(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudMaillet();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& vueProjection) const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	///permet de deplacer selon l'endroit voulu
	void deplacer(glm::vec3 pos);

	///Accepter le visiteur
	virtual void accepter(Visiteur* v);

	///obtient la vitesse du maillet
	glm::vec3 getVitesse() const { return vitesse_; }

private:

	///la position au moment de la derniere animation
	glm::vec3 dernierePosition_;
	///la vitesse du maillet
	glm::vec3 vitesse_;
	///la position vers laquelle le maillet se deplace
	glm::vec3 positionFuture_;


	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };
	
};


#endif // __ARBRE_NOEUDS_NOEUDMAILLET_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


