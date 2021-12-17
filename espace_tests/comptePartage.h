#ifndef COMPTEPARTAGE_H
#define COMPTEPARTAGE_H

#include <string>
#include <QList>

class ComptePartage
{
    public:
        ComptePartage(std::string nom, QList<std::string> list);

        virtual ~ComptePartage();

        /// @brief Accesseur de l'attribut nom de la classe Cagnotte
        std::string getNom();

        /// @brief Mutateur de l'attribut nom de la classe Cagnotte
        void setNom(std::string nom);

        /// @brief Accesseur de la liste des participants
        QList<std::string> getParticipants();

        /// @brief Accesseur d'un participant de la liste
        std::string getParticipant(int index);

        /// @brief Ajoute un participant à la liste
        void ajouterParticipant(std::string participant);

        /// @brief Retire un participant de la liste
        void retirerParticipant(int index);

        /// @brief Ajoute une dépense à la liste
        void ajouterDepense(std::string depense);

        /// @brief Retire une dépense de la liste
        void retirerDepense(int index);

    private:
        std::string m_nom;
        QList<std::string> m_participants;
        QList<std::string> m_depenses;

};

#endif // COMPTEPARTAGE_H
