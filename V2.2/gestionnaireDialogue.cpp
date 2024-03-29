#include <string>
#include <list>
#include <iostream>
#include "gestionnaireDialogue.h"
#include "shareCount.h"
#include "serveurMail.h"
#include <limits>

GestionnaireDialogue::GestionnaireDialogue(ShareCount shareCount, ServeurMail serveurMail,gestionnaireBDD gbdd):m_sharecount(shareCount),m_serveurmail(serveurMail),m_gbdd(gbdd)
{

}

GestionnaireDialogue::GestionnaireDialogue()
{

}

GestionnaireDialogue::~GestionnaireDialogue(){}

void GestionnaireDialogue::verifInformations(std::string nom,std::string email,std::string mdp,std::string prenom,std::string pseudo,bool mailvalide){
    if(!nom.empty() && !email.empty() && !mdp.empty() && !prenom.empty() && !pseudo.empty()){
        m_nom=nom;
        m_prenom=prenom;
        m_email=email;
        m_pseudo=pseudo;
        m_mdp=mdp;
        this->envoiEmail(mailvalide);
    }
    else{
        std::cout << "Un des champs est invalide (EmptyError)" << std::endl;
    }
}
void GestionnaireDialogue::envoiEmail(bool mailvalide){
    if(mailvalide){
        this->m_serveurmail.ajouterEmail(m_email);
        verifValidationEmail();
    }
    else {
        std::cout << "Veuillez valider votre mail\n";
    }
}

void GestionnaireDialogue::verifValidationEmail(){
    if(m_serveurmail.getStatusEmail(m_email)){
        m_sharecount.ajouterCompte(m_nom,m_prenom,m_email,m_mdp,m_pseudo);
        m_gbdd.addUtil(m_prenom,m_nom,m_email,m_mdp,"ABC");
    }
}

bool GestionnaireDialogue::verifConnexion(std::string email,std::string mdp){
    return m_gbdd.informationConnexionValide(email,mdp);
}
