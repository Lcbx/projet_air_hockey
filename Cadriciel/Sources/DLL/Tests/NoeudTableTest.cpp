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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
	//  Premier test : on vérifie que la position initiale des points de controles est un vector nul
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

	//// Second test : on vérifie que la position a été modifiée
	//vecteur = noeud->obtenirPositionRelative();
	//CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0] - 2.2));
	//CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1] - 3.3));
	//CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2] - 4.4));

	
}