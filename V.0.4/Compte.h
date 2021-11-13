#ifndef COMPTE
#define COMPTE

#include <string>

class Compte{
public:

    Compte(std::string nom,std::string email);//Constructeur
    virtual ~Compte();
    void afficher();

private:

    std::string m_nom;
    std::string m_email;

};

#endif
