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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
/// @brief Permet de tester si le bon gagnant est assigé au matchup
void TournoiTest::testGagnant() {
	Tournoi<std::string> tournoi({ "albert","robert","romain","andre" });
	std::string gagnant1 = "romain";
	std::string gagnant2 = "robert";
	std::string gagnant3 = "romain";
	CPPUNIT_ASSERT_MESSAGE("Should return romain", gagnant1 == tournoi.affecterScoreProchainMatchup(2, 1));
	CPPUNIT_ASSERT_MESSAGE("Should return robert", gagnant2 == tournoi.affecterScoreProchainMatchup(1, 2));
	CPPUNIT_ASSERT_MESSAGE("Should return romain (Tournament winner)", gagnant3 == tournoi.affecterScoreProchainMatchup(1, 2));
}


/// @fn void TournoiTest::testArbre() 
/// @brief Permet de tester si l'arbre final est le bon
void TournoiTest::testArbre() {
	Tournoi<std::string> tournoi({ "albert","robert","romain","andre" });
	tournoi.affecterScoreProchainMatchup(2, 1); //Romain gagne
	tournoi.affecterScoreProchainMatchup(1, 2); //Robert gagne
	tournoi.affecterScoreProchainMatchup(2, 1); //Robert gagne
	std::vector<std::pair<std::string, int>> resultats = tournoi.obtenirMatchups();
	std::vector<std::string> nomsResultats({ "robert","robert","romain","albert","robert","romain","andre" });
	std::vector<int> scoreResultats({ 0, 2, 1, 1, 2, 2, 1 });
	for (size_t i = 0; i < 7; i++) {
		std::string text = "Should return " + nomsResultats[i];
		CPPUNIT_ASSERT_MESSAGE(text.c_str(), resultats[i].first == nomsResultats[i]);
		if (i > 0) {
			text = "Should return " + char(scoreResultats[i] + '0');
			CPPUNIT_ASSERT_MESSAGE(text.c_str(), resultats[i].second == scoreResultats[i]);
		}
	}
}

/// @}
