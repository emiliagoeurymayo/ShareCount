#include "mainwindow.h"
#include "Compte.h"
#include "ShareCount.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    ShareCount sC;

    Compte c("Jorge","jorge@pompidou.com");
    c.afficher();

    w.show();
    return a.exec();
}
