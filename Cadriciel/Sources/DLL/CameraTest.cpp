///////////////////////////////////////////////////////////////////////////////////
/// @file CameraTest.cpp
/// @authorMedaoud Ikram
/// @date 2016-11-04
/// @version 1.0
///
////////////////////////////////////////////////////////////////////////////////////
#include"CameraTest.h"
#include "vue.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(CameraTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void cameraTest::setUp()
///
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CameraTest::setUp()
{
	camera = std::make_unique<vue::Camera>(glm::dvec3{ 0, 0, 200 }, glm::dvec3{ 0, 0, 0 },
		glm::dvec3{ 0, 1, 0 }, glm::dvec3{ 0, 1, 0 });
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void RedimensionnementTest::tearDown()
///
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CameraTest::tearDown()
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void RedimensionnementTest::testFenetre()
///
/// Cas de test: écriture/lecture de la cloture
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CameraTest::testDeplacerXY()
{

	 //Premier test : on vérifie que la position initiale est un vector nul
		camera->obtenirPosition();
		glm::dvec3 vecteur { camera->obtenirPosition() };
		CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0]));
		CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1]));

		camera->deplacerXY(50, 60, true);

	//// Second test : on vérifie que la fenêtre a été modifiée
		vecteur = camera-> obtenirPosition();
		CPPUNIT_ASSERT(vecteur[0]==50);
		CPPUNIT_ASSERT(vecteur[1]==60);

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void RedimensionnementTest::testFenetre()
///
/// Cas de test: écriture/lecture de la cloture
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CameraTest::testDeplacerZ()
{

	//Premier test : on vérifie que la position initiale est un vector nul
	camera->obtenirPosition();
	glm::dvec3 vecteur{ camera->obtenirPosition() };
	CPPUNIT_ASSERT((vecteur[2] == 200));
	camera->deplacerZ(100, true);

	//// Second test : on vérifie que la fenêtre a été modifiée
	vecteur = camera->obtenirPosition();
	CPPUNIT_ASSERT(vecteur[2] == 300);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
