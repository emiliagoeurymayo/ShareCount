#ifndef SERVEURMAIL
#define SERVEURMAIL

#include <string>
#include <list>



/** @brief La classe ServeurMail permet l'envoi de mails
 **
 ** Elle contient
 **  @ref ServeurMail()
 **  @ref void ajouterMail(string)
 **  @ref bool getStatusEmail(String)
 **  @ref bool is_valid(string)
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/
class ServeurMail{
public:

    ///@brief Constructeur
    ServeurMail();
    ///@brief Destructeur
    virtual ~ServeurMail();
    ///@brief Ajoute un mail à la liste des mails connus
    void ajouterEmail(std::string email);
    ///@brief Recupère le status d'un email
    bool getStatusEmail(std::string email);
    ///@brief Vérifie la validité de l'eamil
    bool is_valid(std::string email);

private:

    std::list<std::string> listeMailValide;

};

#endif // SERVEURMAIL
