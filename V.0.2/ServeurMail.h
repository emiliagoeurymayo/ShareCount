#ifndef SERVEURMAIL
#define SERVEURMAIL

#include <string>
#include <list>


/** @brief La classe ServeurMail permet l'envoi de mails
 **
 ** Elle contient 
 **  @ref ServeurMail(string, string)
 **  @ref ajouterMail(string)
 **  @ref getStatusEmail(String)
 ** 
 ** @version 0.2
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo 
 **/
class ServeurMail{
public:
    ///@brief Constructeur
    ServeurMail();

    ///@brief Destructeur
    virtual ~ServeurMail();
    ///@ Ajoute un mail à la liste des mails connus
    void ajouterEmail(std::string email);

    ///@ Recupère le status d'un email
    bool getStatusEmail(std::string email);

private:

    std::list<std::string> listeMailValide;

};

#endif // SERVEURMAIL
