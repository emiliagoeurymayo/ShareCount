#include <string>
#include <iostream>
#include "compte.h"
#include "cagnotte.h"



/** @brief Classe Cagnotte
 **
 ** Sert à la création d'une cagnotte
 **
 ** @version 1.2.2
 **
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/


/// @param string nom: Le nom de la cagnotte.
/// @brief Constructeur Cagnotte.
Cagnotte::Cagnotte(std::string nom)
{
    m_nom = nom;
    //m_participants = vector();
    m_montant = 0; // Montant par défaut
}

/// @brief Destructeur
Cagnotte::~Cagnotte()
{

}

/// @param int sommme: La somme qu'un utilisateur veut ajouter au montant de la cagnotte.
/// @brief Ajoute la somme donnée en paramètre au montant total.
void Cagnotte::ajouterSomme(int somme)
{
    m_montant = m_montant + somme;
}

/// @param int sommme: La somme qu'un utilisateur veut retirer au montant de la cagnotte.
/// @brief Retire la somme donnée en paramètre au montant total.
void Cagnotte::retirerSomme(int somme)
{
    if(somme > m_montant)
    {
        printf("Impossible de retirer la somme demandée ! \n");
    }
    else
    {
       m_montant = m_montant - somme;
    }

}

std::string Cagnotte::getNom()
{
    return m_nom;
}

void Cagnotte::setNom(std::string nom)
{
    m_nom = nom;
}

/*
/// @brief Accesseur de la liste des participants
std::vector Cagnotte::getParticipants()
{
    return m_participants;
}

/// @brief Accesseur d'un participant de la liste
std::string Cagnotte::getParticipant(int index)
{
    return m_participants.at(index);
}

/// @brief Ajoute un participant à la liste
void Cagnotte::ajouterParticipant(std::string participant)
{
    m_participants.push_back(participant);
}

/// @brief Retire un participant de la liste
void retirerParticipant(int index)
{
    m_participant.erase(index);
}
*/
