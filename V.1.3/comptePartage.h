#ifndef COMPTEPARTAGE_H
#define COMPTEPARTAGE_H

#include <string>
#include <vector>

class ComptePartage
{
    public:
        ComptePartage(std::string nom);

        virtual ~ComptePartage();

        /// @brief Accesseur de l'attribut nom de la classe Cagnotte
        std::string getNom();

        /// @brief Mutateur de l'attribut nom de la classe Cagnotte
        void setNom(std::string nom);

        /// @brief Accesseur de la liste des participants
        // std::vector getParticipants();

        /// @brief Accesseur d'un participant de la liste
        std::string getParticipant(int index);

        /// @brief Ajoute un participant à la liste
        void ajouterParticipant(std::string participant);

        /// @brief Retire un participant de la liste
        void retirerParticipant(int index);

    private:
        std::string m_nom;
        // std::vector m_participants;

};

#endif // COMPTEPARTAGE_H
