#include <string>
#include <iostream>
#include "Compte.h"


/** @brief Classe Compte
 **
 ** Sert à la création d'un compte
 **
 ** @version 0.6
 **
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/

/// @brief Constructeur
///
/// @param nom : nom de l'utilisateur
/// @param email : email de l'utilisateur
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


void Compte::setMotDePasse(std::string mdp)//MARIE LUC : Oublie pas les Compte::
{
    m_mdp=mdp;//MARIE LUC : C'est comme ça que l'on défini un setter
}

std::string Compte::getMotDePasse()
{
    return m_mdp;
}

void Compte::setEmail(std::string email)
{
    m_email=email;
}
std::string Compte::getEmail()
{
    return m_email;
}
