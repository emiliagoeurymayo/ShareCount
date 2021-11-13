#include "mainwindow.h"
#include "Compte.h"
#include "ShareCount.h"
#include "TestCompte.h"
#include "TestShareCount.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    printf("TestCompte\n");
    TestCompte test;
    test.testAfficherCompte();

    printf("\nTestShareCount\n");
    TestShareCount test1;
    test1.testAjouterCompte();


    w.show();
    return a.exec();
}
