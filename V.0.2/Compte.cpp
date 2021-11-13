#include <string>
#include <iostream>
#include "Compte.h"

Compte::Compte(std::string nom, std::string email) : m_nom(nom), m_email(email)
{

}

Compte::~Compte(){}

void Compte::afficher()
{
    std::cout << "Nom : " << m_nom << " email : " << m_email << std::endl;
}
