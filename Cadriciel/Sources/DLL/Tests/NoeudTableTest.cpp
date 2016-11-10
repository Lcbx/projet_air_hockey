////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudTableTest.cpp
/// @authorAli
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudTableTest.h"
#include "NoeudTable.h"
#include "GL/glew.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudTableTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTableTest::setUp()
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
void NoeudTableTest::setUp()
{
	noeud = std::make_unique<NoeudTable>(ArbreRenduINF2990::NOM_TABLE);	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTableTest::tearDown()
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
void NoeudTableTest::tearDown()
{
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTableTest::dansTable()
///
/// Cas de test: verifier si la position d'un tel objet est dans la table
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTableTest::testDansTable()
{
	//  Premier test : on v�rifie que la position initiale des points de controles est un vector nul
	glm::vec3  pointControle[8];
	for (int i=0; i<8 ; i++)
		noeud->getPointControle(i, pointControle[i]);

	for (int i = 0; i<8; i++)
		for (int j = 0; j < 3; j++)
		{
			//CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(pointControle[i][j]));
			CPPUNIT_ASSERT_MESSAGE("failed to get pointdecontrole", utilitaire::EGAL_ZERO(pointControle[i][j]));
		}

	//// On modifie la position
	//noeud->assignerPositionRelative(glm::dvec3{ 2.2, 3.3, 4.4 });

	//// Second test : on v�rifie que la position a �t� modifi�e
	//vecteur = noeud->obtenirPositionRelative();
	//CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0] - 2.2));
	//CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1] - 3.3));
	//CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2] - 4.4));

	
}