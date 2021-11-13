#ifndef COMPTE
#define COMPTE

#include <string>


/** @brief La classe Compte permet la création de tous les comptes de l'application
 **
 ** Elle contient 
 **  @ref Compte(string, string)
 **
 ** @version 0.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo 
 **/
class Compte{
public:
    ///@brief Constructeur
    Compte(std::string nom,std::string email);

    //@brief Desctructeur 
    virtual ~Compte();

    ///@brief Affiche les informations du compte 
    void afficher();

private:

    std::string m_nom;
    std::string m_email;

};

#endif
