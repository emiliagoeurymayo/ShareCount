#ifndef COMPTE
#define COMPTE

#include <string>


/** @brief La classe Compte permet la création de tous les comptes de l'application
 **
 ** Elle contient
 **  @ref Compte(string, string)
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/
class Compte{
public:
    ///@brief Constructeur
    Compte(std::string nom,std::string prenom,std::string email,std::string mdp,std::string pseudo);
    ///@brief Desctructeur
    virtual ~Compte();
    ///@brief Affiche les informations du compte
    void afficher();
    ///@brief Affecte un nouveau mot de passe au Compte
    void setMotDePasse(std::string mdp);
    ///@brief Récupère le mot de passe
    std::string getMotDePasse();
    ///@brief Affecte une nouvelle adresse mail au Compte
    void setEmail(std::string email);
    ///@brief Recupère l'adresse email
    std::string getEmail();

private:

    std::string m_nom;
    std::string m_prenom;
    std::string m_email;
    std::string m_mdp; // Mot de Passe
    std::string m_pseudo;   //pseudo
    int m_identifiant;

};

#endif
