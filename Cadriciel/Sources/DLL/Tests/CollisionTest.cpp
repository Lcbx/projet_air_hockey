///////////////////////////////////////////////////////////////////////////////////
/// @file CollisionTest.h
/// @author Luc Courbariaux
/// @date 2016-11-07
/// @version 1.0
///
////////////////////////////////////////////////////////////////////////////////////
#include"CollisionTest.h"
#include "../NoeudBonus.h"
#include "../NoeudPortail.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(CollisionTest);


////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionTest::setUp()
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
void CollisionTest::setUp()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionTest::tearDown()
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
void CollisionTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionTest::testCollisionSegments()
///
/// Cas de test: test d'un objet rond par rapport a un ensemble de segments
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTest::testCollisionSegments() {
	glm::vec3 boite[] = {
		glm::vec3(0,0,0),
		glm::vec3(0,1,0),
		glm::vec3(1,1,0),
		glm::vec3(1,0,0),
		glm::vec3(0,0,0)
	};
	visiteur_.rondelle_ = false;
	visiteur_.rayon_ = 0.1;
	aidecollision::DetailsCollision  test;

	//test des collisions proprement dit

	visiteur_.position_ = {0,0.5,0};
	test = visiteur_.collisionSegments( boite, 5);
	CPPUNIT_ASSERT(test.type == aidecollision::COLLISION_SEGMENT);

	visiteur_.position_ = { 0,2,0 };
	test = visiteur_.collisionSegments(boite, 5);
	CPPUNIT_ASSERT(test.type == aidecollision::COLLISION_AUCUNE);

	visiteur_.position_ = { 1,1.05,0 };
	test = visiteur_.collisionSegments(boite, 5);
	CPPUNIT_ASSERT(test.type == aidecollision::COLLISION_SEGMENT);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionTest::testVisiterNoeudCercle()
///
/// Cas de test: test d'un objet rond par rapport a un autre objet rond
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTest::testVisiterNoeudCercle() {

	//initialistion contexte openGl
	auto facade = FacadeModele::obtenirInstance();
	facade->initialiserOpenGL(nullptr);
	auto arbre = facade->obtenirArbreRenduINF2990();

	auto noeudRond = arbre->creerNoeud(ArbreRenduINF2990::NOM_PORTAIL);
	noeudRond->assignerPositionRelative(glm::vec3(0, 0, 0));
	
	
	visiteur_.rondelle_ = false;
	float rayon = visiteur_.rayon_ = noeudRond->obtenirRayon();
	aidecollision::DetailsCollision  test;
	
	
	//test des collisions proprement dit
	
	visiteur_.position_ = { 3 * rayon, 0, 0 };
	test = visiteur_.visiterNoeudCercle( noeudRond, noeudRond->obtenirRayon());
	CPPUNIT_ASSERT(test.type == aidecollision::COLLISION_AUCUNE);

	visiteur_.position_ = { 0, 2*rayon-1, 0 };
	test = visiteur_.visiterNoeudCercle( noeudRond, noeudRond->obtenirRayon());
	CPPUNIT_ASSERT(test.type != aidecollision::COLLISION_AUCUNE);
	
	noeudRond->setScale({ 0.2,1,1 });
	test = visiteur_.visiterNoeudCercle( noeudRond, noeudRond->obtenirRayon());
	CPPUNIT_ASSERT(test.type == aidecollision::COLLISION_AUCUNE);

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void CollisionTest::testVisiterNoeudQuadrilatere()
///
/// Cas de test: test d'un objet rond par rapport a un objet de forme rectangulaire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CollisionTest::testVisiterNoeudQuadrilatere() {

	//initialistion contexte openGl
	auto facade = FacadeModele::obtenirInstance();
	facade->initialiserOpenGL(nullptr);
	auto arbre = facade->obtenirArbreRenduINF2990();

	auto noeudRectangle = arbre->creerNoeud(ArbreRenduINF2990::NOM_BONUS);

	visiteur_.rondelle_ = false;
	visiteur_.rayon_ = 10;
	aidecollision::DetailsCollision  test;
	noeudRectangle->assignerPositionRelative(glm::vec3(0, 10, 0));
	
	//test des collisions proprement dit

	visiteur_.position_ = { -5, 5, 0 };
	test = visiteur_.visiterNoeudQuadrilatere(noeudRectangle);
	CPPUNIT_ASSERT(test.type != aidecollision::COLLISION_AUCUNE);

	visiteur_.position_ = { 25, 10, 0 };
	test = visiteur_.visiterNoeudQuadrilatere(noeudRectangle);
	CPPUNIT_ASSERT(test.type == aidecollision::COLLISION_AUCUNE);

	visiteur_.rayon_ = 30;
	visiteur_.position_ = { 30, 30, 0 };
	test = visiteur_.visiterNoeudQuadrilatere(noeudRectangle);
	CPPUNIT_ASSERT(test.type != aidecollision::COLLISION_AUCUNE);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////