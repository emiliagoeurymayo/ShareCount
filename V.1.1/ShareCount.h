#ifndef SHARECOUNT
#define SHARECOUNT

#include <string>
#include <list>
#include "Compte.h"

/** @brief Classe ShareCount
 **
 ** Elle contient
 **  @ref ShareCount()
 **  @ref ajouterCompte(string, string)
 **
 ** @version 0.6
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/
class ShareCount{
public:

    ShareCount();
    virtual ~ShareCount();
    void ajouterCompte(std::string nom,std::string prenom,std::string email,std::string mdp,std::string pseudo);

private:

    std::list<Compte> listeCompte;

};

#endif // SHARECOUNT
