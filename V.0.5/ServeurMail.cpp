#include <string>
#include <list>
#include <algorithm>
#include "ServeurMail.h"

ServeurMail::ServeurMail():listeMailValide(std::list<std::string>{})
{

}

ServeurMail::~ServeurMail(){}

void ServeurMail::ajouterEmail(std::string email){
    listeMailValide.push_front(email);
}

bool ServeurMail::getStatusEmail(std::string email){
    std::list<std::string> :: iterator pos;
    pos = find(listeMailValide.begin() , listeMailValide.end() , email);
        if(pos != listeMailValide.end() )
            return true;
        else
            return false;
}
