/// @file TournoiTest.cpp
/// @author Carl-Vincent Landry-Duval
/// @date 2016-11-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{

#include "Tournoi.h"
#include "TournoiTest.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(TournoiTest);


////////////////////////////////////////////////////////////////////////
///
/// @fn void TournoiTest::setUp()
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
void TournoiTest::setUp() {}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TournoiTest::tearDown()
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
void TournoiTest::tearDown() {}

/// @fn void TournoiTest::testMatchup()
/// @brief Permet de tester si on obtient le bon matchup dans un tournoi
void TournoiTest::testMatchup() {
	std::vector<std::string> list;
	list.push_back("albert"); list.push_back("robert"); list.push_back("romain"); list.push_back("andre");
	Tournoi<std::string> tournoi(list);
	std::pair<std::string, std::string> expected ({ "romain", "andre" });
	std::pair<std::string, std::string> matchup = tournoi.obtenirProchainMatchup();
	CPPUNIT_ASSERT_MESSAGE("Should return (romain, andre)", expected == matchup);
}

/// @fn void TournoiTest::testGagnant()
/// @brief Permet de tester si le bon gagnant est assig� au matchup
void TournoiTest::testGagnant() {
	Tournoi<std::string> tournoi({ "albert","robert","romain","andre" });
	std::string gagnant1 = "romain";
	std::string gagnant2 = "robert";
	std::string gagnant3 = "romain";
	CPPUNIT_ASSERT_MESSAGE("Should return romain", gagnant1 == tournoi.affecterScoreProchainMatchup(2, 1));
	CPPUNIT_ASSERT_MESSAGE("Should return robert", gagnant2 == tournoi.affecterScoreProchainMatchup(1, 2));
	CPPUNIT_ASSERT_MESSAGE("Should return romain (Tournament winner)", gagnant3 == tournoi.affecterScoreProchainMatchup(1, 2));
}

/// @}
