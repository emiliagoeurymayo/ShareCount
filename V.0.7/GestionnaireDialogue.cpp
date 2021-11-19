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

void GestionnaireDialogue::verifInformations(std::string nom,std::string email,std::string mdp){
    if(!nom.empty() && !email.empty()){
        m_nom=nom;
        m_email=email;
        m_mdp=mdp;
        this->envoiEmail();
    }
    else{
        std::cout << "Un des champs est invalide (EmptyError)" << std::endl;
    }
}
void GestionnaireDialogue::envoiEmail(){
    int n;
    std::cout << "Bonjour " << m_nom << " votre mail est il valide ? (1 pour oui / 0 pour non)\n";
    std::cin >> n;
    if(n==1){
        this->m_serveurmail.ajouterEmail(m_email);
        verifValidationEmail();
    }
    else if(n==0){
        std::cout << "Veuillez valider votre mail\n";
        this->envoiEmail();
    }
    else{
        std::cout << "Veuillez taper 0 ou 1 uniquement\n";
        this->envoiEmail();
    }
}
void GestionnaireDialogue::verifValidationEmail(){
    if(m_serveurmail.getStatusEmail(m_email)){
        m_sharecount.ajouterCompte(m_nom,m_email,m_mdp);
    }
}
