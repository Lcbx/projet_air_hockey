////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author Wajdi Gharsalli
/// @date 2016-11-03
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudAbstrait.h"
#include "NoeudCompositeTest.h"
#include "NoeudTable.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"
#include "Vue.h"
#include "AideGL.h"
#include "../Noeuds/NoeudTypes.h"
#include "../VisiteurSelection.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudCompositeTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::setUp()
///
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::setUp()
{
	//noeud = std::make_unique<NoeudTable>(ArbreRenduINF2990::NOM_TABLE);
	//NoeudTable* noeud{ (NoeudTable *)creerNoeud(NOM_TABLE) };
	noeud= new NoeudTable(ArbreRenduINF2990::NOM_TABLE);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::tearDown()
///
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::tearDown()
{
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testVider()
///
/// Cas de test: vider la table
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testVider()
{
	//creer d'un noeud bonus
	NoeudAbstrait* nouveauNoeud{ new NoeudBonus{ ArbreRenduINF2990::NOM_BONUS } };
	nouveauNoeud->assignerPositionRelative({ 0,0,0 });

	//ajouter le noeud sur la table 
	noeud->ajouter(nouveauNoeud);
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 1);

	//vider la table et verifier
	noeud->vider();
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testAjout()
///
/// Cas de test: ajouter des objets sur la table
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testAjout()
{
	//creer d'un noeud bonus
	NoeudAbstrait* noeudBonus{ new NoeudBonus{ ArbreRenduINF2990::NOM_BONUS } };
	noeudBonus->assignerPositionRelative({ 0,0,0 });

	NoeudAbstrait* noeudMuret{ new NoeudMuret{ ArbreRenduINF2990::NOM_MURET } };
	noeudMuret->assignerPositionRelative({ 10,10,0 });

	
	//ajouter le noeud sur la table 
	noeud->ajouter(noeudBonus);
	noeud->ajouter(noeudMuret);

	//verifier le nombre des objets ajoutés
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 2);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testSuppression()
///
/// Cas de test: supprimer des objets sur la table
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testSuppression()
{
	//creation d'un noeud bonus
	NoeudAbstrait* noeudBonus{ new NoeudBonus{ ArbreRenduINF2990::NOM_BONUS } };
	noeudBonus->assignerPositionRelative({ 20,25,0 });

	//creer d'un noeud portail
	NoeudAbstrait* noeudPortail{ new NoeudPortail{ ArbreRenduINF2990::NOM_PORTAIL } };
	noeudPortail->assignerPositionRelative({ 0,0,0 });

	//creer d'un 2eme portail
	NoeudAbstrait* noeudPortail2{ new NoeudPortail{ ArbreRenduINF2990::NOM_PORTAIL } };
	noeudPortail2->assignerPositionRelative({ 15,10,0 });

	//Etablir le lien entre les deux portails
	noeudPortail->setFrere(noeudPortail2);
	noeudPortail2->setFrere(noeudPortail);

	//ajouter le noeud sur la table 
	noeud->ajouter(noeudPortail);
	noeud->ajouter(noeudPortail2);
	noeud->ajouter(noeudBonus);

	//Verifier le nombre d'enfant tjrs
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 3);


	//selectionner le 1ere portail
	noeudPortail->assignerSelection(true);

	//effacer le portail, doit supprimer le deuxieme portail aussi
	noeud->effacerSelection();

	//Supprimer juste les elements selectionnées
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testTrouverObjet()
///
/// Cas de test: trouver un objet sur la table
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testTrouverObjet()
{
	
	//creation d'un noeud bonus
	NoeudAbstrait* noeudBonus{ new NoeudBonus{ ArbreRenduINF2990::NOM_BONUS } };
	noeudBonus->assignerPositionRelative({ 20,25,0 });

	//creer d'un noeud portail
	NoeudAbstrait* noeudPortail{ new NoeudPortail{ ArbreRenduINF2990::NOM_PORTAIL } };
	noeudPortail->assignerPositionRelative({ 0,0,0 });

	//creer d'un 2eme portail
	NoeudAbstrait* noeudPortail2{ new NoeudPortail{ ArbreRenduINF2990::NOM_PORTAIL } };
	noeudPortail2->assignerPositionRelative({ 15,10,0 });

	//Etablir le lien entre les deux portails
	noeudPortail->setFrere(noeudPortail2);
	noeudPortail2->setFrere(noeudPortail);

	//ajouter le noeud sur la table 
	noeud->ajouter(noeudBonus);
	noeud->ajouter(noeudPortail);
	noeud->ajouter(noeudPortail2);
	
	//Verifier le nombre des objets
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 3); 

	//chercher avec type  
	CPPUNIT_ASSERT(noeud->chercher("bonus") == noeudBonus);

	//chercher avec indice
	CPPUNIT_ASSERT(noeud->chercher(1) == noeudPortail);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testSelectionMultiple()
///
/// Cas de test: selctionner plusieurs objets
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testSelectionMultiple()
{
	//creation d'un noeud bonus
	NoeudAbstrait* noeudBonus{ new NoeudBonus{ ArbreRenduINF2990::NOM_BONUS } };
	noeudBonus->assignerPositionRelative({ 20,25,0 });

	//creer d'un noeud portail
	NoeudAbstrait* noeudMuret{ new NoeudMuret{ ArbreRenduINF2990::NOM_MURET } };
	noeudMuret->assignerPositionRelative({ 0,0,0 });


	//ajouter le noeud sur la table 
	noeud->ajouter(noeudBonus);
	noeud->ajouter(noeudMuret);
	
	//Verifier le nombre des objets
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 2);

	//selectionner tous les objets
	noeud->selectionnerTout();

	//verifier s'il sont selectionnes
	CPPUNIT_ASSERT(noeudBonus->estSelectionne() == true);
	CPPUNIT_ASSERT(noeudMuret->estSelectionne() == true);


	//on cree un deuxieme bonus qu'on va le selectionner seul
	NoeudAbstrait* noeudBonus2{ new NoeudBonus{ ArbreRenduINF2990::NOM_BONUS } };
	noeudBonus2->assignerPositionRelative({ 10,15,0 });

	noeud->ajouter(noeudBonus2);
	
	noeudBonus2->assignerSelection(true);


	//Deselectionner tous les objets
	noeud->deselectionnerTout();

	//verifier s'il sont deselectionnes
	CPPUNIT_ASSERT(noeudBonus->estSelectionne() == false);
	CPPUNIT_ASSERT(noeudMuret->estSelectionne() == false);
	CPPUNIT_ASSERT(noeudBonus2->estSelectionne() == false);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testScale()
///
/// Cas de test: modifier le scale d'un objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testScale()
{

	//Creer un noeud 
	NoeudAbstrait* noeudBonus{ new NoeudBonus{ ArbreRenduINF2990::NOM_BONUS } };
	noeudBonus->assignerPositionRelative({ 0,0,0 });

	//ajouter et selectionner 
	noeud->ajouter(noeudBonus);
	noeudBonus->assignerSelection(true);

	//declarer un vecteur
	glm::dvec3 vecteur{ noeudBonus->getScale() };

	// Second test : on vérifie que la position a été modifiée
	vecteur = noeudBonus->getScale();

	//Verification initial
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0] - 1));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1] - 1));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2] - 1));

	//modifier le scale
	noeudBonus->setScale({ 5,10,2 });

	vecteur = noeudBonus->getScale();
	//verifier encore
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0] - 5));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1] - 10));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2] - 2));
}

