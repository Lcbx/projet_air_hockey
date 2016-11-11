////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigProfilsTest.cpp
/// @author Arthur
/// @date 2016-11-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigProfilsTest.h"
#include "ConfigProfils.h"
#include "FacadeModele.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(ConfigProfilsTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigProfilsTest::setUp()
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
void ConfigProfilsTest::setUp()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigProfilsTest::tearDown()
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
void ConfigProfilsTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigProfilsTest::testGestionProfils()
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
void ConfigProfilsTest::testGestionProfils()
{

	FacadeModele::obtenirInstance()->getConfigProfils()->setProfil("Bohort", 5, 0.5);

	CPPUNIT_ASSERT(FacadeModele::obtenirInstance()->getConfigProfils()->getVitesse("Bohort") == 5 &&
		FacadeModele::obtenirInstance()->getConfigProfils()->getProbabilite("Bohort") == 0.5);

	FacadeModele::obtenirInstance()->getConfigProfils()->supprimerProfil("Bohort");

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
