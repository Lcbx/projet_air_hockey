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
///        m�thodes de la classe VisiteurCollision
///
/// @author Luc Courbariaux
/// @date 2016-11-07
///////////////////////////////////////////////////////////////////////////
class CollisionTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(CollisionTest);
	CPPUNIT_TEST(testCollisionSegments);
	CPPUNIT_TEST(testVisiterNoeudCercle);
	CPPUNIT_TEST(testVisiterNoeudQuadrilatere);
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

