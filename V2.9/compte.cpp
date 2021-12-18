#include <string>
#include <iostream>
#include "compte.h"


/** @brief Classe Compte
 **
 ** Sert à la création d'un compte
 **
 ** @version 2.4
 **
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/

/// @brief Constructeur
///
/// @param nom : nom de l'utilisateur
///@param email : email de l'utilisateur
Compte::Compte(std::string nom,std::string prenom,std::string email,std::string mdp,std::string pseudo) : m_nom(nom),m_prenom(prenom), m_email(email),m_mdp(mdp),m_pseudo(pseudo)
{

}

///@brief Destructeur
Compte::~Compte(){}

///@brief Affiche les informations du compte
void Compte::afficher()
{
    std::cout << "Nom: " << m_nom << "/ Prenom: " << m_prenom <<  " / email: " << m_email << "/ Pseudo: " << m_pseudo << " / mdp: " << m_mdp << std::endl;
}

/// @brief Setter du mot de passe d'un Compte
///
/// @param mdp : nouveau mot de passe
void Compte::setMotDePasse(std::string mdp)
{
    m_mdp=mdp;
}

/// @brief Getter du mot de passe d'un Compte
///
/// @return m_mdp : mot de passe du Compte
std::string Compte::getMotDePasse()
{
    return m_mdp;
}

/// @brief Setter de l'email d'un Compte
///
/// @param email : nouveau email
void Compte::setEmail(std::string email)
{
    m_email=email;
}

/// @brief Getter de l'eamil d'un Compte
///
/// @return m_email : email du Compte
std::string Compte::getEmail()
{
    return m_email;
}
