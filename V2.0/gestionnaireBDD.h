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
    gestionnaireBDD(QString s){
        qDebug() << "Constr";
        this->db = QSqlDatabase::addDatabase("QSQLITE");
        this->db.setDatabaseName(s);
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
            QSqlQuery query4(this->db);
            query4.exec("select max(idutil) from utilisateur");
            if(query4.next()){
                this->nbUtil = query4.value(0).toInt();
                qDebug() << "max idutil" << query4.value(0).toInt();
            }
            addUtil("pre","nomnom","prenom.nom@test.fr","mdp", "1234567891234567891");
            addUtil("admin","admin","admin@test.fr","mdp1","1234567891234567891");
            addUtil("test","test","test@test.fr","mdp2","1234567891234567891");
            addComptePartage("Vacances", "1,2,3");
            addComptePartage("Soiree 29/11", "1,2,3");
            addCagnotte(2, 0, "Cadeau maman", "1,2,3");
            addDettes(1, 1, 2, 30);
            addDettes(2, 3, 2, 1);
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
        bool result = false;
        nbCompte++;
        std::string stc = std::to_string(nbCompte);
        QString requete ="insert into compte values("+QString::fromStdString(stc)+","+QString::fromStdString(nom)+","+QString::fromStdString(listePart)+")";
        QSqlQuery query(requete, db);
        if(query.exec()){
            std::cout << "add compte part ok" << std::endl;
            result = true;
        }
        return result;
    }


    //idcagnotte integer primary key, idRespo integer, montantDispo integer ,nom varchar(30), listePart varchar(30)
    bool addCagnotte(int respo, int montant, std::string nom, std::string listePart){
        return true;
    }
    //idcompte int primary key, util1 int, util2 int, dette int
    bool addDettes(int idcompte,int util1, int util2, int dette){
        return true;
    }


    //typeCompte = 1 comptepartagé || 2 Cagnotte
    //id = numéro du compte
    QMap<QString, QString> getParticipant(int typeCompte, int id){

        QString part;
        if(typeCompte == 1){
            QSqlQuery query(db);
            query.prepare("SELECT listePart FROM compte WHERE idcompte ="+QString::fromStdString(std::to_string(id)));
            query.bindValue(0, part);
            query.exec();

        }else {
            QSqlQuery query(db);
            query.prepare("SELECT listePart FROM cagnotte WHERE idcompte ="+QString::fromStdString(std::to_string(id)));
            QString part;
            query.bindValue(0, part);
            query.exec();
        }

        QStringList list = part.split(",");
        QMap<QString , QString> map;

        QSqlQuery query1(db);

        QString stc1;
        QString stc2;

        for ( const auto& i : list  ){
            query1.prepare("Select prenom, nom FROM utilisateur WHERE idutil ="+list.at(list.indexOf(i)));
            query1.exec();
            stc1 = query1.value(0).toString();
            stc2 = query1.value(1).toString();
            map.insert(stc1, stc2);
        }

        /*for (int i; i < list.size(); i++){
            query1.prepare("Select prenom, nom FROM utilisateur WHERE idutil ="+list.at(list.indexOf(i)));
            query1.exec();
            stc1 = query1.value(0).toString();
            stc2 = query1.value(1).toString();
            map.insert(stc1, stc2);
        }*/

        return map;
    }
};
#endif // GESTIONNAIREBDD_H
