#include "TestCompte.h"
#include "Compte.h"

TestCompte::TestCompte()
{
    void testAfficherCompte();
}

void TestCompte::testAfficherCompte()
{
    Compte c("MOSELLE", "mosellemarieluc@gmail.com");
    c.afficher();
}

TestCompte::~TestCompte(){}
