#include "TestServeurMail.h"

TestServeurMail::TestServeurMail()
{
    void testAjouterEmail();
    void testGetStatusEmail();
}

void TestServeurMail::testAjouterEmail()
{
    ServeurMail sm;
    sm.ajouterEmail("mon email");
    // Getter de la liste des mails du ServeurMail pour tester cette fonction
}

void TestServeurMail::testGetStatusEmail()
{
    ServeurMail sm;
    if(sm.getStatusEmail("mon email") == 0)
    {
        printf("Success !\n");
    }
    else
    {
        printf("Failure !\n");
    }
}

TestServeurMail::~TestServeurMail(){}
