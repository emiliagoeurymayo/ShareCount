#ifndef GESTIONNAIREBDD_H
#define GESTIONNAIREBDD_H
#include <QFileDialog>
#include <QtDebug>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QMap>
#include <stdio.h>
#include <iostream>
#include <string>

class gestionnaireBDD {
private:
    QSqlDatabase db;
    int nbCompte;
    int nbCagnotte;
    int nbUtil;
    bool etatDB;

public:
    //creation db
    gestionnaireBDD(){
        qDebug() << "Constr";
        this->db = QSqlDatabase::addDatabase("QSQLITE");
        this->db.setDatabaseName("a.db");
        this->db.open();
        try{
            if(this->db.open()){
                qDebug() << "Connection succesful";
                nbCompte = 0;
                nbCagnotte = 0;
                nbUtil = 0;
                createDB();
                this->etatDB = true;

            }else{
                qDebug() << "Error: connection with database failed";
                qDebug() << this->db.lastError();
            }

        }catch(QSqlError error){
            qDebug() << this->db.lastError();
            std::cout << "init not ok" << std::endl;
        }
    }

    void createDB(){
        qDebug() << "CreateDB";
        if(this->db.open()){
            QSqlQuery query(this->db);
            if(!query.exec("create table if not exists utilisateur(idutil int primary key, prenom varchar(20),nom varchar(20),email varchar(50), mdp varchar(20), payement varchar(19))")){
               qDebug() << "utilisateur";
               qDebug() << query.lastError();
            }
            QSqlQuery query1(this->db);
            if(!query1.exec("create table if not exists compte(idcompte int primary key, nom varchar(30), listePart varchar(30))")){
                qDebug() << "compte";
                qDebug() << query1.lastError();
            }

            QSqlQuery query2(this->db);
            if(!query2.exec("create table if not exists dettes (idcompte int primary key, util1 int, util2 int, dette int)")){
                qDebug() << "dette";
                qDebug() << query2.lastError();
            }
            QSqlQuery query3(this->db);
            if(!query3.exec("create table if not exists cagnotte (idcagnotte int primary key, idRespo int, montantDispo int ,nom varchar(30), listePart varchar(30))")){
                qDebug() << "cagnotte";
                qDebug() << query3.lastError();
            }

            QSqlQuery queryHistorique(this->db);
            if(!queryHistorique.exec("create table if not exists historique(idcompte int primary key, codeAction int, util1 int, util2 int)")){
                qDebug() << "Historique";
                qDebug() << queryHistorique.lastError();
            }
            QSqlQuery query4(this->db);
            query4.exec("select max(idutil) from utilisateur");
            if(query4.next()){
                this->nbUtil = query4.value(0).toInt();
                qDebug() << "max idutil" << query4.value(0).toInt();
            }

            QSqlQuery query5(this->db);
            query5.exec("select max(idcompte) from compte");
            if(query5.next()){
                this->nbCompte = query5.value(0).toInt();
                qDebug() << "max idcompte" << query5.value(0).toInt();
            }

            QSqlQuery query7(this->db);
            query7.exec("select max(idcagnotte) from cagnotte");
            if(query7.next()){
                this->nbCagnotte = query7.value(0).toInt();
                qDebug() << "maxidcagnotte" << query7.value(0).toInt();
            }

            if(this->nbUtil == 0){
                addUtil("pre","nomnom","prenom.nom@test.fr","mdp", "12");
                addUtil("admin","admin","admin@test.fr","mdp1","25");
                addUtil("test","test","test@test.fr","mdp2","46");
            }

            if(this->nbCompte == 0){
                addComptePartage("Vacances", "1,2,3");
                addComptePartage("Soiree 29/11", "1,2,3");
                addDettes(1, 1, 2, 30);
                addDettes(2, 3, 2, 1);
                addDettes(3, 1, 3, 80);
            }

            if(this->nbCagnotte == 0){
                addCagnotte(2, 0, "Cadeau maman", "1,2,3");
                addCagnotte(1, 0, "Noel", "2,3");
            }
        }
    }

    bool utilExist(std::string email){
        bool result = false;
        QSqlQuery query(this->db);
        query.exec("SELECT * from utilisateur where email ='"+QString::fromStdString(email)+"'");
        if(query.next()){
            result = true;
        }
        qDebug() << "utilExist =" << result;
        return result;
    }

    int informationConnexionValide(std::string email,std::string mdp){
            int result = 0;
            QSqlQuery query(this->db);
            query.exec("SELECT idutil from utilisateur where email ='"+QString::fromStdString(email)+"' AND mdp ='"+QString::fromStdString(mdp)+"'");
            if(query.next()){
                result = query.value(0).toInt();
            }
            qDebug() << "informations de connexions correct =" << result;
            return result;
        }

    //idutil integer primary key, prenom varchar(20),nom varchar(20),email varchar(50), mdp varchar(20), payement varchar(19)
    bool addUtil(std::string prenom, std::string nom, std::string email, std::string mdp, std::string payement){
        qDebug() << "addUtil";
        bool result = false;
        QSqlQuery query(this->db);
        this->nbUtil++;
        qDebug() << "nbUtil :" << this->nbUtil;
        if(!utilExist(email)){
            query.prepare("INSERT INTO utilisateur (idutil, prenom, nom, email, mdp, payement) "
                          "VALUES (?, ?, ?, ?, ?, ?)");
            query.addBindValue(this->nbUtil);
            query.addBindValue(QString::fromStdString(prenom));
            query.addBindValue(QString::fromStdString(nom));
            query.addBindValue(QString::fromStdString(email));
            query.addBindValue(QString::fromStdString(mdp));
            query.addBindValue(QString::fromStdString(payement));
            query.exec();
            if(utilExist(email)){
                result = true;
            }else{
                qDebug() << query.lastError();
                qDebug() << this->db.lastError();
            }
        }else{
            this->nbUtil--;
        }
        return result;
    }

    //idcompte integer primary key, nom varchar(30), listePart varchar(30)
    bool addComptePartage(std::string nom, std::string listePart){
        qDebug()  << "addCompte";
        this->nbCompte++;
        QSqlQuery query(this->db);
        query.prepare("INSERT INTO compte(idcompte,nom,listePart)"
                      "VALUES(?,?,?)");
        query.addBindValue(this->nbCompte);
        query.addBindValue(QString::fromStdString(nom));
        query.addBindValue(QString::fromStdString(listePart));

        return query.exec();
    }


    //idcagnotte integer primary key, idRespo integer, montantDispo integer ,nom varchar(30), listePart varchar(30)
    bool addCagnotte(int respo, int montant, std::string nom, std::string listePart){
        qDebug() << "addCagnotte";
        this->nbCagnotte++;
        QSqlQuery query(this->db);
        query.prepare("INSERT INTO cagnotte(idcagnotte,idRespo,montantDispo,nom,listePart)""VALUES(?,?,?,?,?)");
        query.addBindValue(this->nbCagnotte);
        query.addBindValue(respo);
        query.addBindValue(montant);
        query.addBindValue(QString::fromStdString(nom));
        query.addBindValue(QString::fromStdString(listePart));

        return query.exec();
    }


    //idcompte int primary key, util1 int, util2 int, dette int
    bool addDettes(int idcompte,int util1, int util2, int dette){
        qDebug() << "addDettes";
        QSqlQuery query(this->db);
        query.prepare("INSERT INTO dettes(idcompte, util1, util2, dette)""VALUES(?,?,?,?)");
        query.addBindValue(idcompte);
        query.addBindValue(util1);
        query.addBindValue(util2);
        query.addBindValue(dette);
        return query.exec();
    }

    QMap <QString, QString> getUtil(int id){
        QSqlQuery query(this->db);
        QMap <QString, QString> result;
        query.prepare("SELECT prenom,nom FROM utilisateur WHERE idutil ="+QString::fromStdString(std::to_string(id)));
        query.exec();
        while(query.next()){
            result.insert(query.value(0).toString(), query.value(1).toString());
            //qDebug() << query.value(0).toString() << query.value(1).toString();
        }
        return result;
    }

    //typeCompte = 1 comptepartagé || 2 Cagnotte
    //id = numéro du compte
    QMap<QString, QString> getParticipants(int typeCompte, int id){

        QString part;
        QSqlQuery query(this->db);

        if(typeCompte == 1){
            query.exec("SELECT listePart FROM compte WHERE idcompte="+QString::fromStdString(std::to_string(id)));
            if(query.next()){
                part = query.value(0).toString();
            }
        }else if(typeCompte == 2){
            query.exec("SELECT listePart FROM cagnotte WHERE idcagnotte="+QString::fromStdString(std::to_string(id)));
            if(query.next()){
                part = query.value(0).toString();
            }
        }

        QStringList list = part.split(",");
        qDebug() << "liste" << list;
        QMap<QString , QString> map;


        for ( const auto& i : list){
            query.exec("SELECT prenom,nom FROM utilisateur WHERE idutil ="+i);
            if(query.next()){
                map.insert(query.value(0).toString(), query.value(1).toString());
                //qDebug() << query.value(0).toString() << query.value(1).toString();
            }
        }

        return map;
    }

    QMap <QString, QString> getRespo(int idcagnotte){
        QSqlQuery query(this->db);
        QMap<QString , QString> map;

        query.exec("SELECT idrespo FROM cagnotte WHERE idcagnotte="+QString::fromStdString(std::to_string(idcagnotte)));
        if(query.next()){
            map = this->getUtil(query.value(0).toInt());
        }
        return map;
    }

    bool addHistorique(int idcompte, int codeaction, int util1, int util2){
        QSqlQuery query(this->db);
        return query.prepare("INSERT INTO historique(idcompte, codeAction, util1, util2)" "VALUES(?,?,?,?)");
        query.addBindValue(idcompte);
        query.addBindValue(codeaction);
        query.addBindValue(util2);
        query.addBindValue(util2);
        return query.exec();
    }
};
#endif // GESTIONNAIREBDD_H
