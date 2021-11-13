#ifndef TESTGESTIONNAIREDIALOGUE_H
#define TESTGESTIONNAIREDIALOGUE_H
#include "GestionnaireDialogue.h"

class TestGestionnaireDialogue
{
public:
    TestGestionnaireDialogue();
    virtual ~TestGestionnaireDialogue();
    void testVerifInformations();
    void testEnvoiEmail();
    void testVerifValidationEmail();
};

#endif // TESTGESTIONNAIREDIALOGUE_H
