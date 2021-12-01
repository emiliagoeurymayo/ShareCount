#ifndef GESTIONNAIREDIALOGUE
#define GESTIONNAIREDIALOGUE

#include <string>
#include "ServeurMail.h"
#include "ShareCount.h"

class GestionnaireDialogue{
public:

    GestionnaireDialogue(ShareCount sharecount,ServeurMail serveurmail);//Constructeur
    GestionnaireDialogue();//Def constructor
    virtual ~GestionnaireDialogue();
    void verifInformations(std::string nom,std::string email,std::string mdp,std::string prenom,std::string pseudo);
    void envoiEmail();
    void verifValidationEmail();

private:

    ShareCount m_sharecount;
    ServeurMail m_serveurmail;
    std::string m_nom;
    std::string m_prenom;
    std::string m_email;
    std::string m_mdp; // Mot de Passe
    std::string m_pseudo;   //pseudo

};

#endif // GESTIONNAIREDIALOGUE
