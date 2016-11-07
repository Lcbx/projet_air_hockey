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
///        m�thodes de la classe ConfigScene
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class PointControleTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(PointControleTest);
	CPPUNIT_TEST(testWiiw);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();

	// =================================================================
	// D�finissez ici les diff�rents cas de tests...
	// =================================================================

	/// Cas de test: sauvegarde et chargement XML de la configuration
	void testWiiw();



};

#endif // _TESTS_POINTCONTROLETEST_H