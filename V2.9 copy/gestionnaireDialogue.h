#ifndef GESTIONNAIREDIALOGUE
#define GESTIONNAIREDIALOGUE

#include <string>
#include "serveurMail.h"
#include "shareCount.h"
#include "gestionnaireBDD.h"

/** @brief La classe GestionnaireDialogue est le modele de notre application
 **
 ** Elle contient
 ** @ref GestionnaireDialogue(ShareCount,ServeurMail ,gestionnaireBDD )
 ** @ref GestionnaireDialogue()
 ** @ref virtual ~GestionnaireDialogue()
 ** @ref void verifInformations(string,string,string,string,string,bool)
 ** @ref void envoiEmail(bool)
 ** @ref void verifValidationEmail()
 ** @ref int verifConnexion(string,string)
 ** @ref QMap<QString,QString> identifierUtilisateur(int)
 ** @ref QMap<QString,QString> getParticipants(int,int)
 ** @ref QString getNomCompte(int)
 ** @ref QMap<int, QString> getListeCompte()
 ** @ref bool addPartCompt(QString,int)
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/
class GestionnaireDialogue{
public:
    ///@brief Constructeur
    GestionnaireDialogue(ShareCount sharecount,ServeurMail serveurmail,gestionnaireBDD gbdd);//Constructeur
    ///@brief Constructeur vide
    GestionnaireDialogue();
    ///@brief Destructeur
    virtual ~GestionnaireDialogue();
    ///@brief Verifie la véracité des informations saisies dans les champs de texte de l'interface Inscription
    void verifInformations(std::string nom,std::string email,std::string mdp,std::string prenom,std::string pseudo,bool mailvalide);
    ///@brief "Envoie" le mail de validation
    void envoiEmail(bool mailvalide);
    ///@brief Ajoute le compte à la base de donnée aprés la vérification
    void verifValidationEmail();
    ///@brief Retourne l'id de l'utilisateur defini à l'aide de la base de donnée, 0 sinon
    int verifConnexion(std::string email,std::string mdp);
    ///@brief Identifie le nom et prénom de l'utilisateur possédant l'id défini en paramètre
    QMap<QString,QString> identifierUtilisateur(int id);
    ///@brief Getter des participants d'un compte partagé
    QMap<QString,QString> getParticipants(int typeCompte, int idCompte);
    ///@brief Retourne le nom du compte identifier par l'id en paramètre
    QString getNomCompte(int id);
    ///@brief Retourne le nom de la cagnotte identifiée par l'id en paramètre
    QString getNomCagnotte(int id);
    ///@brief Retourne la liste des comptes auquel l'utilisateur participe
    QMap<int, QString> getListeCompte();
    ///@brief Retourne la liste des cagnottes auquelles l'utilisateur participe
    QMap<int, QString> getListeCagnotte();
    ///@brief Ajoute un participant à un compte partagé
    bool addPartCompt(QString text, int idCompte);
    ///@brief Ajoute un participant à une cagnotte partagé
    bool addPartCagnotte(QString email, int idCagnotte);
    ///@brief Retourne la liste d'action de la Cagnotte
    QStringList getListeHistorique(int idCagnotte);
    ///@breif Renvoie les fonds disponibles de la cagnotte
    int getFondsDispo(int idCagnotte);
    ///@brief ajoute de l'argent à la cagnotte
    bool addFonds(QString fond, int m_id, int m_idcagnotte);
    ///@brief retire de l'argent à la cagnotte
    bool retirerFonds(QString fond, int m_id, int m_idcagnotte);
    ///@brief retourne la liste des dettes
    QStringList getListeDettes(int m_idcompte);
private:

    ShareCount m_sharecount;
    ServeurMail m_serveurmail;
    gestionnaireBDD m_gbdd;
    std::string m_nom;
    std::string m_prenom;
    std::string m_email;
    std::string m_mdp; // Mot de Passe
    std::string m_pseudo;   //pseudo

};

#endif // GESTIONNAIREDIALOGUE
