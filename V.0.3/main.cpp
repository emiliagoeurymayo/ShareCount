#include "mainwindow.h"
#include "Compte.h"
#include "ShareCount.h"
#include "ServeurMail.h"
#include "TestCompte.h"
#include "TestShareCount.h"
#include "TestServeurMail.h"
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

    printf("\nTest ServeurMail\n");
    TestServeurMail test2;
    test2.testAjouterEmail();
    test2.testGetStatusEmail();


    w.show();
    return a.exec();
}
