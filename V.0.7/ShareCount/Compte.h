#ifndef COMPTE
#define COMPTE

#include <string>

class Compte{
public:

    Compte(std::string nom, std::string prenom, std::string email, std::string mdp);//Constructeur
    virtual ~Compte();
    void afficher();
    void setMotDePasse(std::string mdp);
    std::string getMotDePasse();
    void setEmail(std::string email);
    std::string getEmail();

private:

    std::string m_nom;
    std::string m_email;
    std::string m_prenom;
    std::string m_mdp; // Mot de Passe
    std::string m_pseudo;
    int m_identifiant;

};

#endif
