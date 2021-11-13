#include "mainwindow.h"
#include "Compte.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    ShareCount sC;
    ServeurMail sM;

    GestionnaireDialogue g(sC,sM);

    if(g.verifInformations("Jorge","Jorge@Pompidou.com")==0){
        g.verifValidationEmail("Jorge","Jorge@Pompidou.com");
    }
    else{
        std::cout << "Un des champs est invalide (EmptyError)" << std::endl;
    }

    if(g.verifInformations("","Test@Empty.com")==0){
        g.verifValidationEmail("","Test@Empty.com");
    }
    else{
        std::cout << "Un des champs est invalide (EmptyError)" << std::endl;
    }

    w.show();
    return a.exec();
}
