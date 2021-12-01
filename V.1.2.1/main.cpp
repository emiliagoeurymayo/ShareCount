#include "inscription.h"
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
    ShareCount sC;
    ServeurMail sM;
    GestionnaireDialogue g(sC,sM);
    ConnexionInscription c;
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
