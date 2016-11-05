////////////////////////////////////////////////////////////////////////////////////
/// @file RedimensionnementTest.cpp
/// @authorMedaoud Ikram
/// @date 2016-11-04
/// @version 1.0
///
////////////////////////////////////////////////////////////////////////////////////

#include "RedimensionnementTest.h"
#include "ProjectionOrtho.h"
#include "vue.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(RedimensionnementTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void RedimensionnementTest::setUp()
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
void RedimensionnementTest::setUp()
{
	fenetre = std::make_unique<vue::ProjectionOrtho>(LARGEUR_CLOTURE_DEFAUT,HAUTEUR_CLOTURE_DEFAUT,0.5 ,100,100,100, 4,LARGEUR_FENETREV_DEFAUT, HAUTEUR_FENETREV_DEFAUT);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void RedimensionnementTest::tearDown()
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
void RedimensionnementTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void RedimensionnementTest::testFenetre()
///
/// Cas de test: �criture/lecture de la cloture
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RedimensionnementTest::testFenetre()
{
	

	// Premier test : on v�rifie que la position initiale est un vector nul
	fenetre->obtenirDimensionFenetreVirtuelle();
	


	//// On modifie la dimension de la fen�tre
	fenetre->redimensionnerFenetre(600,700);

	//// Second test : on v�rifie que la fen�tre a �t� modifi�e
	glm::dvec2 vecteur({ fenetre->obtenirDimensionFenetreVirtuelle() });
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0] == 700));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1] ==600));
}




///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
