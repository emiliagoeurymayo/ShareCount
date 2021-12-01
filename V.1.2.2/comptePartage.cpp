#include <string>
#include <iostream>
#include "compte.h"
#include "comptePartage.h"

ComptePartage::ComptePartage(std::string nom)
{
    m_nom = nom;
    //m_participants = vector();
}

ComptePartage::~ComptePartage()
{

}

/// @brief Accesseur de l'attribut nom de la classe Cagnotte
std::string ComptePartage::getNom()
{
    return m_nom;
}

/// @brief Mutateur de l'attribut nom de la classe Cagnotte
void ComptePartage::setNom(std::string nom)
{
    m_nom = nom;
}
/*
/// @brief Accesseur de la liste des participants
std::vector ComptePartage::getParticipants()
{
    return m_participants;
}

/// @brief Accesseur d'un participant de la liste
std::string ComptePartage::getParticipant(int index)
{
    m_participants.at(index);
}

/// @brief Ajoute un participant à la liste
void ComptePartage::ajouterParticipant(std::string participant)
{
    m_participants.push_back(participant);
}

/// @brief Retire un participant de la liste
void ComptePartage::retirerParticipant(int index)
{
    m_participants.erase(index);
}
*/
