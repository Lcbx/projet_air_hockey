///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"
#include "Usines/UsineNoeud.h"
#include "EtatOpenGL.h"
#include "Noeuds/NoeudTypes.h"
#include <iostream>
#include "../Visiteur.h"
#include "../VisiteurAjout.h"
#include "../VisiteurDeplacement.h"
#include "../VisiteurMiseEchelle.h"
#include "../VisiteurRotation.h"
#include "../VisiteurSelection.h"

using namespace std;


/// La chaîne représentant le type des araignées.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La chaîne représentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };

//Bonus
const std::string ArbreRenduINF2990::NOM_BONUS{ "bonus" };


//Portail
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };

//Muret
const std::string ArbreRenduINF2990::NOM_MURET{ "muret" };

//Table
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
/////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_ARAIGNEE, new UsineNoeud<NoeudAraignee>{ NOM_ARAIGNEE, std::string{ "media/spider.obj" } });
	ajouterUsine(NOM_CONECUBE, new UsineNoeud<NoeudConeCube>{ NOM_CONECUBE, std::string{ "media/cubecone.obj" } });
	ajouterUsine(NOM_BONUS, new UsineNoeud<NoeudBonus>{ NOM_BONUS, std::string{ "media/rondelle.obj" } });
	ajouterUsine(NOM_PORTAIL, new UsineNoeud<NoeudPortail>{ NOM_PORTAIL, std::string{ "media/rondelle.obj" } });
	ajouterUsine(NOM_MURET, new UsineNoeud<NoeudMuret>{ NOM_MURET, std::string{ "media/muret.obj" } });
	ajouterUsine(NOM_TABLE, new UsineNoeud<NoeudTable>{ NOM_TABLE, std::string{ "" } });
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	// On vide l'arbre
	vider();

	///TODO
	///Chabnger l'araignee par la table / cube par les buts

	
	// On ajoute un noeud bidon seulement pour que quelque chose s'affiche.
	NoeudAbstrait* noeudAraignee{ creerNoeud(NOM_TABLE) };
	noeudAraignee->assignerPositionRelative(glm::dvec3{ 0.0, 0.0, 0.0 });
	//noeudAraignee->ajouter(creerNoeud(NOM_CONECUBE));
	ajouter(noeudAraignee);
	


	
	/*NoeudAbstrait* noeudRondelle{ creerNoeud(NOM_RONDELLE) };
	ajouter(noeudRondelle);
	*/

	
	
}





////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::ajouterBonus(glm::dvec3 pos) 
///
/// Cette fonction permet d'ajouter un bonus accélarateur a la scene
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void ArbreRenduINF2990::ajouterBonus(glm::dvec3 pos) 
{

	NoeudAbstrait* noeudBonus{ creerNoeud(NOM_BONUS) };
	Visiteur* v1 = new VisiteurAjout(pos);
	noeudBonus->accepter(v1);

	cout << "Bonus x  : " << noeudBonus->obtenirPositionRelative().x << "  Bonus  y: " << noeudBonus->obtenirPositionRelative().y << "  Bonus z: " << noeudBonus->obtenirPositionRelative().z << endl;


	// toujours liberer la mémoire !!!!
	delete v1;

	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::ajouterPortail(glm::dvec3 pos) 
///
/// Cette fonction permet d'ajouter le premier portail a la scene
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::ajouterPortail(glm::dvec3 pos)
{
	
		NoeudAbstrait* noeudPortail{ creerNoeud(NOM_PORTAIL) };
		Visiteur* v1 = new VisiteurAjout(pos);
	
		noeudPortail->accepter(v1);

		premierEstajoute = true;
		// toujours liberer la mémoire !!!!
		delete v1;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::ajouterPortailDeux(glm::dvec3 pos) 
///
/// Cette fonction permet d'ajouter le 2 partie de portail a la scene
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::ajouterPortailDeux(glm::dvec3 pos)
{
	NoeudAbstrait* premierPortail = this->enfants_.back();

	NoeudAbstrait* noeudPortail{ creerNoeud(NOM_PORTAIL) };
	Visiteur* v1 = new VisiteurAjout(pos);
	
	//etablir les liens entre les 2 portails
	noeudPortail->setFrere(premierPortail);
	premierPortail->setFrere(noeudPortail);

	noeudPortail->accepter(v1);

	premierEstajoute = false;
	// toujours liberer la mémoire !!!!
	delete v1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::supprimerPortail(bool escTouche)
///
/// Cette fonction permet de supprimer portail de la scene
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void ArbreRenduINF2990::supprimerPortail(bool escTouche) 
{
//	this->effacer(this->enfants_.back());

	if (escTouche == true)
	{
		if (this->enfants_.size() != NULL && premierEstajoute == true) 
		{
		
			cout<<"enfant du dernier: "<< this->enfants_.back()->obtenirNombreEnfants()<<endl;

			//supprime le 1er portail			
			this->effacer(this->enfants_.back());
			premierEstajoute = false;
		}
	}
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::ajouterMuret(glm::dvec3 position1, glm::dvec3 position2)
///
/// Cette fonction permet d'ajouter un muret de la scene
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void ArbreRenduINF2990::ajouterMuret(glm::dvec3 position1, glm::dvec3 position2)
{
	NoeudAbstrait* noeudMuret{ creerNoeud(NOM_MURET) };
	// a mettre dans une fonction de calcul d'angle et position

	Visiteur* v1 = new VisiteurAjout(glm::dvec3{ (position2.x + position1.x) / 2.0, (position2.y + position1.y) / 2.0, 0.0 });
	
	noeudMuret->setScale({ calculerScale(position1, position2), 2, 2 });
	
	noeudMuret->setAngle(calculerAngle(position1, position2));
	noeudMuret->accepter(v1);
	

	// toujours toujours liberer la mémoire svp !!!!
	delete v1;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn GLfloat calculerScale(glm::dvec3 pos, glm::dvec3 posf)
///
/// Cette fonction de calculer un scale
///
/// @return scale.
///
////////////////////////////////////////////////////////////////////////

GLfloat ArbreRenduINF2990::calculerScale(glm::dvec3 pos, glm::dvec3 posf)
{
	glm::dvec3 diff = posf - pos;
	GLfloat scale = sqrtf(glm::dot(diff, diff));

	scale = scale/2 ;
	return scale;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn GLfloat calculerAngle(glm::dvec3 pos, glm::dvec3 posf)
///
/// Cette fonction de calculer un angle
///
/// @return angle.
///
////////////////////////////////////////////////////////////////////////

double ArbreRenduINF2990::calculerAngle(glm::dvec3 pos, glm::dvec3 posf)
{
	double angle;

	angle = glm::degrees(atan(sqrt(pow((double)((posf.y - pos.y) / (posf.x - pos.x)), 2.0))));

	if (pos.x > posf.x && posf.y > pos.y)
	{
		angle = 180 - angle;
	}
	else
		if (pos.x > posf.x && posf.y < pos.y)
		{
			angle -= 180;
		}
		else
			if (pos.x < posf.x && posf.y < pos.y)
			{
				angle *= -1;
			}
	return angle;
}


double ArbreRenduINF2990::getPosi()
{

	
	for (NoeudAbstrait * enfant : this->enfants_)
	{
		if (enfant->estSelectionne())
		{
			cout << "*************aloooooo*************" << endl;

			double posX = enfant->obtenirPositionRelative().x;
			posX += 110;

			cout << "**** POSX***** "<<posX << endl;
			return posX;

		}
	}
}

void ArbreRenduINF2990::deplacer(glm::dvec3 posInial, glm::dvec3 posFinal)
{
	conteneur_enfants copy = enfants_;
	NoeudAbstrait* enfant;
	
	for (conteneur_enfants::iterator it{ copy.begin() }; it != copy.end(); ++it)
	{
		Visiteur* v1 = new VisiteurDeplacement(posInial, posFinal);
		//if (enfant->obtenirNombreEnfants() == 0){

		enfant = { (*it) };
		enfant->accepter(v1);
		// toujours toujours liberer la mémoire svp !!!!

		//}
		/*if (enfant->obtenirNombreEnfants()>0) {


			for (unsigned int i = 0; i < enfant->obtenirNombreEnfants(); i++) {


				NoeudAbstrait* fils = enfant->chercher(i);

				fils->acceptVisitor(v1);
				// toujours toujours liberer la mémoire svp !!!!
			}
		}*/

		delete v1;

	}

}




///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
