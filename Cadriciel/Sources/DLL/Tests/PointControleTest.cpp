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
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PointControleTest::setUp()
{
	
	// Nous pourrions initialiser l'objet, mais puisqu'il s'agit d'un singleton,
	// aucune initialisation n'est requise.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::tearDown()
///
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PointControleTest::tearDown()
{
	// Nous pourrions lib�rer l'objet, mais puisqu'il s'agit d'un singleton,
	// aucune lib�ration n'est requise.
	//delete arbreTest;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::testSauvegardeChargement()
///
/// Cas de test: sauvegarde et chargement XML de la configuration
/// Modifier la valeur CALCULS_PAR_IMAGE, enregistrer la configuration,
/// restaurer la valeur CALCULS_PAR_IMAGE, charger la configuration,
/// s'assurer que la valeur sauvegard�e a bien �t� restaur�e du fichier
/// XML, restaurer la valeur par d�faut.
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
