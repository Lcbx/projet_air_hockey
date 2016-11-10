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
#include "FacadeModele.h"
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
	//FacadeModele::obtenirInstance()->initialiserOpenGL(nullptr);
	arbre = new ArbreRenduINF2990();
	arbre->initialiser();
	
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
	delete arbre;
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
	
	// on test avec des position qui se trouve dans la table 
	glm::dvec3 positionObjet[3] = { {0,0,0 }, {-84,10,0}, {84,-30,0} };
	// on teste si la position est dans la table 
	for (int i = 0; i < 3; i++)
	{
		bool danstable = arbre->getTable()->dansTable(positionObjet[i]);
		CPPUNIT_ASSERT_MESSAGE("objet est pas dans la table!!", danstable == true);
	}
	
	// on test avec des position qui se trouve a l'exterieur de la table 
	glm::dvec3 positionObjet2[5] = { { -86,20,0 },{ 86,-40,0 },{ 10,-76,0 }, {-30,76,0}, {200,200,0} };
	// on teste si la position est dans la table 
	for (int i = 0; i < 5; i++)
	{
		bool danstable = arbre->getTable()->dansTable(positionObjet2[i]);
		CPPUNIT_ASSERT_MESSAGE("objet n'est pas dans la table!!", danstable == false);
	}

	
}