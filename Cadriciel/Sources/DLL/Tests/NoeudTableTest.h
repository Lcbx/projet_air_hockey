//////////////////////////////////////////////////////////////////////////////
/// @file NoeudTableTest.h
/// @author Ali
/// @date 2016-09-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDTABLETEST_H
#define _TESTS_NOEUDTABLETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "ArbreRenduINF2990.h"

class NoeudTable;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstraitTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe NoeudAbstrait
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class NoeudTableTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(NoeudTableTest);
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

	/// Cas de test: tester si la position d'un objet est dans la table ou non
	void testDansTable();

private:
	/// Instance d'un noeud Table
	std::unique_ptr<NoeudTable> noeud;
	ArbreRenduINF2990 * arbre;
};

#endif // _TESTS_NOEUDTABLETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
