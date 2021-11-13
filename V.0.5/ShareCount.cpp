#include <string>
#include <list>
#include "ShareCount.h"
#include "Compte.h"

ShareCount::ShareCount():listeCompte(std::list<Compte>{})
{

}

ShareCount::~ShareCount(){}

void ShareCount::ajouterCompte(std::string nom,std::string email){
    Compte c(nom,email);
    listeCompte.push_front(c);
    c.afficher();
}
