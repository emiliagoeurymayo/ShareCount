#include <string>
#include <list>
#include <iostream>
#include "gestionnaireDialogue.h"
#include "shareCount.h"
#include "serveurMail.h"
#include <limits>

/** @brief Classe GestionnaireDialogue
 **
 ** Modele de notre application MVC
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/

///@brief Constructeur
///
///@param shareCount : sharecount
///@param serveurMail : serveur mail
///@param gbdd : gestionnaire de la base de donnée
GestionnaireDialogue::GestionnaireDialogue(ShareCount shareCount, ServeurMail serveurMail,gestionnaireBDD gbdd):m_sharecount(shareCount),m_serveurmail(serveurMail),m_gbdd(gbdd)
{

}

///@brief Constructeur vide
GestionnaireDialogue::GestionnaireDialogue()
{

}

///@brief Destructeur
GestionnaireDialogue::~GestionnaireDialogue(){}

///@brief Verifie la véracité des informations saisies dans les champs de texte de l'interface Inscription
///
/// @param nom le nom a attribuer au compte
/// @param prenom le prenom a attribuer au compte
/// @param email l'email a attribuer au compte
/// @param mdp le mot de passe a attribuer au compte
/// @param pseudo le pseudo a attribuer au compte
/// @param mailvalide permet de simuler la validation ou non de l'adresse email lors de l'inscription
void GestionnaireDialogue::verifInformations(std::string nom,std::string email,std::string mdp,std::string prenom,std::string pseudo,bool mailvalide){
    if(!nom.empty() && !email.empty() && !mdp.empty() && !prenom.empty() && !pseudo.empty()){
        if(m_serveurmail.is_valid(email)){
            m_nom=nom;
            m_prenom=prenom;
            m_email=email;
            m_pseudo=pseudo;
            m_mdp=mdp;
            this->envoiEmail(mailvalide);
        }
        else{
            std::cout << "eMail saisi invalide" << std::endl;
        }
    }
    else{
        std::cout << "Un des champs est invalide (EmptyError)" << std::endl;
    }
}

///@brief "Envoie" le mail de validation
///
/// @param mailvalide permet de simuler la validation ou non de l'adresse email lors de l'inscription
void GestionnaireDialogue::envoiEmail(bool mailvalide){
    if(mailvalide){
        this->m_serveurmail.ajouterEmail(m_email);
        verifValidationEmail();
    }
    else {
        std::cout << "Veuillez valider votre mail\n";
    }
}

///@brief Ajoute le compte à la base de donnée aprés la vérification
void GestionnaireDialogue::verifValidationEmail(){
    if(m_serveurmail.getStatusEmail(m_email)){
        if(!m_gbdd.addUtil(m_prenom,m_nom,m_email,m_mdp,"ABC")){
            qDebug() << "eMAil déja associe a un compte";
        }
        else{
            m_sharecount.ajouterCompte(m_nom,m_prenom,m_email,m_mdp,m_pseudo);
        }
    }
}

///@brief Retourne l'id de l'utilisateur defini à l'aide de la base de donnée, 0 sinon
///
/// @param string email : email à vérifier
/// @param string mdp : mot de passe associé à l'email
/// @return l'id de l'utilisateur defini à l'aide de la base de donnée, 0 sinon
int GestionnaireDialogue::verifConnexion(std::string email,std::string mdp){
    m_email = email;
    m_mdp = mdp;
    return m_gbdd.informationConnexionValide(email,mdp);
}

///@brief Identifie le nom et prénom de l'utilisateur possédant l'id défini en paramètre
///
/// @param int id : id de l'utilisateur à identifier
/// @return retourne le nom et prénom de l'utilisateur possédant l'id défini en paramètre
QMap<QString,QString> GestionnaireDialogue::identifierUtilisateur(int id){
    return m_gbdd.getUtil(id);
}

///@brief Getter des participants d'un compte partagé
///
/// @param int typeCompte : id du type de compte à vérifier
/// @param int idCompte : id du compte à vérifier
/// @return retourne une liste contenant les participants d'un compte partagé
QMap<QString,QString> GestionnaireDialogue::getParticipants(int typeCompte, int idCompte){
    return m_gbdd.getParticipants(typeCompte, idCompte);
}

///@brief Retourne le nom du compte identifié par l'id en paramètre
///
/// @param int id : id du compte à identifier
/// @return retourne le nom du compte identifier par l'id en paramètre
QString GestionnaireDialogue::getNomCompte(int id){
    return m_gbdd.getNomCompte(id);
}

///@brief Retourne le nom de la cagnotte identifiée par l'id en paramètre
///
/// @param int id : id de la cagnotte à identifier
/// @return retourne le nom du compte identifier par l'id en paramètre
QString GestionnaireDialogue::getNomCagnotte(int id){
    return m_gbdd.getNomCagnotte(id);
}


///@brief Retourne la liste des comptes auquel l'utilisateur participe
///
/// @return retourne une liste contenant les comptes auquel l'utilisateur participe
QMap<int, QString> GestionnaireDialogue::getListeCompte(){
    return m_gbdd.getListeCompte(m_email);
}

///@brief Retourne la liste des comptes auquel l'utilisateur participe
///
/// @return retourne une liste contenant les comptes auquel l'utilisateur participe
QMap<int, QString> GestionnaireDialogue::getListeCagnotte(){
    return m_gbdd.getListeCagnotte(m_email);
}

///@brief Ajoute un participant à un compte partagé
///
/// @param QString email : participant à ajouter
/// @param int idCompte : id du compte à vérifier
/// @return retourne True si l'operation c'est bien effectuée
bool GestionnaireDialogue::addPartCompt(QString email, int idCompte){
    return m_gbdd.addPartCompt(email,idCompte);

}

///@brief Ajoute un participant à une cagnotte
///
/// @param QString email : participant à ajouter
/// @param int idCagnotte : id du compte à vérifier
/// @return retourne True si l'operation c'est bien effectuée
bool GestionnaireDialogue::addPartCagnotte(QString email, int idCagnotte){
    return m_gbdd.addPartCagnotte(email, idCagnotte);
}

///@brief Retourne une liste d'actions effectuées en rapport avec la cagnotte
///
/// @param int idCagnotte : id de la cagnotte en question
QStringList GestionnaireDialogue::getListeHistorique(int idCagnotte){
    return this->m_gbdd.getListeHistorique(idCagnotte);
}

///@brief Retourne les fonds disponibles d'une cagnotte
///
/// @param int idCagnotte : id de la cagnotte en question
int GestionnaireDialogue::getFondsDispo(int idCagnotte){
    return m_gbdd.getFondsDispo(idCagnotte);
}

///@brief Ajoute de l'argent à la cagnotte
///
/// @param fond : montant à rajouter
/// @param m_id : id de l'utilisateur
/// @param m_idcagnotte : id de la cagnotte
bool GestionnaireDialogue::addFonds(QString fond, int m_id, int m_idcagnotte){
    return m_gbdd.addFonds(fond, m_id, m_idcagnotte);
}

///@brief Ajoute de l'argent à la cagnotte
///
/// @param m_id : id de l'utilisateur
/// @param m_idcagnotte : id de la cagnotte
bool GestionnaireDialogue::retirerFonds(QString fond, int m_id, int m_idcagnotte){
    return m_gbdd.retirerFonds(fond, m_id, m_idcagnotte);

}
