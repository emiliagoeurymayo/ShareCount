#include <string>
#include <list>
#include <algorithm>
#include "serveurMail.h"

/** @brief Classe Serveur mail
 **
 **Sert à repliquer un ServeurMail
 **
 ** @version 0.6
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

// Permet de vérifier si le charactère est une lettre ou pas
bool isChar(char c){return ((c >= 'a' && c <= 'z')|| (c >= 'A' && c <= 'Z'));}
// Permet de vérifier si le charactère est un nombre ou pas
bool isDigit(const char c){return (c >= '0' && c <= '9');}

// Permet de vérifier la validité du mail
bool ServeurMail::is_valid(std::string email)
{
    //Premier charactère doit etre une lettre
    if (!isChar(email[0])) {
        return 0;
    }

    // Permet de stocker la position de @ et .
    int a = -1, point = -1;

    // Parcour le mail pour identifier la position de @ et .
    for (std::string::size_type i = 0;i < email.length(); i++) {
        if (email[i] == '@') {a = i;}
        else if (email[i] == '.') {point = i;}
    }

    // Si aucun des deux présent
    if (a == -1 || point == -1)
        return 0;

    // Si le point est présent aprés @
    if (a > point)
        return 0;

    // Si aucun domaine défini
    if (point==a+1)
        return 0;

    // Si le point est présent à la fin (rien aprés .)
    return !(point >= (email.length() - 1));
}
