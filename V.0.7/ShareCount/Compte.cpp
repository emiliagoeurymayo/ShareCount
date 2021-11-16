#include <string>
#include <iostream>
#include "Compte.h"

Compte::Compte(std::string nom, std::string prenom, std::string email, std::string mdp) : m_nom(nom), m_prenom(prenom), m_email(email), m_mdp(mdp)
{

}

Compte::~Compte(){}

void Compte::afficher()
{
    std::cout << "Nom : " << m_nom << "Prénom" << m_prenom << " email : " << m_email << "Mot de passe" << m_mdp << std::endl;
}

void setMotDePasse(std::string mdp)
{
  m_mdp(mdp)
}

std::string getMotDePasse()
{
    return m_mdp;
}

void setEmail(std::string email)
{
    m_email(email);
}
std::string getEmail()
{
    return m_email;
}
