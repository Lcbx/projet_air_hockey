#include "OpenGL_VBO.h"

///////////////////////////////////////////////////////////////////////////////
/// @file ModeleStorage_VBO.cpp
/// @author Martin Paradis
/// @date 2015-08-28
/// @version 1.0
///
/// @addtogroup modele Modele
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Modele3D.h"
#include "AideGL.h"
#include "Materiau.h"
#include "Utilitaire.h"
#include "../../../Sources/DLL/Application/FacadeModele.h"

/// Position de l'attribut de location dans le nuanceur de sommet
#define VERTEX_LOCATION 0
#define TEXCOORD_LOCATION 1
#define NORMAL_LOCATION 2




namespace opengl{

	Programme VBO::programme_;
	Nuanceur VBO::nuanceurFragment_;
	Nuanceur VBO::nuanceurSommet_;

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VBO::VBO(modele::Modele3D const* modele)
	///
	/// Assigne le mod�le 3D.
	///
	/// @param[in] modele : le modele 3D � dessiner.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	VBO::VBO(modele::Modele3D const* modele)
		: modele_{ modele }
	{}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VBO::~VBO()
	///
	/// Destructeur, rel�che le VBO.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	VBO::~VBO()
	{
		liberer();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::charger()
	///
	/// Charge les donn�es du mod�les 3D sur la m�moire de la carte graphique
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::charger()
	{
		if(!programme_.estInitialise())
		{
			// Initialisation des nuanceurs
			nuanceurFragment_.initialiser(Nuanceur::Type::NUANCEUR_FRAGMENT, "nuanceurs/fragment.glsl");
			nuanceurSommet_.initialiser(Nuanceur::Type::NUANCEUR_VERTEX, "nuanceurs/sommet.glsl");
			programme_.initialiser();
			programme_.attacherNuanceur(nuanceurFragment_);
			programme_.attacherNuanceur(nuanceurSommet_);
		}
		creerVBO(modele_->obtenirNoeudRacine());
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::creerVBO(modele::Noeud const& noeud)
	///
	/// Cr�ation des VBO selon les donn�es propres � chaque Mesh. L'ordre 
	/// des identifiants OpenGL se calque sur le mod�le 3D, en prenant pour
	/// acquis que la hi�rarchie interne des noeuds internes n'est pas 
	/// modifi�e.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::creerVBO(modele::Noeud const& noeud)
	{
		for (auto const& mesh : noeud.obtenirMeshes())
		{
			enregistrerTampon(mesh.obtenirSommets());
			if (mesh.possedeNormales())
				enregistrerTampon(mesh.obtenirNormales());
			if (mesh.possedeTexCoords())
				enregistrerTampon(mesh.obtenirTexCoords());
			if (mesh.possedeFaces())
				enregistrerTampon(mesh.obtenirFaces());
		}
		/// Cr�ation r�cursive.
		for (auto const& n : noeud.obtenirEnfants())
		{
			creerVBO(n);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::dessiner() const
	///
	/// Appelle le dessin du mod�le � partir des VBO.  Utilise le mod�le 3D
	/// pour obtenir la mat�riau propre � chaque Mesh.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::dessiner(const glm::mat4& modele, const glm::mat4& vue, const glm::mat4& projection) const
	{
		unsigned int bufferIndex = 0;
		dessiner(modele_->obtenirNoeudRacine(), bufferIndex, modele, vue, projection);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex) const
	///
	/// Dessin r�cursif du mod�le 3D.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex, const glm::mat4& modele, const glm::mat4& vue, const glm::mat4& projection) const
	{
		// Matrice de transformation
		glm::mat4x4 const& m{ projection * vue * modele };
		glm::mat4x4 const& v{ vue };
		glm::mat4x4 const& p{ projection };
		glm::mat4x4 const& mo{ modele };
		// Appliquer le nuanceur
#if 1
			Programme::Start(programme_);
			programme_.assignerUniforme("modelViewProjection", m);
			programme_.assignerUniforme("colorIn", glm::vec4(0.f, 0.f, 0.f, 1.f));
			programme_.assignerUniforme("matrVisu", v);
			programme_.assignerUniforme("matrProj", p);
			programme_.assignerUniforme("matrModel", mo);
			

#else		
		
			
			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(glm::value_ptr(m));
#endif

		for (auto const& mesh : noeud.obtenirMeshes())
		{
			// Appliquer le mat�riau pour le mesh courant
			appliquerMateriau(mesh.obtenirMateriau());

			bool possedeNormales{ mesh.possedeNormales() };
			bool possedeCouleurs{ mesh.possedeCouleurs() };
			bool possedeTexCoords{ mesh.possedeTexCoords() };
			bool possedeSommets{ mesh.possedeSommets() };
			bool possedeFaces{ mesh.possedeFaces() };

			if (possedeSommets)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableVertexAttribArray(VERTEX_LOCATION);
				glVertexAttribPointer(VERTEX_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			}
			if (possedeNormales)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				/// � Faire: Envoyer les normales aux nuanceurs si n�cessaire
				glEnableVertexAttribArray(NORMAL_LOCATION);
				glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
				//glNormalPointer(GL_FLOAT, 0, nullptr);
				
			}
			if (possedeTexCoords)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableVertexAttribArray(TEXCOORD_LOCATION);
				glVertexAttribPointer(TEXCOORD_LOCATION, 2, GL_FLOAT,	GL_FALSE, 0, nullptr);
			}
			if (possedeFaces)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(3 * mesh.obtenirFaces().size()), GL_UNSIGNED_INT, nullptr);
			}

			if (possedeSommets)
				glDisableVertexAttribArray(VERTEX_LOCATION);
			if (possedeTexCoords)
				glDisableVertexAttribArray(TEXCOORD_LOCATION);
		}
		Programme::Stop(programme_);

		/// Dessin r�cursif.
		for (auto const& n : noeud.obtenirEnfants())
		{
			dessiner(n, bufferIndex, modele, vue, projection);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::liberer()
	///
	/// Rel�che la m�moire sur la carte graphique.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::liberer()
	{
		for (auto const& handle : handles_)
		{
			glDeleteBuffers(static_cast<GLsizei>(handles_.size()), handles_.data());
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::appliquerMateriau(modele::Materiau const& materiau) const
	///
	/// Assigne un mat�riau OpenGL selon la m�thode d�pr�ci�e d'illumination
	/// d'OpenGL
	///
	/// @param[in] materiau : le materiau � assigner
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::appliquerMateriau(modele::Materiau const& materiau) const
	{
		/// V�rifier si texture existe
		if (modele_->possedeTexture(materiau.nomTexture_)) {
			// Activer le texturage OpenGL et lier la texture appropri�e
			glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_2D, modele_->obtenirTextureHandle(materiau.nomTexture_));
		}
		else {
			// D�sactiver le texturage OpenGL puisque cet objet n'a aucune texture
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}

		/// Assigner le mat�riau
		/// � Faire : Envoyez les valeurs du mat�riau aux nuanceurs
		programme_.assignerUniforme("Kemission", materiau.emission_);
		programme_.assignerUniforme("Kambient", materiau.ambiant_);
		programme_.assignerUniforme("Kdiffuse", materiau.diffuse_) ;
		programme_.assignerUniforme("Kspeculaire", materiau.speculaire_);
		programme_.assignerUniforme("KShininess", materiau.shininess_ * materiau.shininessStrength_);

		//Light 
		auto facade = FacadeModele::obtenirInstance();
		int lumiereAmbiant = facade->getEtatLumiereAmbiante();
		int lumiereDirectionelle = facade->getEtatLumiereDirectionnelle();
		int lumiereAmbiantSpot = facade->getEtatLumiereSpot();

		programme_.assignerUniforme("lumiereAmbiante", lumiereAmbiant);
		programme_.assignerUniforme("lumiereDirectionnelle", lumiereDirectionelle);
		programme_.assignerUniforme("lumiereSpot", lumiereAmbiantSpot);


		glPolygonMode(	GL_FRONT_AND_BACK,	materiau.filDeFer_ ? GL_LINE : GL_FILL);
		materiau.afficherDeuxCotes_ ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);




		
	}

	
}
