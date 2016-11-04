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

#include "Deplacement.h"

#include "../Affichage_debuggage.h"

using namespace std;


/// La chaîne représentant le type des araignées.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La chaîne représentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };
///La chaîne représentant le type des Bonus
const std::string ArbreRenduINF2990::NOM_BONUS{ "bonus" };
///La chaîne représentant le type des Portails
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
///La chaîne représentant le type des murets
const std::string ArbreRenduINF2990::NOM_MURET{ "muret" };
///La chaîne représentant le type des tables
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };
///La chaîne représentant le type des rondelles
const std::string ArbreRenduINF2990::NOM_RONDELLE{ "rondelle" };
///La chaîne représentant le type des points de controles de la table
const std::string ArbreRenduINF2990::NOM_POINTCONTROLE{ "pointcontrole" };
///La chaîne représentant le type des points de controles de la table
const std::string ArbreRenduINF2990::NOM_MAILLET{ "maillet" };

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
	ajouterUsine(NOM_MAILLET, new UsineNoeud<NoeudMaillet>{ NOM_MAILLET, std::string{ "media/maillet.obj" } });

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
	// On cree un objet Table et 8 points de controle
	NoeudTable* noeudTable { (NoeudTable *)creerNoeud(NOM_TABLE) };
	noeudTable_ = noeudTable;
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
	// ajouter les noeuds des points de controle a la table
	noeudTable_->ajouter(noeudPointControle0);
	noeudTable_->ajouter(noeudPointControle1);
	noeudTable_->ajouter(noeudPointControle2);
	noeudTable_->ajouter(noeudPointControle3);
	noeudTable_->ajouter(noeudPointControle4);
	noeudTable_->ajouter(noeudPointControle5);
	noeudTable_->ajouter(noeudPointControle6);
	noeudTable_->ajouter(noeudPointControle7);
	
	
	noeudTable_->setPointControles();
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
	ajouterTable();
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
/// Cette fonction permet d'ajouter un bonus accélérateur a la scene
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
	
	utilitaire::BoiteEnglobante boudingBox = utilitaire::calculerBoiteEnglobante(*noeudMuret->getModele());
	int sizeModelX = std::abs(boudingBox.coinMax.x - boudingBox.coinMin.x) / 2;

	noeudMuret->setScale({ calculerScale(position1, position2) / sizeModelX, 2, 2 });
	
	noeudMuret->setAngle(utilitaire::DEG_TO_RAD(calculerAngle(position1, position2)));
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
		if (enfant->estSelectionne())
		{
			//verifier si l'objet sort pas de la table 

			glm::dvec3 posTemp = enfant->obtenirPositionRelative();

			if (this->getTable()->dansTable(posDep))
			{
				enfant->assignerPositionRelative(posDep);
				this->estInterieur = true;
			}
			else
			{
				enfant->assignerPositionRelative(posTemp);
				this->estInterieur = false ;

			}

			//setter l'angle
			enfant->setAngle(angle);

			//fixer des limites pour scale
			if (scale > 8) {
				scale = 8;
			}
			if (scale < 0.5) {
				scale = 0.5;
			}
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
/// @return nombre objet selectionnées
///
////////////////////////////////////////////////////////////////////////
int ArbreRenduINF2990::obtenirNombreObjetSelctionnes()
{
	int comp = 0;
	//int compMuret = 0;
	
	
	for (NoeudAbstrait * enfant : enfants_)
	{
		if (enfant->estSelectionne())
		{
		//	if (enfant->obtenirType() == "muret" ) {
		//		compMuret++;
		//	}
		//	else 
		//	{
				comp++;
		//	}
		}
	}
	//compMuret = compMuret / 2;
	comp = comp; // +compMuret;
	return comp;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn doublegetAngleDataBinding()
///
/// Cette fonction de retourner l'angle d'un objet selectionné
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
				 double angleDeg = utilitaire::RAD_TO_DEG( enfant->getAngle());
				 return angleDeg;
			}
		}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn doublegetScaleDataBinding()
///
/// Cette fonction de retourner le scale d'un objet selectionné
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

////////////////////////////////////////////////////////////////////////
///
/// @fn bool objetEstDansLaTable()
///
/// Cette fonction de retourner faux si un objet a l'exterieur de la table
///
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool ArbreRenduINF2990::objetEstDansLaTable()
{
	return estInterieur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ajouterMailletEtRondelle()
///
/// Cette fonction permet d'Ajouter les maillets et la rondelle
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void  ArbreRenduINF2990::ajouterMailletEtRondelle()
{
	//initialiser le score
	this->setScoreMoi(0);
	this->setScoreAutre(0);

	//AJOUT RONDELLE
	NoeudAbstrait* noeudRondelle{ creerNoeud(NOM_RONDELLE) };
	noeudRondelle->assignerPositionRelative({ 0,0,0 });
	noeudRondelle->setScale({ 1, 1, 1 });
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeudRondelle);
	
	// get les coord du but droit
	glm::vec3 pointHaut, pointMilieu, pointBas;
	this->getTable()->getButs(1, pointHaut, pointMilieu, pointBas);
	//AJOUT MAILLET1
	NoeudAbstrait* noeudMaillet{ creerNoeud(NOM_MAILLET) };
	// positionner le maillet a 5 pas du but
	noeudMaillet->assignerPositionRelative({pointMilieu.x - noeudMaillet->obtenirRayon() - 5,0,0 });
	noeudMaillet->setScale({ 1, 1, 1 });
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeudMaillet);
	noeudMaillet->estDeuxiemeJoueur = false;
	
	
	// get les coord du but gauche
	this->getTable()->getButs(2, pointHaut, pointMilieu, pointBas);
	//AJOUT MAILLET2
	NoeudAbstrait* noeudMaillet2{ creerNoeud(NOM_MAILLET) };
	// positionner le maillet a 5 pas du but
	noeudMaillet2->assignerPositionRelative({ pointMilieu.x + noeudMaillet2->obtenirRayon() +5,0,0 });
	noeudMaillet2->setScale({ 1, 1, 1 });
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeudMaillet2);
	noeudMaillet2->estDeuxiemeJoueur = true;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  ArbreRenduINF2990::obtenirMailletManuel()
///
/// Cette fonction permet d'obtenir le maillet controlle avec les touches
///
/// @return NoeudAbstrait*
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* ArbreRenduINF2990::obtenirMailletManuel()
{
	for (NoeudAbstrait * enfant : this->enfants_)
		if (enfant->obtenirType() == "maillet")
			if (enfant->estDeuxiemeJoueur == true)
				return enfant;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn deplacerMailletAvecClavier(double x, double y)
///
/// Cette fonction permet de deplacer le maillet avedc les touches de clavier
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
//void ArbreRenduINF2990::deplacerMailletAvecClavier(double x, double y)
//{
//	NoeudAbstrait* dernier = this->enfants_.back();//pour obtenir le maillet du 2eme joueur
//	glm::dvec3 pos = dernier->obtenirPositionRelative();
//	double rayon = dernier->obtenirRayon();
//	//bouger vers droite
//	if (x == 1) {
//		if (this->getTable()->dansZone1({ pos.x + rayon , pos.y + rayon, 0 }) && this->getTable()->dansZone1({ pos.x + rayon , pos.y - rayon, 0 })) 		
//		{
//			if (y == 1) { dernier->assignerPositionRelative({ pos.x + 4, pos.y + 4, 0 }); }
//			else if (y == -1) { dernier->assignerPositionRelative({ pos.x + 2, pos.y - 2, 0 }); }
//			else dernier->assignerPositionRelative({ pos.x + 4, pos.y, 0 });
//		}
//		else dernier->assignerPositionRelative({ pos.x, pos.y, 0 });//ne pas depasser le centre
//	}
//
//	if (x == -1) {
//		if (this->getTable()->dansZone1({ pos.x - rayon , pos.y + rayon, 0 }) && this->getTable()->dansZone1({ pos.x - rayon , pos.y - rayon, 0 }))//checker si a l'interieur 		
//		{
//			if (y == 1) { dernier->assignerPositionRelative({ pos.x - 4, pos.y + 4, 0 }); }
//			else if (y == -1) { dernier->assignerPositionRelative({ pos.x - 4, pos.y - 4, 0 }); }
//			else dernier->assignerPositionRelative({ pos.x - 4, pos.y, 0 });
//		}
//		else dernier->assignerPositionRelative({ pos.x, pos.y, 0 });
//	}
//
//	if (x == 0) {
//		if (y == 1) {
//			if (this->getTable()->dansZone1({ pos.x , pos.y + rayon , 0 }))			
//			{
//				dernier->assignerPositionRelative({ pos.x , pos.y + 4, 0 });
//			}
//			else {
//				dernier->assignerPositionRelative({ pos.x, pos.y, 0 });
//			}
//		}
//			else if (y == -1) { 
//				if (this->getTable()->dansZone1({ pos.x , pos.y - rayon , 0 })) 				
//				{
//				dernier->assignerPositionRelative({ pos.x , pos.y - 4, 0 }); 
//				}
//				else {
//					dernier->assignerPositionRelative({ pos.x, pos.y, 0 });
//				}
//		}
//	}
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//test Ali
////////////////////////////////////////////////////////////////////////
///
/// @fn deplacerMailletAvecClavier(double x, double y)
///
/// Cette fonction permet de deplacer le maillet avedc les touches de clavier
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::deplacerMailletAvecClavier(double x, double y)
{
	NoeudAbstrait* dernier = this->enfants_.back();//pour obtenir le maillet du 2eme joueur
	glm::vec3 positionActuelle = dernier->obtenirPositionRelative();
	glm::vec3 nouvellePosition = positionActuelle;
	double rayon = dernier->obtenirRayonModele();
	if (x == 1)
		nouvellePosition.x = nouvellePosition.x + 4;
	if (x == -1)
		nouvellePosition.x = nouvellePosition.x - 4;
	if (y == 1)
		nouvellePosition.y = nouvellePosition.y + 4;
	if (y == -1)
		nouvellePosition.y = nouvellePosition.y - 4;
	if (this->getTable()->mailletDansZone1(nouvellePosition, rayon))
		dernier->assignerPositionRelative(nouvellePosition);
	else
		dernier->assignerPositionRelative(positionActuelle);	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
///
/// @fn void reinitialiserPartieCourante()
///
/// Cette fonction permet de re-initialiser la scene, donc mettre les maillets et la rondelle
/// a la position de depart
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::reinitialiserPartieCourante()
{
	// retirer maillet et rondelle
	//effacer les maillets et la rondelle
	this->effacer(this->chercher("rondelle"));

	while (this->chercher("maillet")) {
		this->effacer(this->chercher("maillet"));
	}
	ajouterMailletEtRondelle();

	////To-Do; 
	////re-initilaser sscore
	//this->setScoreMoi(0);
	//this->setScoreAutre(0);

	//glm::vec3 pointHaut, pointMilieu, pointBas;

	//for (NoeudAbstrait * enfant : this->enfants_)
	//{
	//	if (enfant->obtenirType() == "maillet") {
	//		if (enfant->estDeuxiemeJoueur == true) {
	//			this->getTable()->getButs(2, pointHaut, pointMilieu, pointBas);
	//			
	//			enfant->assignerPositionRelative({ pointMilieu.x + enfant->obtenirRayon() + 5,0,0 });
	//		}
	//		else {
	//			this->getTable()->getButs(1, pointHaut, pointMilieu, pointBas);

	//			enfant->assignerPositionRelative({ pointMilieu.x - enfant->obtenirRayon() - 5,0,0 });
	//		}
	//	}
	//	else if (enfant->obtenirType() == "rondelle") {
	//		enfant->assignerPositionRelative({ 0,0,0 });
	//	}
	//}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void deplacerMailletAvecSouris(glm::dvec3 pos)
///
/// Cette fonction permet de deplacer le maillet avec la souris
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::deplacerMailletAvecSouris(glm::dvec3 pos)
{
	for (NoeudAbstrait * enfant : this->enfants_)
	{
		if (enfant->obtenirType() == "maillet") {
			if (enfant->estDeuxiemeJoueur == false)
			{
				if (this->getTable()->mailletDansZone2(pos, enfant->obtenirRayonModele()))
				{
					enfant->assignerPositionRelative(pos);
				}
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void activerRayonPortail()
///
///Author : Ali
/// Cette fonction permet d'activer le rayon d'attraction d'un portail
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::activerRayonPortail()
{
	Debug::obtenirInstance().afficherAttraction = true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void deactiverRayonPortail()
///
///Author : Ali
/// Cette fonction permet de deactiver le rayon d'attraction d'un portail
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::deactiverRayonPortail()
{
	Debug::obtenirInstance().afficherAttraction = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void effacerPointControle()
///
///Author : Ali
/// Cette fonction permet d'effacer l'affichage les points de controles
/// de la table
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::effacerPointControle()
{
	noeudTable_->afficherPointsControles = false;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void effacerPointControle()
///
///Author : Ali
/// Cette fonction permet d'effacer l'affichage les points de controles
/// de la table
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::afficherPointControle()
{
	noeudTable_->afficherPointsControles = true;
}
