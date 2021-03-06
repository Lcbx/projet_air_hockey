///////////////////////////////////////////////////////////////////////////
/// @file SkyBox.cpp
/// @author Luc Courbariaux
/// @date 2016-11-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////


#include "Skybox.h"
#include "FacadeModele.h"


////////////////////////////////////////////////////////////////////////
/// @fn SkyBox::SkyBox()
/// Ce constructeur crait un noeud h�ritant de la classe noeudAbstrait non selectionnable et non enregistrable
/// @return Aucune (constructeur).
/////////////////////////////////////////////////////////////////////////
SkyBox::SkyBox() : NoeudAbstrait("skybox"){
	selectionnable_ = false;
	enregistrable_ = false;
}

////////////////////////////////////////////////////////////////////////
/// @fn SkyBox::~SkyBox()
/// Ce destructeur appelle le destructeur de noeudAbstrait
/// @return Aucune (destructeur).
/////////////////////////////////////////////////////////////////////////
//SkyBox::~SkyBox() { this->NoeudAbstrait::~NoeudAbstrait(); }

////////////////////////////////////////////////////////////////////////
/// @fn virtual void afficherConcret(const glm::mat4& vueProjection) const
/// Cette fonction affiche tout simplement la bo�te d'environnement.
/// @param[in] vueprojection  : La matrice de la vue et projection utilis�e.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void SkyBox::afficherConcret(const glm::mat4& modele, const glm::mat4& vue, const glm::mat4& projection) const {
	glm::mat4 vueTemp = vue;
	if (!FacadeModele::obtenirInstance()->isVueOrtho())
		vueTemp =  vueTemp * glm::rotate(modele, 1.57f, glm::vec3(1.0f, 0.0f, 0.0f));
	boite_.afficher(projection * vueTemp * modele, glm::mat4(1));
}

////////////////////////////////////////////////////////////////////////
/// @fn virtual void animer(float temps)
/// Cette fonction ne fait rien (pas d'animation de la boite d'environnment)
/// @param[in] temps  : le temps ecoule entre deux affichages
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
//void SkyBox::animer(float temps) {}


////////////////////////////////////////////////////////////////////////
/// @fn virtual void accepter(Visiteur* v)
/// Cette fonction ne fait rien (pas de traitement sur la boite d'environnment)
/// @param[in] v  : le visiteur
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void SkyBox::accepter(Visiteur* v) {}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////