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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
/// Cas de test: écriture/lecture de la cloture
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void RedimensionnementTest::testFenetre()
{
	

	// Premier test : on vérifie que la position initiale est un vector nul
	fenetre->obtenirDimensionFenetreVirtuelle();
	


	//// On modifie la dimension de la fenêtre
	fenetre->redimensionnerFenetre(600,700);

	//// Second test : on vérifie que la fenêtre a été modifiée
	glm::dvec2 vecteur({ fenetre->obtenirDimensionFenetreVirtuelle() });
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0] == 700));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1] ==600));
}




///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
