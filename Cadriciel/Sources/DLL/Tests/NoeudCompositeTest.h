////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author Wajdi Gharsalli
/// @date 2016-11-03
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef _TESTS_NOEUDCOMPOSITETEST_H
#define _TESTS_NOEUDCOMPOSITETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "NoeudTable.h"
#include "AideGL.h"

class NoeudComposite;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstraitTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe NoeudAbstrait
///
/// @author Wajdi Gharsalli
/// @date 2016-11-03
///////////////////////////////////////////////////////////////////////////
class NoeudCompositeTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(NoeudCompositeTest);
	CPPUNIT_TEST(testVider);
	CPPUNIT_TEST(testAjout);
	CPPUNIT_TEST(testSuppression);
	CPPUNIT_TEST(testTrouverObjet);
	CPPUNIT_TEST(testSelectionMultiple);
	CPPUNIT_TEST(testScale);

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

	/// Cas de test: vider la table
	void testVider();

	/// Cas de test: ajout des objets
	void testAjout();

	/// Cas de test: supprimer des objets
	void testSuppression();

	///Cas de test: dans la table
	void testTrouverObjet(); 

	///Cas de test: selection multiple
	void testSelectionMultiple();

	///Cas de test: modifier le scale
	void testScale();


private:
	/// Instance d'un noeud abstrait
	//std::unique_ptr<NoeudComposite> noeud;
	NoeudTable *noeud;
};

#endif // _TESTS_NOEUDABSTRAITTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
