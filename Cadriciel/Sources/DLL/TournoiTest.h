////////////////////////////////////////////////////////////////////////////////////
/// @file TournoiTest.h
/// @author Carl-Vincent Landry-Duval
/// @date 2016-11-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include "Tournoi.h"


///////////////////////////////////////////////////////////////////////////
/// @class TournoiTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe Tournoi
///
/// @author Carl-Vincent Landry-Duval
/// @date 2016-11-08
///////////////////////////////////////////////////////////////////////////
class TournoiTest : public CppUnit::TestFixture {
	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(TournoiTest);
	CPPUNIT_TEST(testMatchup);
	CPPUNIT_TEST(testGagnant);
	CPPUNIT_TEST_SUITE_END();

public:
	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================
	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();

	// =================================================================
	// Définissez ici les différents cas de tests...
	// =================================================================

	/// Cas de test : Obtenir un matchup de deux partitipants
	void testMatchup();


	/// Cas de test : Obtenir le gagnant d'un matchup
	void testGagnant();
};

/// @}