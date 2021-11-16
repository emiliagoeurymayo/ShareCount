#include <string>
#include <list>
#include "GestionnaireDialogue.h"
#include "ShareCount.h"
#include "ServeurMail.h"

GestionnaireDialogue::GestionnaireDialogue(ShareCount shareCount, ServeurMail serveurMail):m_sharecount(shareCount),m_serveurmail(serveurMail)
{

}

GestionnaireDialogue::~GestionnaireDialogue(){}

int GestionnaireDialogue::verifInformations(std::string nom,std::string email){
    if(!nom.empty() && !email.empty()){
        this->envoiEmail(email);
        return 0;
    }
    else{
        return 1;
    }
}
void GestionnaireDialogue::envoiEmail(std::string email){
    if(true){
        this->m_serveurmail.ajouterEmail(email);
    }
}
void GestionnaireDialogue::verifValidationEmail(std::string nom,std::string email){
    if(m_serveurmail.getStatusEmail(email)){
        m_sharecount.ajouterCompte(nom,email);
    }
}
