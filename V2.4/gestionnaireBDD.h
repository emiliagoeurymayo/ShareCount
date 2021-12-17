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
#include <QOperatingSystemVersion>

#include <stdio.h>
#include <iostream>
#include <string>

class gestionnaireBDD {
private:
    QSqlDatabase db;
    int nbCompte;
    int nbCagnotte;
    int nbUtil;
    QString path;

public:
    //creation db
    gestionnaireBDD(){
        this->db = QSqlDatabase::addDatabase("QSQLITE");
        QString sys = QOperatingSystemVersion::current().name();
        this->path = QDir::currentPath();

        if(sys == "macOS" || sys=="Linux" || sys==""){
            QStringList list = this->path.split("ShareCount");
            this->path = list[0];
            this->path.append("ShareCount/ressources/database.db");
        }else if(sys =="Windows"){
            QStringList list = this->path.split("ShareCount");
            this->path = list[0];
            this->path.append("ShareCount\\ressources\\database.db");
        }
        qDebug() << this->path;
        this->db.setDatabaseName(this->path);
        this->db.open();
        try{
            if(this->db.open()){
                qDebug() << "Connection succesful";
                nbCompte = 0;
                nbCagnotte = 0;
                nbUtil = 0;
                createDB();
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
        if(this->db.open()){
            QSqlQuery queryUtil(this->db);
            if(!queryUtil.exec("create table if not exists utilisateur(idutil int primary key, prenom varchar(20),nom varchar(20),email varchar(50), mdp varchar(20), payement varchar(19))")){
               qDebug() << "utilisateur";
               qDebug() << queryUtil.lastError();
            }
            QSqlQuery queryCompte(this->db);
            if(!queryCompte.exec("create table if not exists compte(idcompte int primary key, nom varchar(30), listePart varchar(30))")){
                qDebug() << "compte";
                qDebug() << queryCompte.lastError();
            }

            QSqlQuery queryDettes(this->db);
            if(!queryDettes.exec("create table if not exists dettes (idcompte int primary key, util1 int, util2 int, dette int)")){
                qDebug() << "dette";
                qDebug() << queryDettes.lastError();
            }
            QSqlQuery queryCagnotte(this->db);
            if(!queryCagnotte.exec("create table if not exists cagnotte (idcagnotte int primary key, idRespo int, montantDispo int ,nom varchar(30), listePart varchar(30))")){
                qDebug() << "cagnotte";
                qDebug() << queryCagnotte.lastError();
            }

            QSqlQuery queryHistorique(this->db);
            if(!queryHistorique.exec("create table if not exists historique(idcompte int primary key, codeAction int, util1 int, util2 int)")){
                qDebug() << "Historique";
                qDebug() << queryHistorique.lastError();
            }
            QSqlQuery queryIdUtil(this->db);
            queryIdUtil.exec("select max(idutil) from utilisateur");
            if(queryIdUtil.next()){
                this->nbUtil = queryIdUtil.value(0).toInt();
                //qDebug() << "max idutil" << query4.value(0).toInt();
            }

            QSqlQuery queryIdCompte(this->db);
            queryIdCompte.exec("select max(idcompte) from compte");
            if(queryIdCompte.next()){
                this->nbCompte = queryIdCompte.value(0).toInt();
                //qDebug() << "max idcompte" << query5.value(0).toInt();
            }

            QSqlQuery queryIdCagnotte(this->db);
            queryIdCagnotte.exec("select max(idcagnotte) from cagnotte");
            if(queryIdCagnotte.next()){
                this->nbCagnotte = queryIdCagnotte.value(0).toInt();
                //qDebug() << "maxidcagnotte" << query7.value(0).toInt();
            }

            if(this->nbUtil == 0){
                addUtil("Thibault","Odor","to@test.fr","mdp", "1234567891234567891");
                addUtil("Marie-Luc","Moselle","mlm@test.fr","mdp1","1234567891234567891");
                addUtil("Emilia","Goeury","egm@test.fr","mdp2","1234567891234567891");
                addUtil("Max", "Illoul", "mi@test.fr", "mdp3","1234567891234567891" );
            }

            if(this->nbCompte == 0){
                addComptePartage("Vacances", "1,2,4");
                addComptePartage("Soiree 29/11", "1,2,3");
                addComptePartage("Noel", "2,3,4");
                addComptePartage("Restaurant 12/06","3,4");
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
        return result;
    }

    int informationConnexionValide(std::string email,std::string mdp){
            int result = 0;
            QSqlQuery query(this->db);
            query.exec("SELECT idutil from utilisateur where email ='"+QString::fromStdString(email)+"' AND mdp ='"+QString::fromStdString(mdp)+"'");
            if(query.next()){
                result = query.value(0).toInt();
            }
            return result;
        }

    //idutil integer primary key, prenom varchar(20),nom varchar(20),email varchar(50), mdp varchar(20), payement varchar(19)
    bool addUtil(std::string prenom, std::string nom, std::string email, std::string mdp, std::string payement){
        bool result = false;
        QSqlQuery query(this->db);
        this->nbUtil++;
        //qDebug() << "nbUtil :" << this->nbUtil;
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
        //qDebug()  << "addCompte";
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
        //qDebug() << "addCagnotte";
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
        //qDebug() << "addDettes";
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
        query.addBindValue(util1);
        query.addBindValue(util2);
        return query.exec();
    }

    QString getNomCompte(int id){
            QString result;
            QSqlQuery query(this->db);
            query.exec("SELECT nom FROM compte WHERE idcompte="+QString::fromStdString(std::to_string(id)));
            if(query.next()){
                result = query.value(0).toString();
            }
           return result;
        }
    QString getNomCagnotte(int id){
        QString result;
        QSqlQuery query(this->db);
        query.exec("SELECT nom FROM cagnotte WHERE idcagnotte="+QString::fromStdString(std::to_string(id)));
        if(query.next()){
            result = query.value(0).toString();
        }
       return result;
    }

        bool addPartCompt(QString email, int id){
            bool result = false;
            std::string stc = email.toStdString();
            if(utilExist(stc)){
                QSqlQuery query(this->db);
                query.prepare("SELECT listePart FROM compte WHERE idcompte="+QString::fromStdString(std::to_string(id)));
                query.exec();
                if(query.next()){
                    QString stc = query.value(0).toString();
                    query.exec("SELECT idutil FROM utilisateur WHERE email='"+email+"'");
                    if(query.next()){
                        if(!stc.contains(query.value(0).toString())){
                            stc.append(","+query.value(0).toString());
                            if(query.exec("UPDATE compte SET listePart ='"+stc+"' WHERE idcompte="+QString::fromStdString(std::to_string(id)))){
                                result = true;
                            }
                        }
                    }
                }
            }
            return result;
        }

        bool addPartCagnotte(QString email, int idCagnotte){
            bool result = false;
            std::string stc = email.toStdString();
            if(utilExist(stc)){
                QSqlQuery query(this->db);
                query.prepare("SELECT listePart FROM cagnotte WHERE idcagnotte="+QString::fromStdString(std::to_string(idCagnotte)));
                query.exec();
                if(query.next()){
                    QString stc = query.value(0).toString();
                    query.exec("SELECT idutil,payement FROM utilisateur WHERE email='"+email+"'");
                    if(query.next()){
                        QString id = query.value(0).toString();
                        QString payement = query.value(1).toString();
                        if(!payement.isEmpty() && !stc.contains(query.value(0).toString())){
                            stc.append(","+query.value(0).toString());
                            if(query.exec("UPDATE cagnotte SET listePart ='"+stc+"' WHERE idcagnotte="+QString::fromStdString(std::to_string(idCagnotte)))){
                                result = true;
                            }
                        }
                    }
                }
            }
            return result;
        }

        QMap<int, QString> getListeCompte(std::string email){
            QString mail = QString::fromStdString(email);
            QString list;
            QMap<int, QString> map;
            QSqlQuery query(this->db);
            query.prepare("SELECT idutil FROM utilisateur WHERE email='"+mail+"'");
            query.exec();
            if(query.next()){
                QString id = query.value(0).toString();
                query.prepare("SELECT listePart,nom,idcompte FROM compte");
                query.exec();
                while(query.next()){
                    QString stc = query.value(0).toString();
                    if(stc.contains(id)){
                        list = query.value(1).toString();
                        map.insert(query.value(2).toInt(), list);
                    }
                }
            }
            return map;
        }

        QMap <int,QString> getListeCagnotte(std::string email){
            QString mail = QString::fromStdString(email);
            QString list;
            QMap<int, QString> map;
            QSqlQuery query(this->db);
            query.prepare("SELECT idutil FROM utilisateur WHERE email='"+mail+"'");
            query.exec();
            if(query.next()){
                QString id = query.value(0).toString();
                query.prepare("SELECT listePart,nom,idcagnotte FROM cagnotte");
                query.exec();
                while(query.next()){
                    list=query.value(1).toString();
                    map.insert(query.value(2).toInt(), list);
                }
            }
            return map;
        }

        ~gestionnaireBDD(){
            this->db.close();
            QSqlDatabase::removeDatabase(this->path);
        }

};
#endif // GESTIONNAIREBDD_H
