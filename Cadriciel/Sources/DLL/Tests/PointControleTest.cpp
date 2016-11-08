////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigSceneTest.cpp
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "PointControleTest.h"
#include "FacadeModele.h"
#include "PointsControle.h"
#include "ArbreRenduINF2990.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(PointControleTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::setUp()
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
void PointControleTest::setUp()
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::tearDown()
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
void PointControleTest::tearDown()
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::testSauvegardeChargement()
///
/// cas de test: tester si deux points sont symetriques
/// 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PointControleTest::testWiiw()
{
	NoeudTable* nouveauNoeud{ new NoeudTable{ ArbreRenduINF2990::NOM_TABLE } };
	nouveauNoeud->assignerPositionRelative({ 0,0,0 });
	

	glm::vec3 p0 =  nouveauNoeud->getPc(0);
	glm::vec3 p4 = nouveauNoeud->getPc(4);


	CPPUNIT_ASSERT(p0.x == -p4.x);
	CPPUNIT_ASSERT( p0.y == p4.y);
	CPPUNIT_ASSERT(p0.z == p4.z);

	delete nouveauNoeud;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
