#include "mainwindow.h"
#include "gestionnaireBDD.h"

#include <QApplication>

int main(int argc, char *argv[]){
    //qDebug() << QSqlDatabase::drivers()

    gestionnaireBDD g("/Users/emiliagoeury/Desktop/Univ/L3_V2/cpoa/ShareCount/DB_FILES/test.db");
    g.addUtil("emilia", "goeury", "emilia@gmail.fr", "motdepasse", "1234567891234567891");

    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
}
