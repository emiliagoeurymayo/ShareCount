#include "mainwindow.h"
#include "gestionnaireBDD.h"

#include <QApplication>

int main(int argc, char *argv[]){
    //qDebug() << QSqlDatabase::drivers()

    gestionnaireBDD g("/Users/emiliagoeury/Desktop/Univ/L3_V2/cpoa/ShareCount/DB_FILES/test2.db");
    g.addUtil("emilia", "goeury", "emilia@gmail.fr", "motdepasse", "1234567891234567891");
    g.addComptePartage("nouvel an", "1,2");
    g.addCagnotte(3, 100, "Grèce" ,"1,3");
    g.addDettes(2, 1, 3, 30);

    QMap <QString, QString> result = g.getUtil(1);
    QMap <QString, QString> test = g.getParticipants(2, 1);


    for(const auto &e : test.toStdMap()){
     qDebug() << e.first << "," << e.second << '\n';
    }

    QMap <QString, QString> test2 = g.getRespo(3);
    for(const auto &e : test2.toStdMap()){
     qDebug() << e.first << "," << e.second << '\n';
    }


    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
}
