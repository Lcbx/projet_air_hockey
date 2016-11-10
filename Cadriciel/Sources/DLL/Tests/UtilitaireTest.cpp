///////////////////////////////////////////////////////////////////////////////////
/// @file CollisionTest.cpp
/// @author Luc Courbariaux
/// @date 2016-11-07
/// @version 1.0
///
////////////////////////////////////////////////////////////////////////////////////
#include"UtilitaireTest.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(UtilitaireTest);


////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::setUp()
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
void UtilitaireTest::setUp()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::tearDown()
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
void UtilitaireTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testCalculerAngle3D()
///
/// Cas de test: test du calcul de l'angle entre trois points
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testCalculerAngle3D() {
	glm::vec3 p[] = {
		{ 0,0,0 }, //0
		{ 0,1,0 }, //1
		{ 0,2,0 }, //2
		{ 1,1,0 }, //3
		{ 2,0,0 }  //4
	};
#define ASSERT_ANGLE(p1, p2, p3, res) CPPUNIT_ASSERT( glm::round(glm::degrees(utilitaire::calculerAngle3D(p[p1], p[p2], p[p3]))) == res )
	ASSERT_ANGLE(0, 1, 2, 180 );
	ASSERT_ANGLE(1, 0, 2, 0);
	ASSERT_ANGLE(1, 0, 4, 90);
	ASSERT_ANGLE(2, 1, 3, 90);
	ASSERT_ANGLE(1, 0, 3, 45);
#undef ASSERT_ANGLE
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testMdansTriangleABC()
///
/// Cas de test: test d'un point comme etant dans un triangle de trois point
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testMdansTriangleABC() {
	glm::vec3 p[] = {
		{ 0,0,0 }, //0
		{ 0,1,0 }, //1
		{ 0,2,0 }, //2
		{ 1,1,0 }, //3
		{ 2,0,0 }  //4
	};
#define ASSERT_TRIANGLE(p1, p2, p3, M, res) CPPUNIT_ASSERT( utilitaire::MdansTriangleABC(p[p1], p[p2], p[p3], p[M]) == res )
	ASSERT_TRIANGLE(0, 0, 0, 1, false);
	ASSERT_TRIANGLE(0, 2, 4, 3, true);
	ASSERT_TRIANGLE(0, 2, 4, 1, true);
	ASSERT_TRIANGLE(0, 1, 3, 4, false);
#undef ASSERT_TRIANGLE
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testRotater()
///
/// Cas de test: test de la rotation d'un point par rapport a l'origine
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testRotater() {
	glm::dvec3 p[] = {
		{ 0,0,0 }, //0
		{ 0,1,0 }, //1
		{ 0,2,0 }, //2
		{ 1,1,0 }, //3
		{ 2,0,0 }  //4
	};
	glm::dvec3 test;
#define ASSERT_ROTATER(p1, angle, res)	test = utilitaire::rotater(p[p1], (double) glm::radians(angle)); \
										 CPPUNIT_ASSERT( glm::round(p[res].x) == glm::round(test.x) &&  glm::round(p[res].y) == glm::round(test.y) )
	ASSERT_ROTATER(0, 180.f, 0);
	ASSERT_ROTATER(4, 90.f, 2);
	ASSERT_ROTATER(2, -90.f, 4);

	//dernier test
	test = utilitaire::rotater(p[1], (double)glm::radians(60.f));
	CPPUNIT_ASSERT(glm::round(p[3].x) != glm::round(test.x) && glm::round(p[3].y) != glm::round(test.y));

#undef ASSERT_ROTATER
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////