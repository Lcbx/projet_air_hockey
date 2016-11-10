//////////////////////////////////////////////////////////////////////////////
/// @file CollisionTest.h
/// @author Luc Courbariaux
/// @date 2016-11-07
/// @version 1.0
///
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../VisiteurCollision.h"
#include <cppunit/extensions/HelperMacros.h>
#include <memory>


///////////////////////////////////////////////////////////////////////////
/// @class CollisionTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe VisiteurCollision
///
/// @author Luc Courbariaux
/// @date 2016-11-07
///////////////////////////////////////////////////////////////////////////
class CollisionTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(CollisionTest);
	CPPUNIT_TEST(testCollisionSegments);
	CPPUNIT_TEST(testVisiterNoeudCercle);
	CPPUNIT_TEST(testVisiterNoeudQuadrilatere);
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
	void testCollisionSegments();
	void testVisiterNoeudCercle();
	void testVisiterNoeudQuadrilatere();

private:
	/// Instance d'un noeud abstrait
	VisiteurCollision visiteur_;
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

