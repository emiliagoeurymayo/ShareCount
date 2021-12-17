#include <string>
#include <iostream>
#include "compte.h"
#include "comptePartage.h"

ComptePartage::ComptePartage(std::string nom, QList<std::string> list)
{
    m_nom = nom;
    m_participants = list;
    m_depenses = list;
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

/// @brief Accesseur de la liste des participants
QList<std::string> ComptePartage::getParticipants()
{
    return m_participants;
}

/// @brief Accesseur d'un participant de la liste
std::string ComptePartage::getParticipant(int index)
{
    return m_participants.value(index);
}

/// @brief Ajoute un participant à la liste
void ComptePartage::ajouterParticipant(std::string participant)
{
    m_participants.append(participant);
}

/// @brief Retire un participant de la liste
void ComptePartage::retirerParticipant(int index)
{
    m_participants.removeAt(index);
}

/// @brief Ajoute une dépense
void ComptePartage::ajouterDepense(std::string depense)
{
    m_depenses.append(depense);
}

/// @brief Retire une dépense de la liste
void ComptePartage::retirerDepense(int index)
{
    m_depenses.removeAt(index);
}

