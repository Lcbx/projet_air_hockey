//////////////////////////////////////////////////////////////////////////////
/// @file UtilitaireTest.h
/// @author Luc Courbariaux
/// @date 2016-11-07
/// @version 1.0
///
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../utilitaire.h"
#include <cppunit/extensions/HelperMacros.h>


///////////////////////////////////////////////////////////////////////////
/// @class UtilitaireTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes du namespace utilitaire
///
/// @author Luc Courbariaux
/// @date 2016-11-07
///////////////////////////////////////////////////////////////////////////
class UtilitaireTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(UtilitaireTest);
	CPPUNIT_TEST(testCalculerAngle3D);
	CPPUNIT_TEST(testMdansTriangleABC);
	CPPUNIT_TEST(testRotater);
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
	void testCalculerAngle3D();
	void testMdansTriangleABC();
	void testRotater();

private:
	
};


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

