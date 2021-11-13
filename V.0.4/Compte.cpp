#include <string>
#include <iostream>
#include "Compte.h"

/** @brief Classe Compte
 **
 ** Sert à la création d'un compte
 **
 ** @version 0.4
 **
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo 
 **/

/// @brief Constructeur
///
/// @param nom : nom de l'utilisateur
///@param email : email de l'utilisateur
Compte::Compte(std::string nom, std::string email) : m_nom(nom), m_email(email)
{

}

///@brief Destructeur
Compte::~Compte(){}


///@brief Affiche les informations du compte 
void Compte::afficher()
{
    std::cout << "Nom : " << m_nom << " email : " << m_email << std::endl;
}