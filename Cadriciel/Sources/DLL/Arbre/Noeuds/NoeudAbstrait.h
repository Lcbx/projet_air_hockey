///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstrait.h
/// @author DGI-INF2990
/// @date 2007-01-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef __ARBRE_NOEUDS_NOEUDABSTRAIT_H__
#define __ARBRE_NOEUDS_NOEUDABSTRAIT_H__


#include "GL/glew.h"
#include <string>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "Utilitaire.h"

/// D�clarations avanc�es pour contenir un pointeur vers un mod�le3D et son storage
namespace modele{
	class Modele3D;
}
namespace opengl{
	class VBO;
}


/// D�clarations avanc�es pour le patron visiteur
class Visiteur;
class VisiteurPointMilieu;
class VisiteurDeplacement;
class VisiteurDuplication;
class VisiteurSelection;
class VisiteurRotation;
class VisiteurMiseEchelle;
class VisiteurAjout;





///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilis�e pour cr�er l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant �tre pr�sent dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudAbstrait(
		const std::string& type = std::string{ "" }
	);
	/// Destructeur.
	virtual ~NoeudAbstrait();

	/// Obtient le parent de ce noeud.
	inline NoeudAbstrait* obtenirParent();

	/// Obtient le parent de ce noeud (version constante).
	inline const NoeudAbstrait* obtenirParent() const;

	/// Assigne le parent de ce noeud.
	inline void assignerParent(NoeudAbstrait* parent);

	/// Obtient la position relative du noeud.
	inline glm::vec3 obtenirPositionRelative() const;

	/// Assigne la position relative du noeud.
	inline void assignerPositionRelative(const glm::vec3& positionRelative);

	/// Obtient le type du noeud.
	inline const std::string& obtenirType() const;

	/// �crit l'�tat de l'affichage du du noeud.
	inline void assignerAffiche(bool affiche);
	/// V�rifie si le noeud se fait afficher.
	inline bool estAffiche() const;

	/// �crit l'�tat de la s�lection du noeud.
	inline void assignerSelection(bool selectionne);
	/// V�rifie si le noeud est s�lectionn�.
	inline bool estSelectionne() const;
	/// �crit si le noeud peut �tre s�lectionn� ou non.
	inline void assignerEstSelectionnable(bool selectionnable);
	/// V�rifie si le noeud est s�lectionnable.
	inline bool estSelectionnable() const;
	/// �crit si le noeud peut �tre enregistr� ou non.
	inline void assignerEstEnregistrable(bool enregistrable);
	/// V�rifie si le noeud est enregistrable.
	inline bool estEnregistrable() const;

	/// Assigne le mod�le3D et la liste d'affichage du noeud courant
	inline void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste);

	/// Calcule la profondeur de l'arbre sous le noeud courant.
	virtual unsigned int calculerProfondeur() const;

	/// Vide le noeud de ses enfants.
	virtual void vider();
	/// Efface le noeud pass� en param�tre.
	virtual void effacer(const NoeudAbstrait* noeud);

	/// Cherche un noeud par le type (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(const std::string& typeNoeud) const;
	/// Cherche un noeud par le type.
	virtual NoeudAbstrait* chercher(const std::string& typeNoeud);
	/// Cherche un noeud enfant selon l'indice (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(unsigned int indice) const;
	/// Cherche un noeud enfant selon l'indice.
	virtual NoeudAbstrait* chercher(unsigned int indice);

	/// Ajoute un noeud enfant.
	virtual bool ajouter(NoeudAbstrait* enfant);
	/// Obtient le nombre d'enfants du noeud.
	virtual unsigned int obtenirNombreEnfants() const;

	/// Changer la s�lection du noeud.
	virtual void inverserSelection();
	/// Efface les enfants s�lectionn�s.
	virtual void effacerSelection();
	/// S�lectionne tous les enfants de m�me que le noeud.
	virtual void selectionnerTout();
	/// D�s�lectionne tous les enfants de m�me que le noeud.
	virtual void deselectionnerTout();
	/// V�rifier si le noeud ou un de ses enfants est s�lectionn�.
	virtual bool selectionExiste() const;

	/// Change le mode d'affichage des polygones.
	virtual void changerModePolygones(bool estForce);
	/// Assigne le mode d'affichage des polygones.
	virtual void assignerModePolygones(GLenum modePolygones);
	/// Affiche le noeud.
	virtual void afficher(const glm::mat4& vueProjection) const;
	/// Affiche le noeud de mani�re concr�te.
	virtual void afficherConcret(const glm::mat4& vueProjection) const;
	/// Anime le noeud.
	virtual void animer(float dt);

	/// Permet d'obtenir le rayon du mod�le du noeud
	inline virtual double obtenirRayonModele() const;
	/// Permet d'obtenir le rayon du mod�le du noeud avec la mise � l'�chelle
	inline virtual double obtenirRayon() const;

	/// Accepter le visiteur
	virtual void accepter(Visiteur* v);

	/// Permet d'obtenir le mod�le du noeud
	modele::Modele3D const* getModele() { return this->modele_; };
	
	/// Permet de d'assigner un noeud fr�re (utile pour les portails)
	virtual void setFrere(NoeudAbstrait* frere);

	/// Permet d'obtenir un noeud fr�re (utile pour les portails)
	virtual NoeudAbstrait* getFrere();


	/// Permet de changer l'angle directeur du noeud
	virtual void setAngle(float angle);
	/// Permet de changer l'�chelle de redimensionnement
	virtual void setScale(const glm::dvec3& scale);
	
	/// Permet d'obtenir l'angle directeur du noeud
	inline float getAngle() const;
	/// Permet d'obtenir la mise � l'�chelle du noeud
	inline const glm::dvec3& getScale() const; 

	///definir le deuxieme joueur
	bool estDeuxiemeJoueur = false;
	// boolean pour afficher ou non le rayon d'attraction du portail
	bool rayonAffiche_{ false };

protected:
	/// Type du noeud.
	std::string      type_;

	/// Mode d'affichage des polygones.
	GLenum           modePolygones_{ GL_FILL };

	/// Transformation relative du noeud.
	glm::mat4         transformationRelative_;

	/// Vrai si on doit afficher le noeud.
	bool             affiche_{ true };

	/// S�lection du noeud.
	bool             selectionne_{ false };

	/// Vrai si le noeud est s�lectionnable.
	bool             selectionnable_{ true };

	/// D�termine si l'objet peut �tre sauvegard� en XML.
	bool             enregistrable_{ true };

	/// Pointeur vers le parent.
	NoeudAbstrait*   parent_{ nullptr };

	/// Mod�le 3D correspondant � ce noeud.
	modele::Modele3D const* modele_;
	/// Storage pour le dessin du mod�le
	opengl::VBO const* vbo_;


	// scale
	glm::dvec3 scale_ = { 1.0, 1.0, 1.0 };
	
	// angle de rotation
	/// Angle selon l'axe des X.
	float angleX_{ 0.f };
	/// Angle selon l'axe des Y.
	float angleY_{ 0.f };
	/// Angle de rotation.
	float angleRotation_{ 0.f };

	NoeudAbstrait* frere_;
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
///
/// Cette fonction retourne le pointeur vers le parent de ce noeud.
///
/// @return Le pointeur vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
///
/// Cette fonction retourne le pointeur constant vers le parent de ce noeud.
///
/// @return Le pointeur constant vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerParent( NoeudAbstrait* parent )
///
/// Cette fonction assigne le parent du noeud afin qu'il soit possible
/// de remonter dans l'arbre.
///
/// @param[in] parent : Le parent du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerParent(
	NoeudAbstrait* parent
	)
{
	parent_ = parent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position relative du noeud par rapport
/// � son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline glm::vec3 NoeudAbstrait::obtenirPositionRelative() const
{
	return glm::vec3(transformationRelative_[3]);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport � son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionRelative(
	const glm::vec3& positionRelative
	)
{
	transformationRelative_= glm::translate(glm::mat4(1.0f), positionRelative);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une cha�ne repr�sentante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& NoeudAbstrait::obtenirType() const
{
	return type_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'�tat affich� ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAffiche(bool affiche)
{
	affiche_ = affiche;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estAffiche() const
///
/// Cette fonction retourne l'�tat que le noeud se fait afficher ou non.
///
/// @return L'�tat affich� ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estAffiche() const
{
	return affiche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'�tat d'�tre s�lectionn� ou non du noeud.
///
/// @param selectionne : L'�tat s�lectionn� ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection(bool selectionne)
{
	// Un objet non s�lectionnable n'est jamais s�lectionn�.
	selectionne_ = (selectionne && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'�tat d'�tre s�lectionn� ou non du noeud.
///
/// @return L'�tat s�lectionn� ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
	// Un objet non s�lectionnable n'est jamais s�lectionn�.
	return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'�tat d'�tre s�lectionnable ou non du noeud.
///
/// @param selectionnable : L'�tat s�lectionnable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstSelectionnable(bool selectionnable)
{
	selectionnable_ = selectionnable;
	selectionne_ = selectionne_ && selectionnable_;
}




////////////////////////////////////////////////////////////////////////
/// @fn double NoeudAbstrait::obtenirRayonModele()
/// Permet d'obtenir lle rayon du modele
/// @return Le rayon du mod�le
////////////////////////////////////////////////////////////////////////
inline double NoeudAbstrait::obtenirRayonModele() const {
	//obtenir le rayon via le calcul du cylindre englobant
	return utilitaire::calculerCylindreEnglobant(*modele_).rayon;
}

////////////////////////////////////////////////////////////////////////
/// @fn double NoeudAbstrait::obtenirRayon()
/// Permet d'obtenir le rayon de la forme en fonction du rayon du mod�le
/// @return Le rayon de l'objet
////////////////////////////////////////////////////////////////////////
inline double NoeudAbstrait::obtenirRayon() const {
	return obtenirRayonModele() * this->getScale().y;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionnable() const
///
/// Cette fonction retourne l'�tat d'�tre s�lectionnable ou non du noeud.
///
/// @return L'�tat s�lectionnable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionnable() const
{
	return selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
///
/// Cette fonction permet d'assigner l'�tat d'�tre entregistrable ou non du noeud.
///
/// @param enregistrable : L'�tat enregistrable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstEnregistrable(bool enregistrable)
{
	enregistrable_ = enregistrable;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estEnregistrable() const
///
/// Cette fonction retourne l'�tat d'�tre enregistrable en XML ou non du
/// noeud.
///
/// @return L'�tat enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estEnregistrable() const
{
	return enregistrable_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D* modele, modele::opengl_storage::OpenGL_Liste* liste)
///
/// Cette fonction assigne l'objet de rendu au mod�le, c'est-�-dire son
/// mod�le 3D et sa liste d'affichage
///
/// @param modele : le mod�le 3D
/// @param liste : la liste d'affichage OpenGL
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)
{
	modele_ = modele;
	vbo_ = liste;
}


////////////////////////////////////////////////////////////////////////
/// @fn void NoeudAbstrait::setAngle(float angle)
/// Permet de changer l'angle de rotation de l'objet. Il est ensuite normalis� entre -pi et pi
/// @param[in] angle : Angle de rotation par rapport � l'axe des X en radian
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::setAngle(float angle) {
	if (angle <= utilitaire::DEG_TO_RAD(-180))
		angle += (float) utilitaire::DEG_TO_RAD(360);
	else if (angle > utilitaire::DEG_TO_RAD(180))
		angle -= (float) utilitaire::DEG_TO_RAD(360);

	angleRotation_ = angle;
}

////////////////////////////////////////////////////////////////////////
/// @fn void NoeudAbstrait::setScale(const glm::dvec3& scale) 
/// Permet de changer le redimensionnement de l'objet
/// @param[in] scale : Vecteur contenant l'ensemble des redimensionnements en X, Y et Z
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::setScale(const glm::dvec3& scale) {
	scale_ = scale;
}


////////////////////////////////////////////////////////////////////////
/// @fn float NoeudAbstrait::getAngle()
/// Permet d'obtenir l'angle de rotation du noeud en radian
/// @return L'angle de rotation par rapport � l'axe des X en radian
////////////////////////////////////////////////////////////////////////
inline float NoeudAbstrait::getAngle() const {
	return angleRotation_;
}


////////////////////////////////////////////////////////////////////////
/// @fn glm::dvec3&  NoeudAbstrait::getScale()
/// Permet d'obtenir la mise � l'�chelle de l'objet en prennant en compte
/// que le vecteur retourn� est l'agrandissement en fonction des composants
/// i.e: vec.x est le redimensonnement en X
/// @return L'angle de rotation par rapport � l'axe des X en radian
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::getScale() const{
	return scale_;
}


#endif // __ARBRE_NOEUDS_NOEUDABSTRAIT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
