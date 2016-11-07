//////////////////////////////////////////////////////////////////////////////
/// @file PointControleTest.h
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_POINTCONTROLETEST_H
#define _TESTS_POINTCONTROLETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "PointsControle.h"
#include "NoeudPointControle.h"
#include "ArbreRenduINF2990.h"

class ArbreRenduINF2990;

///////////////////////////////////////////////////////////////////////////
/// @class PointControleTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe ConfigScene
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class PointControleTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(PointControleTest);
	CPPUNIT_TEST(testWiiw);
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

	/// Cas de test: sauvegarde et chargement XML de la configuration
	void testWiiw();



};

#endif // _TESTS_POINTCONTROLETEST_H