#include "mainwindow.h"
#include "Compte.h"
#include "TestCompte.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
    MainWindow w;

    printf("TestCompte\n");
    TestCompte test;
    test.testAfficherCompte();

    w.show();
    return a.exec();
}
