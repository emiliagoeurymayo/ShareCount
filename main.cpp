#include "mainwindow.h"
#include "Compte.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Compte c("Jorge","jorge@pompidou");
    c.afficher();

    w.show();
    return a.exec();
}
