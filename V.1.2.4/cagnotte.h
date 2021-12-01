#ifndef CAGNOTTE_H
#define CAGNOTTE_H

#include <string>
#include <vector>




/** @brief Classe Cagnotte
 **
 ** Sert à la création d'une cagnotte
 **
 ** @version 1.2.2
 **
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/


class Cagnotte
{
    /// @brief Constructeur
    public:
        Cagnotte(std::string nom);

        /// @brief Destructeur
        virtual ~Cagnotte();

        /// @brief Ajouter une somme au montant total de la cagnotte
        void ajouterSomme(int somme);

        ///@brief Retirer une somme au montant total de la cagnotte
        void retirerSomme(int somme);


        /// @brief Accesseur de l'attribut nom de la classe Cagnotte
        std::string getNom();

        /// @brief Mutateur de l'attribut nom de la classe Cagnotte
        void setNom(std::string nom);

        /// @brief Accesseur de la liste des participants
        //std::vector getParticipants();

        /// @brief Accesseur d'un participant de la liste
        std::string getParticipant(int index);

        /// @brief Ajoute un participant à la liste
        void ajouterParticipant(std::string participant);

        /// @brief Retire un participant de la liste
        void retirerParticipant(int index);

    private:

        std::string m_nom;
        //std::vector m_participants;
        int m_montant;


};

#endif // CAGNOTTE_H
