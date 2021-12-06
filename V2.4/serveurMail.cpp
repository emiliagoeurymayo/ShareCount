#include <string>
#include <list>
#include <algorithm>
#include "serveurMail.h"

/** @brief Classe Serveur mail
 **
 **Sert à répliquer un ServeurMail
 **
 ** @version 2.4
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
/// @param string email : email à
bool ServeurMail::getStatusEmail(std::string email){
    std::list<std::string> :: iterator pos;
    pos = find(listeMailValide.begin() , listeMailValide.end() , email);
        if(pos != listeMailValide.end() )
            return true;
        else
            return false;
}

///@brief Permet de vérifier si le charactère est une lettre ou pas
///
/// @param char c : charactere a vérifier
/// @return true si le charactère est une lettre
bool isChar(char c){return ((c >= 'a' && c <= 'z')|| (c >= 'A' && c <= 'Z'));}

///@brief Permet de vérifier si le charactère est un nombre ou pas
///
/// @param char c : charactere a vérifier
/// @return true si le charactère est un nombre ou pas
bool isDigit(const char c){return (c >= '0' && c <= '9');}

///@brief Permet de vérifier la validité du mail
///
/// @param string : email a analyser
/// @return true si l'email est valide (commence par une lettre,possède un @ et un ., le point n'est pas le dernier charactère, l'eamil possède un domaine et l'@ se situe avant le point)
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
    std::string::size_type temp_point = point;
    return !(temp_point >= (email.length() - 1));
}
