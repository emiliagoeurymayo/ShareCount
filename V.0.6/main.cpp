#include "mainwindow.h"
#include "Compte.h"
#include "ShareCount.h"
#include "ServeurMail.h"
#include "GestionnaireDialogue.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    ShareCount sC;
    ServeurMail sM;

    GestionnaireDialogue g(sC,sM);

    std::string nom,mail;
    std::cout << "Bonjour, entrez votre nom :\n";
    std::cin >> nom;
    std::cout << "Ainsi que votre mail :\n";
    std::cin >> mail;

    g.verifInformations(nom,mail);

    w.show();
    return a.exec();
}
