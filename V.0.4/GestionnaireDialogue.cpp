#include <string>
#include <list>
#include "GestionnaireDialogue.h"
#include "ShareCount.h"
#include "ServeurMail.h"


/** @brief Classe GestionnaireDialogue
 **
 ** permet comunication
 **
 ** @version 0.4
 **
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo 
 **/


///@brief Contructeur
///
///@param sharecount : ShareCount
///@param serveurMail : ServeurMail
GestionnaireDialogue::GestionnaireDialogue(ShareCount shareCount, ServeurMail serveurMail):m_sharecount(shareCount),m_serveurmail(serveurMail)
{

}

///@brief Destructeur
GestionnaireDialogue::~GestionnaireDialogue(){}

///@brief Verifie informations données
///
///@param nom : String
///@param email : String 
void GestionnaireDialogue::verifInformations(std::string nom,std::string email){
    //TODO verifier la formalation du nom et de l'email.
    this->envoiEmail(email);
}

///@brief envoi un email
///
///@param email : String
void GestionnaireDialogue::envoiEmail(std::string email){
    if(true){
        this->m_serveurmail.ajouterEmail(email);
    }
}

///@brief verifie la validation d'un email
///
///@param nom : String 
///@param email : String 
void GestionnaireDialogue::verifValidationEmail(std::string nom,std::string email){
    if(m_serveurmail.getStatusEmail(email)){
        m_sharecount.ajouterCompte(nom,email);
    }
}
