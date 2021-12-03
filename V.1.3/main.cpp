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
    gestionnaireBDD gd("/Users/emiliagoeury/Desktop/Univ/L3_V2/cpoa/ShareCount/resources/database.db");
    qDebug() << "DB OK";
    ShareCount sC;
    qDebug() << "Sharecount ok";
    ServeurMail sM;
    qDebug() << "ServeurMail ok";
    GestionnaireDialogue g(sC,sM);
    qDebug() << "gestionnaireDiag ok";
    ConnexionInscription c;
    qDebug() << "ConnexionInscription ok";
    c.attachGestionnaireDialogue(g);
    c.show();

//    std::cout << "Bonjour, entrez votre nom :\n";
//    std::cin >> nom;
//    std::cout << "Ainsi que votre mail :\n";
//    std::cin >> mail;
//    std::cout << "Et enfin votre mot de passe :\n";
//    std::cin >> mdp;

    return a.exec();
}
