#include "mainwindow.h"
#include "Compte.h"
#include "ShareCount.h"
#include "ServeurMail.h"
#include "GestionnaireDialogue.h"
#include <iostream>
#include <QApplication>
#include "connexioninscription.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ShareCount sC;
    ServeurMail sM;
    GestionnaireDialogue g(sC,sM);
    w.attachGestionnaireDialogue(g);
    w.show();

//    std::cout << "Bonjour, entrez votre nom :\n";
//    std::cin >> nom;
//    std::cout << "Ainsi que votre mail :\n";
//    std::cin >> mail;
//    std::cout << "Et enfin votre mot de passe :\n";
//    std::cin >> mdp;

    return a.exec();
}
