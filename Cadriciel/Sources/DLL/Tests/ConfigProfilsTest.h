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
///        m�thodes de la classe ConfigProfils
///
/// @author Arthur
/// @date 2016-11-10
///////////////////////////////////////////////////////////////////////////
class ConfigProfilsTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(ConfigProfilsTest);
	CPPUNIT_TEST(testGestionProfils);
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
	void testGestionProfils();

};

#endif // _TESTS_CONFIGPROFILSTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
