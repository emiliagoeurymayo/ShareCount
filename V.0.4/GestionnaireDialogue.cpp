#include <string>
#include <list>
#include "GestionnaireDialogue.h"
#include "ShareCount.h"
#include "ServeurMail.h"

GestionnaireDialogue::GestionnaireDialogue(ShareCount shareCount, ServeurMail serveurMail):m_sharecount(shareCount),m_serveurmail(serveurMail)
{

}

GestionnaireDialogue::~GestionnaireDialogue(){}

void GestionnaireDialogue::verifInformations(std::string nom,std::string email){
    //TODO verifier la formalation du nom et de l'email.
    this->envoiEmail(email);
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
