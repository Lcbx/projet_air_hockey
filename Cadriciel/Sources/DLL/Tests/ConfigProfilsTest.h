//////////////////////////////////////////////////////////////////////////////
/// @file ConfigProfilsTest.h
/// @author Arthur
/// @date 2016-11-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_CONFIGPROFILSTEST_H
#define _TESTS_CONFIGPROFILSTEST_H

#include <cppunit/extensions/HelperMacros.h>

///////////////////////////////////////////////////////////////////////////
/// @class ConfigProfilsTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe ConfigProfils
///
/// @author Arthur
/// @date 2016-11-10
///////////////////////////////////////////////////////////////////////////
class ConfigProfilsTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(ConfigProfilsTest);
	CPPUNIT_TEST(testGestionProfils);
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
	void testGestionProfils();

};

#endif // _TESTS_CONFIGPROFILSTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
