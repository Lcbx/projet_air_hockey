////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudCompositeTest.h"
#include "NoeudTable.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

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
	noeud = std::make_unique<NoeudTable>(ArbreRenduINF2990::NOM_TABLE);
	//NoeudTable* noeud{ (NoeudTable *)creerNoeud(NOM_TABLE) };

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
/// @fn void NoeudCompositeTest::testEnfants()
///
/// Cas de test: s'assurer que le noeud abstrait n'a pas d'enfant
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


	/*
	// On vérifie qu'initialement, le noeud n'a pas d'enfant
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);

	// Essaie d'ajouter un noeud
	NoeudAbstrait* nouveauNoeud{ new NoeudConeCube{ ArbreRenduINF2990::NOM_CONECUBE } };
	bool ajout{ noeud->ajouter(nouveauNoeud) };

	// L'ajout devrait avoir échoué puisqu'il s'agit d'un noeud abstrait...
	CPPUNIT_ASSERT(ajout == false);

	// Assurons-nous que le noeud ne possède pas d'enfant...
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);

	// Nettoyage
	delete nouveauNoeud;*/
}

void NoeudCompositeTest::testDansTable()
{
	NoeudAbstrait* nouveauNoeud{ new NoeudBonus{ ArbreRenduINF2990::NOM_BONUS } };

	nouveauNoeud->assignerPositionRelative({ 0,0,0 });

	noeud->ajouter(nouveauNoeud);

	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 1);

}
