#ifndef GESTIONNAIREDIALOGUE
#define GESTIONNAIREDIALOGUE

#include <string>
#include "ServeurMail.h"
#include "ShareCount.h"

/** @brief La classe GestionnaireDialogue gère les interactions 
 **
 ** Elle contient 
 **  @ref GestionnaireDialogue(ShareCount, ServeurMail)
 **  @ref verifInformations(String, String) 
 **  @ref envoiEmail(String)
 **  @ref verifValidationEmail(String, String) 
 ** @version 0.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo 
 **/

class GestionnaireDialogue{
public:
    ///@brief Constructeur
    GestionnaireDialogue(ShareCount sharecount,ServeurMail serveurmail);//Constructeur
    
    ///@brief Destructeur
    virtual ~GestionnaireDialogue();

    ///@brief verifie les informations
    void verifInformations(std::string nom,std::string email);

    ///@brief envoie un email
    void envoiEmail(std::string email);

    ///@brief verifie l'email de validation
    void verifValidationEmail(std::string nom,std::string email);

private:

    ShareCount m_sharecount;
    ServeurMail m_serveurmail;

};

#endif // GESTIONNAIREDIALOGUE
