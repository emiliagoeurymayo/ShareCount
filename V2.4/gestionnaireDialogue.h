#ifndef GESTIONNAIREDIALOGUE
#define GESTIONNAIREDIALOGUE

#include <string>
#include "serveurMail.h"
#include "shareCount.h"
#include "gestionnaireBDD.h"

class GestionnaireDialogue{
public:

    GestionnaireDialogue(ShareCount sharecount,ServeurMail serveurmail,gestionnaireBDD gbdd);//Constructeur
    GestionnaireDialogue();//Def constructor
    virtual ~GestionnaireDialogue();
    void verifInformations(std::string nom,std::string email,std::string mdp,std::string prenom,std::string pseudo,bool mailvalide);
    void envoiEmail(bool mailvalide);
    void verifValidationEmail();
    int verifConnexion(std::string email,std::string mdp);
    QMap<QString,QString> identifierUtilisateur(int id);
    QMap<QString,QString> getParticipants(int typeCompte, int idCompte);
    QString getNomCompte(int id);
    QMap<int, QString> getListeCompte();
    bool addPartCompt(QString text, int idCompte);
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
