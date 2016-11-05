//////////////////////////////////////////////////////////////////////////////
/// @file RedimensionnementTest.h
/// @author Medaoud Ikram
/// @date 2016-11-03
/// @version 1.0
///
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_REDIMENSIONNEMENTTEST_H
#define _TESTS_REDIMENSIONNEMENTTEST_H
#include "ProjectionOrtho.h"
#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class ProjectionOrtho;

///////////////////////////////////////////////////////////////////////////
/// @class RedimensionnementTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe ProjectionOrtho
///
/// @author Medaoud Ikram
/// @date 2016-11-03
///////////////////////////////////////////////////////////////////////////
class RedimensionnementTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(RedimensionnementTest);
	CPPUNIT_TEST(testFenetre);
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

	/// Cas de test: écriture/lecture de la position relative
	

	void testFenetre();

	
private:
	/// Instance d'un noeud abstrait
	std::unique_ptr<vue::ProjectionOrtho> fenetre;
};

#endif // _TESTS_REDIMENSIONNEMENTTEST_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
#pragma once
