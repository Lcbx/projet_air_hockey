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

#include "Couleurs.h"

using namespace std;


/// La cha�ne repr�sentant le type des araign�es.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La cha�ne repr�sentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };

//Bonus
const std::string ArbreRenduINF2990::NOM_BONUS{ "bonus" };


//Portail
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
//La cha�ne repr�sentant le type des murets
const std::string ArbreRenduINF2990::NOM_MURET{ "muret" };
//La cha�ne repr�sentant le type des tables
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };
//La cha�ne repr�sentant le type des rondelles
const std::string ArbreRenduINF2990::NOM_RONDELLE{ "rondelle" };
//La cha�ne repr�sentant le type des points de controles de la table
const std::string ArbreRenduINF2990::NOM_POINTCONTROLE{ "pointcontrole" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur cr�e toutes les usines qui seront utilis�es par le
/// projet de INF2990et les enregistre aupr�s de la classe de base.
/// Il cr�e �galement la structure de base de l'arbre de rendu, c'est-�-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
/////////////////////////////////////////////////////////////////////////6
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_ARAIGNEE, new UsineNoeud<NoeudAraignee>{ NOM_ARAIGNEE, std::string{ "media/spider.obj" } });
	ajouterUsine(NOM_CONECUBE, new UsineNoeud<NoeudConeCube>{ NOM_CONECUBE, std::string{ "media/cubecone.obj" } });
	ajouterUsine(NOM_BONUS, new UsineNoeud<NoeudBonus>{ NOM_BONUS, std::string{ "media/bonus.obj" } });
	ajouterUsine(NOM_PORTAIL, new UsineNoeud<NoeudPortail>{ NOM_PORTAIL, std::string{ "media/portail.obj" } });
	ajouterUsine(NOM_MURET, new UsineNoeud<NoeudMuret>{ NOM_MURET, std::string{ "media/muret.obj" } });
	ajouterUsine(NOM_RONDELLE, new UsineNoeud<NoeudRondelle>{ NOM_RONDELLE, std::string{ "media/rondelle.obj" } });
	ajouterUsine(NOM_TABLE, new UsineNoeud<NoeudTable>{ NOM_TABLE, std::string{ "" } });
	ajouterUsine(NOM_POINTCONTROLE, new UsineNoeud<NoeudPointControle>{ NOM_POINTCONTROLE, std::string{ "" } });
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
/// @fn void ArbreRenduINF2990::ajouterTable()
///
/// Cette fonction ajoute la table a l'arbre du rendu
/// elle cree la table avec les 8 points de controle et l'affiche dans la fenetre opengl
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::ajouterTable()
{
	NoeudTable* noeudTable { (NoeudTable *)creerNoeud(NOM_TABLE) };
	noeudTable_ = noeudTable;
	//delete noeudTable;

	
	// On cree un objet Table et 8 points de controle
	//NoeudTable* noeudTable{ (NoeudTable *)creerNoeud(NOM_TABLE) };
	NoeudPointControle* noeudPointControle0{ (NoeudPointControle *)creerNoeud(NOM_POINTCONTROLE) };
	NoeudPointControle* noeudPointControle1{ (NoeudPointControle *)creerNoeud(NOM_POINTCONTROLE) };
	NoeudPointControle* noeudPointControle2{ (NoeudPointControle *)creerNoeud(NOM_POINTCONTROLE) };
	NoeudPointControle* noeudPointControle3{ (NoeudPointControle *)creerNoeud(NOM_POINTCONTROLE) };
	NoeudPointControle* noeudPointControle4{ (NoeudPointControle *)creerNoeud(NOM_POINTCONTROLE) };
	NoeudPointControle* noeudPointControle5{ (NoeudPointControle *)creerNoeud(NOM_POINTCONTROLE) };
	NoeudPointControle* noeudPointControle6{ (NoeudPointControle *)creerNoeud(NOM_POINTCONTROLE) };
	NoeudPointControle* noeudPointControle7{ (NoeudPointControle *)creerNoeud(NOM_POINTCONTROLE) };
	

	// ajouter le noeud table a l'arbre
	ajouter(noeudTable_);

	
	//GLfloat couleur[4] = { ROUGE };
	std::vector<GLdouble> couleur;
	couleur = { GRIS };
	glm::vec4 color;
	color.x = couleur[0];color.y = couleur[1];color.z = couleur[2];color.w = couleur[3];
	noeudTable->setCouleurMurs(color);
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//noeudTable->ajouter(noeudPointControle); // ajout du noeud (fils) point de controle dans la table (pere) -- pas fonctionnel !! pourquoi? sais pas
	//ajouter(noeudPointControle); // ajout du point de controle comme un noeud fils de l'arbre du rendu -- fonctionnel!! pourquoi? sais pas XD
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// asigner la position relative a la table 
	//noeudTable->assignerPositionRelative(glm::dvec3{ 0.0, 0.0, 0.0 }); //position (0,0,0) par default
	std::cout << "position Table : x=" << noeudTable_->obtenirPositionRelative().x 
		<<" y="<< noeudTable_->obtenirPositionRelative().y<<" z="<< noeudTable_->obtenirPositionRelative().z<<std::endl;
	
	// Associer les coord. des points de controle dans le noeudTable aux coord. des points des 8 noeuds noeudPointControle
	glm::vec3 point;
	// p0
	if (noeudTable_->getPointControle(0, point) == false)
		std::cout << "point de controle 0 introuvable " << std::endl;
	if (noeudPointControle0->setCoord(point) == false)
		std::cout << "incapable de mofidier les coordonnnes du point de controle 0 " << std::endl;
	// p1
	if (noeudTable_->getPointControle(1, point) == false)
		std::cout << "point de controle 1 introuvable " << std::endl;
	if (noeudPointControle1->setCoord(point) == false)
		std::cout << "incapable de mofidier les coordonnnes du point de controle 1 " << std::endl;
	// p2
	if (noeudTable_->getPointControle(2, point) == false)
		std::cout << "point de controle 2 introuvable " << std::endl;
	if (noeudPointControle2->setCoord(point) == false)
		std::cout << "incapable de mofidier les coordonnnes du point de controle 2 " << std::endl;
	// p3
	if (noeudTable_->getPointControle(3, point) == false)
		std::cout << "point de controle 3 introuvable " << std::endl;
	if (noeudPointControle3->setCoord(point) == false)
		std::cout << "incapable de mofidier les coordonnnes du point de controle 3 " << std::endl;
	// p4
	if (noeudTable_->getPointControle(4, point) == false)
		std::cout << "point de controle 4 introuvable " << std::endl;
	if (noeudPointControle4->setCoord(point) == false)
		std::cout << "incapable de mofidier les coordonnnes du point de controle 4 " << std::endl;
	// p5
	if (noeudTable_->getPointControle(5, point) == false)
		std::cout << "point de controle 5 introuvable " << std::endl;
	if (noeudPointControle5->setCoord(point) == false)
		std::cout << "incapable de mofidier les coordonnnes du point de controle 5 " << std::endl;
	// p6
	if (noeudTable_->getPointControle(6, point) == false)
		std::cout << "point de controle 6 introuvable " << std::endl;
	if (noeudPointControle6->setCoord(point) == false)
		std::cout << "incapable de mofidier les coordonnnes du point de controle 6 " << std::endl;
	// p7
	if (noeudTable_->getPointControle(7, point) == false)
		std::cout << "point de controle 7 introuvable " << std::endl;
	if (noeudPointControle7->setCoord(point) == false)
		std::cout << "incapable de mofidier les coordonnnes du point de controle 7 " << std::endl;
	
	// modifier la couleur des points de controle
	couleur = { BLEU};
	color.x = couleur[0];color.y = couleur[1];color.z = couleur[2];color.w = couleur[3];
	noeudPointControle0->setCouleur(color);noeudPointControle1->setCouleur(color);
	noeudPointControle2->setCouleur(color);noeudPointControle3->setCouleur(color);
	noeudPointControle4->setCouleur(color);noeudPointControle5->setCouleur(color);
	noeudPointControle6->setCouleur(color);noeudPointControle7->setCouleur(color);

	// ajouter les noeuds des points de controle a l'arbre du rendu
	ajouter(noeudPointControle0);ajouter(noeudPointControle1);
	ajouter(noeudPointControle2);ajouter(noeudPointControle3);
	ajouter(noeudPointControle4);ajouter(noeudPointControle5);
	ajouter(noeudPointControle6);ajouter(noeudPointControle7);
	
	
	// modification des points de controle
	//noeudTable->setPointControle(0, { -.9,.8,0 });
	//noeudTable->setPointControle(1, { -.7,-.8,0 });

	// tests
	//
	//// modifier la position du pointcontrole 0 de la table
	//if (noeudTable->setPointControle(0, { -1.,1.,0. }) == false)
	//	std::cout << "point de controle introuvable -- pas de set" << std::endl;
	//noeudPointControle0->setCoord({ -1.,1.,0. }); // modifier aussi les coords du point de controle 
	//// modifier la position du pointcontrole 4 de la table
	//noeudTable->setPointControle(4, { 1.,1.,0. });
	//noeudPointControle4->setCoord({ 1.,1.,0. }); // modifier aussi les coords du point de controle

	//GLfloat couleur[4] = { GRIS };
	//glm::vec4 color;
	//color.x = couleur[0];color.y = couleur[1];color.z = couleur[2];color.w = couleur[3];
	//noeudPointControle0->setCouleur(color);


}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction cr�e la structure de base de l'arbre de rendu, c'est-�-dire
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
	// afficher un message de test sur la console
	std::cout << "Allo! je suis dans l'initialisation de l'arbre du rendu inf2990"<< std::endl;
	// afficher la table avec les points de controles
	ajouterTable();

	///TODO
	///Chabnger l'araignee par la table / cube par les buts

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// test original d'affichage , les 2 objets arraignee et cubecone sont affiches
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//{
	//	// On vide l'arbre
	//	vider();
	//	// On ajoute un noeud bidon seulement pour que quelque chose s'affiche.
	//	NoeudAbstrait* noeudAraignee{ creerNoeud(NOM_ARAIGNEE) };
	//	noeudAraignee->ajouter(creerNoeud(NOM_CONECUBE));
	//	ajouter(noeudAraignee);
	//}	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable ArbreRenduINF2990::getTable() 
///
/// Cette fonction permet de recuperer le noeud Table
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
NoeudTable* ArbreRenduINF2990::getTable()
{
	return noeudTable_;
}




////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::ajouterBonus(glm::dvec3 pos) 
///
/// Cette fonction permet d'ajouter un bonus acc�larateur a la scene
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void ArbreRenduINF2990::ajouterBonus(glm::dvec3 pos) 
{

	NoeudAbstrait* noeudBonus{ creerNoeud(NOM_BONUS) };
	VisiteurAjout v1(pos);
	noeudBonus->setScale({ 1, 1, 1 });
	noeudBonus->accepter(&v1);


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
		// toujours liberer la m�moire !!!!
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
	// toujours liberer la m�moire !!!!
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
	

	// toujours toujours liberer la m�moire svp !!!!
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

	if (pos.x > posf.x && posf.y > pos.y) {
		angle = 180 - angle;
	} else if (pos.x > posf.x && posf.y < pos.y) {
		angle -= 180;
	} else if (pos.x < posf.x && posf.y < pos.y) {
		angle *= -1;
	}
	return angle;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn double getPosiX()
///
/// Cette fonction de retourner une position X d'un objet selectionne
///
/// @return position X
///
////////////////////////////////////////////////////////////////////////
double ArbreRenduINF2990::getPosiX()
{
	for (NoeudAbstrait * enfant : this->enfants_)
	{
		if (enfant->estSelectionne())
		{
			double posX = enfant->obtenirPositionRelative().x;
			return posX;
		}
	}
}




////////////////////////////////////////////////////////////////////////
///
/// @fn double getPosiY()
///
/// Cette fonction de retourner une position Y d'un objet selectionne
///
/// @return position Y
///
////////////////////////////////////////////////////////////////////////
double ArbreRenduINF2990::getPosiY()
{
	for (NoeudAbstrait * enfant : this->enfants_)
	{
		if (enfant->estSelectionne())
		{
			double posY = enfant->obtenirPositionRelative().y;
			return posY;
		}
	}
}




////////////////////////////////////////////////////////////////////////
///
/// @fn void deplacerObjet(glm::dvec3 posDep, double angle)
///
/// cette fonction permet de deplacer un objet 
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::deplacerObjet(glm::dvec3 posDep, double angle, double scale)
{

	for (NoeudAbstrait * enfant : enfants_)
	{
		if (enfant->estSelectionne())// && enfant->obtenirType() == "bonus" && comp==1)
		{
			//TODO: reste a verifier si l'objet sort pas de la table 
			//glm::dvec3 posTemp = enfant->obtenirPositionRelative();
			
			enfant->assignerPositionRelative(posDep);
			enfant->setAngle(angle);
			enfant->setScale(glm::dvec3(scale, scale, 1.0));
		}

	}
}



////////////////////////////////////////////////////////////////////////
///
/// @fn int obtenirNombreObjetSelectionnes()
///
/// Cette fonction de calculer le nombre des objets selectionnes 
///
/// @return nombre objet selectionn�es
///
////////////////////////////////////////////////////////////////////////
int ArbreRenduINF2990::obtenirNombreObjetSelctionnes()
{
	int comp = 0;
	for (NoeudAbstrait * enfant : enfants_)
	{
		if (enfant->estSelectionne())
		{
			comp++;
		}
	}
	std::cout << "Nombre objets selectionnes: " << comp << std::endl;
	return comp;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn doublegetAngleDataBinding()
///
/// Cette fonction de retourner l'angle d'un objet selectionn�
///
/// @return l'angle d'un objet
///
////////////////////////////////////////////////////////////////////////
double ArbreRenduINF2990::getAngleDataBinding()
{
		for (NoeudAbstrait * enfant : this->enfants_)
		{
			if (enfant->estSelectionne())
			{
				return enfant->getAngle();
			}
		}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn doublegetScaleDataBinding()
///
/// Cette fonction de retourner le scale d'un objet selectionn�
///
/// @return le scale d'un objet
///
////////////////////////////////////////////////////////////////////////
double ArbreRenduINF2990::getScaleDataBinding()
{
	for (NoeudAbstrait * enfant : this->enfants_)
	{
		if (enfant->estSelectionne())
		{
			double myScale= enfant->getScale().x;
			return myScale;
		}
	}


}



