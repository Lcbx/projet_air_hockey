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
///        méthodes de la classe Camera
///
/// @author Medaoud Ikram
/// @date 2016-11-03
///////////////////////////////////////////////////////////////////////////
class CameraTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(CameraTest);
	CPPUNIT_TEST(testPosition);
	CPPUNIT_TEST(testPointVise);
	CPPUNIT_TEST(testUp);
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

