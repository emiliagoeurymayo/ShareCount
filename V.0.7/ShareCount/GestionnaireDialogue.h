#ifndef GESTIONNAIREDIALOGUE
#define GESTIONNAIREDIALOGUE

#include <string>
#include "ServeurMail.h"
#include "ShareCount.h"

class GestionnaireDialogue{
public:

    GestionnaireDialogue(ShareCount sharecount,ServeurMail serveurmail);//Constructeur
    virtual ~GestionnaireDialogue();
    int verifInformations(std::string nom,std::string email);
    void envoiEmail(std::string email);
    void verifValidationEmail(std::string nom,std::string email);

private:

    ShareCount m_sharecount;
    ServeurMail m_serveurmail;

};

#endif // GESTIONNAIREDIALOGUE
