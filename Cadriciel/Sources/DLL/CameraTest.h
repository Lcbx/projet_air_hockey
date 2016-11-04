//////////////////////////////////////////////////////////////////////////////
/// @file CameraTest.h
/// @author Medaoud Ikram
/// @date 2016-11-03
/// @version 1.0
///
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_CAMERATEST_H
#define _TESTS_CAMERATEST_H
#include "vue.h"
#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class Camera;

///////////////////////////////////////////////////////////////////////////
/// @class CameraTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe Camera
///
/// @author Medaoud Ikram
/// @date 2016-11-03
///////////////////////////////////////////////////////////////////////////
class CameraTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(CameraTest);
	CPPUNIT_TEST(testPosition);
	CPPUNIT_TEST(testPointVise);
	CPPUNIT_TEST(testUp);
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

	void testPosition();
	void testPointVise();
	void testUp();

private:
	/// Instance d'un noeud abstrait
	std::unique_ptr<vue::Camera> camera;
};

#endif // _TESTS_CAMERATEST_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
#pragma once

