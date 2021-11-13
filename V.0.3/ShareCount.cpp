#include <string>
#include <list>
#include "ShareCount.h"
#include "Compte.h"


/** @brief Classe Sharecount
 **
 ** classe de l'application 
 **  
 ** @version 0.3
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
void ShareCount::ajouterCompte(std::string nom,std::string email){
    Compte c(nom,email);
    listeCompte.push_front(c);
    c.afficher();
}
