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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
/// s'assurer que la valeur sauvegardée a bien été restaurée du fichier
/// XML, restaurer la valeur par défaut.
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
