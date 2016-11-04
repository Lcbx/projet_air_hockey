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
///        m�thodes de la classe ProjectionOrtho
///
/// @author Medaoud Ikram
/// @date 2016-11-03
///////////////////////////////////////////////////////////////////////////
class RedimensionnementTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(RedimensionnementTest);
	CPPUNIT_TEST(testFenetre);
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

	/// Cas de test: �criture/lecture de la position relative
	

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
