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

    g.verifInformations("Jorge","Jorge@Pompidou.com");
    g.verifValidationEmail("Jorge","Jorge@Pompidou.com");

    w.show();
    return a.exec();
}
