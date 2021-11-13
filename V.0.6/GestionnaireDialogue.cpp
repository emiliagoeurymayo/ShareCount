#include <string>
#include <list>
#include <iostream>
#include "GestionnaireDialogue.h"
#include "ShareCount.h"
#include "ServeurMail.h"

GestionnaireDialogue::GestionnaireDialogue(ShareCount shareCount, ServeurMail serveurMail):m_sharecount(shareCount),m_serveurmail(serveurMail)
{

}

GestionnaireDialogue::~GestionnaireDialogue(){}

void GestionnaireDialogue::verifInformations(std::string nom,std::string email){
    if(!nom.empty() && !email.empty()){
        this->envoiEmail(nom,email);
    }
    else{
        std::cout << "Un des champs est invalide (EmptyError)" << std::endl;
    }
}
void GestionnaireDialogue::envoiEmail(std::string nom,std::string email){
    int n;
    std::cout << "Bonjour " << nom << " votre mail est il valide ? (1 pour oui / 0 pour non)\n";
    std::cin >> n;
    if(n==1){
        this->m_serveurmail.ajouterEmail(email);
        verifValidationEmail(nom,email);
    }
    else if(n==0){
        std::cout << "Veuillez valider votre mail\n";
        this->envoiEmail(nom,email);
    }
    else{
        std::cout << "Veuillez taper 0 ou 1 uniquement\n";
        this->envoiEmail(nom,email);
    }
}
void GestionnaireDialogue::verifValidationEmail(std::string nom,std::string email){
    if(m_serveurmail.getStatusEmail(email)){
        m_sharecount.ajouterCompte(nom,email);
    }
}
