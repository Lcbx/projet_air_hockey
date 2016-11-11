//////////////////////////////////////////////////////////////////////////////
/// @file UtilitaireTest.h
/// @author Luc Courbariaux
/// @date 2016-11-07
/// @version 1.0
///
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../utilitaire.h"
#include <cppunit/extensions/HelperMacros.h>


///////////////////////////////////////////////////////////////////////////
/// @class UtilitaireTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes du namespace utilitaire
///
/// @author Luc Courbariaux
/// @date 2016-11-07
///////////////////////////////////////////////////////////////////////////
class UtilitaireTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(UtilitaireTest);
	CPPUNIT_TEST(testCalculerAngle3D);
	CPPUNIT_TEST(testMdansTriangleABC);
	CPPUNIT_TEST(testRotater);
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
	void testCalculerAngle3D();
	void testMdansTriangleABC();
	void testRotater();

private:
	
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

