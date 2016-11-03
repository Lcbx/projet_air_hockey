//////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstraitTest.h
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDCOMPOSITETEST_H
#define _TESTS_NOEUDCOMPOSITETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class NoeudComposite;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstraitTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe NoeudAbstrait
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class NoeudCompositeTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(NoeudCompositeTest);
	CPPUNIT_TEST(testVider);
	CPPUNIT_TEST(testDansTable);


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

	/// Cas de test: vider la table
	void testVider();

	/// Cas de test: a l'interieur de la table
	void testDansTable();





private:
	/// Instance d'un noeud abstrait
	std::unique_ptr<NoeudComposite> noeud;
};

#endif // _TESTS_NOEUDABSTRAITTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
