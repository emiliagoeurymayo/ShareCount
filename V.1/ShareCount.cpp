#include <string>
#include <list>
#include <iostream>
#include "ShareCount.h"
#include "Compte.h"

/** @brief Classe Sharecount
 **
 ** classe de l'application
 **
 ** @version 0.6
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/

///@brief Constructeur
///
///@param list : liste de comptes
ShareCount::ShareCount():listeCompte(std::list<Compte>{})
{

}

///@brief Destructeur
ShareCount::~ShareCount(){}


///@brief ajoute un compte
///
///@param string nom : nom de l'utilisateur
///@param string email : email de l'utilisateur
void ShareCount::ajouterCompte(std::string nom,std::string email,std::string mdp){
    Compte c(nom,email,mdp); // MARIE LUC : Oublie d'ajout d'un mdp
    listeCompte.push_front(c);
    std::cout << "Ajout reussi pour le compte : " << std::endl;
    c.afficher();
}
