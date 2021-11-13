#include <string>
#include <list>
#include <algorithm>
#include "ServeurMail.h"



/** @brief Classe Serveur mail
 **
 **Sert à repliquer un ServeurMail 
 **  
 ** @version 0.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo 
 **/


/// @brief Constructeur
///
/// @param liste : liste d'email
ServeurMail::ServeurMail():listeMailValide(std::list<std::string>{})
{

}

///@brief Destructeur
ServeurMail::~ServeurMail(){}


///@brief Ajoute un mail à la liste des mails connus 
///
///@param string email : email à ajouter
void ServeurMail::ajouterEmail(std::string email){
    listeMailValide.push_front(email);
}

///@brief 
///
///@param string email : email à 
bool ServeurMail::getStatusEmail(std::string email){
    std::list<std::string> :: iterator pos;
    pos = find(listeMailValide.begin() , listeMailValide.end() , email);
        if(pos != listeMailValide.end() )
            return true;
        else
            return false;
}
