#ifndef SHARECOUNT
#define SHARECOUNT

#include <string>
#include <list>
#include "Compte.h"

class ShareCount{
public:

    ShareCount();//Constructeur
    virtual ~ShareCount();
    void ajouterCompte(std::string nom,std::string email);

private:

    std::list<Compte> listeCompte;

};

#endif // SHARECOUNT
