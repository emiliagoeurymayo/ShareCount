#ifndef SHARECOUNT
#define SHARECOUNT

#include <string>
#include <list>
#include "compte.h"

/** @brief Classe ShareCount
 **
 ** Elle contient
 **  @ref ShareCount()
 **  @ref ajouterCompte(string, string, string, string, string)
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/
class ShareCount{
public:
    ///@brief Constructeur
    ShareCount();
    ///@brief Destructeur
    virtual ~ShareCount();
    ///@brief Ajoute un compte
    void ajouterCompte(std::string nom,std::string prenom,std::string email,std::string mdp,std::string pseudo);

private:

    std::list<Compte> listeCompte;

};

#endif // SHARECOUNT
