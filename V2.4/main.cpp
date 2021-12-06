#include "compte.h"
#include "shareCount.h"
#include "serveurMail.h"
#include "gestionnaireDialogue.h"
#include "connexioninscription.h"
#include "gestionnaireBDD.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Instanciation du gestionnaire de base de donnée (sert à gérer la bdd)
    gestionnaireBDD gd; ;
    qDebug() << "DB OK";
    //Instanciation de ShareCount
    ShareCount sC;
    qDebug() << "Sharecount ok";
    //Instanciation du Serveur mail
    ServeurMail sM;
    qDebug() << "ServeurMail ok";
    //Instanciation du modele Gestionnaire Dialogue
    GestionnaireDialogue g(sC,sM,gd);
    qDebug() << "gestionnaireDiag ok";
    //Instanciation de la fenetre de connexion / inscription
    ConnexionInscription c;
    qDebug() << "ConnexionInscription ok";
    c.attachGestionnaireDialogue(&g);
    c.show();
    return a.exec();
}
