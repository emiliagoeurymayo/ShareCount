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

#include "simplecrypt.h"

class gestionnaireBDD {
private:
    QSqlDatabase db;
    int nbCompte;
    int nbCagnotte;
    int nbUtil;
    int nbHistorique;
    QString path;
    int cleEncrypt;
public:
    //creation db
    gestionnaireBDD(){
        this->cleEncrypt = (89473829);

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

        this->db.setDatabaseName(this->path);
        this->db.open();
        try{
            if(this->db.open()){
                qDebug() << "Connection succesful";
                nbCompte = 0;
                nbCagnotte = 0;
                nbUtil = 0;
                nbHistorique = 0;
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
            if(!queryUtil.exec("create table if not exists utilisateur(idutil int primary key, prenom varchar(20),nom varchar(20),email varchar(50), mdp varchar(100), payement varchar(500))")){
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
            if(!queryHistorique.exec("create table if not exists historique(idNumHistorique int primary key, idcagnotte int, codeAction int, util1 int, montant int)")){
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
            QSqlQuery queryNbHistorique(this->db);
            queryNbHistorique.exec("select max(idNumHistorique) from historique");
            if(queryNbHistorique.next()){
                this->nbHistorique = queryNbHistorique.value(0).toInt();
            }

            if(this->nbUtil == 0){
                SimpleCrypt encrypt(this->cleEncrypt);

                QString mdp("mdp");
                QString stc = encrypt.encryptToString(mdp);

                QString banque("1234567891234567891");
                QString stc2 = encrypt.encryptToString(banque);

                addUtil("Thibault","Odor","to@test.fr",stc.toStdString(), stc2.toStdString());
                addUtil("Marie-Luc","Moselle","mlm@test.fr",stc.toStdString(),stc2.toStdString());
                addUtil("Emilia","Goeury","egm@test.fr",stc.toStdString(),stc2.toStdString());
                addUtil("Max", "Illoul", "mi@test.fr", stc.toStdString(),stc2.toStdString());
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

            if(this->nbHistorique == 0){
                addHistorique(1,1,1,10);
                addHistorique(1,2,2,10);
                addHistorique(2,1,2,10);
                addHistorique(2,2,3,10);
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
            SimpleCrypt encrypt(this->cleEncrypt);

            QSqlQuery query(this->db);
            int result = 0;
            query.prepare("SELECT idutil, mdp FROM utilisateur WHERE email ='"+QString::fromStdString(email)+"'");
            query.exec();
            if(query.next()){
                QString verif = query.value(1).toString();
                QString verif2 = encrypt.decryptToString(verif);
                QString verif3 = encrypt.decryptToString(verif2);
                if(verif3 == QString::fromStdString(mdp)){
                    result = query.value(0).toInt();
                }
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

            SimpleCrypt encrypt(this->cleEncrypt);

            QString stc = encrypt.encryptToString(QString::fromStdString(mdp));
            query.addBindValue(stc);

            QString stc2 = encrypt.encryptToString(QString::fromStdString(payement));
            query.addBindValue(stc2);

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
        QMap<QString , QString> map;


        for ( const auto& i : list){
            query.exec("SELECT prenom,nom,idutil FROM utilisateur WHERE idutil ="+i);
            if(query.next()){
                QString info =query.value(0).toString()+" "+query.value(1).toString();
                map.insert(query.value(2).toString()+".", info);
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

    bool addHistorique(int idcagnotte, int codeaction, int util1, int montant){
        QSqlQuery query(this->db);
        this->nbHistorique++;
        query.prepare("INSERT INTO historique(idNumHistorique, idcagnotte, codeAction, util1, montant)" "VALUES(?,?,?,?,?)");
        query.addBindValue(this->nbHistorique);
        query.addBindValue(idcagnotte);
        query.addBindValue(codeaction);
        query.addBindValue(util1);
        query.addBindValue(montant);
        bool result = query.exec();
        if(!result){
            this->nbHistorique--;
            qDebug() << query.lastError();
            qDebug() << this->db.lastError();
        }
        return result;
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
                    QString stc = query.value(0).toString();
                    if(stc.contains(id)){
                        list=query.value(1).toString();
                        map.insert(query.value(2).toInt(), list);
                    }
                }
            }
            return map;
        }
        //1 ajout argent
        //2 retirer argent
        //(nbHistoriqueint primary key, idcompte int, codeAction int, util1 int, montant int)
        QStringList getListeHistorique(int idCagnotte){
            QStringList result;
            QSqlQuery query(this->db);
            query.prepare("SELECT * FROM historique WHERE idcagnotte="+QString::fromStdString(std::to_string(idCagnotte)));
            query.exec();
            QString action;
            while(query.next()){
                switch (query.value(2).toInt()){
                case 1:
                    action=" a ajouté ";
                    break;
                case 2:
                    action=" a retiré ";
                    break;
                default:
                    break;
                }
                QMap<QString, QString> personne = getUtil(query.value(3).toInt());
                QString stc;
                for(const auto &e : personne.toStdMap()){stc.append(e.first+" "+e.second);}
                QString str = stc+action+query.value(4).toString()+"€";
                result.append(str);
            }
            return result;
        }

        int getFondsDispo(int idCagnotte){
            int result = 0;
            QSqlQuery query(this->db);
            query.exec("SELECT montantDispo from cagnotte WHERE idcagnotte="+QString::fromStdString(std::to_string(idCagnotte)));
            if(query.next()){
                result = query.value(0).toInt();
            }
            return result;
        }

        //int idcagnotte, int codeaction, int util1, int montant
        bool addFonds(QString fond, int m_id, int m_idcagnotte){
            SimpleCrypt encrypt(this->cleEncrypt);
            bool result = false;
            QSqlQuery query(this->db);
            query.exec("SELECT payement FROM utilisateur WHERE idutil="+QString::fromStdString(std::to_string(m_id)));
            if(query.next()){
                QString verif = query.value(0).toString();
                QString verif2 = encrypt.decryptToString(verif);
                QString verif3 = encrypt.decryptToString(verif2);
                if(verif3 != "ABC" || verif3 !=""){
                   query.exec("SELECT montantDispo FROM cagnotte WHERE idCagnotte="+QString::fromStdString(std::to_string(m_idcagnotte)));
                   if(query.next()){
                       int montant = query.value(0).toInt();
                       int ajout = fond.toInt();
                       montant += ajout;
                       result = query.exec("UPDATE cagnotte set montantDispo="+QString::fromStdString(std::to_string(montant))+" WHERE idcagnotte="+QString::fromStdString(std::to_string(m_idcagnotte)));
                       addHistorique(m_idcagnotte, 1, m_id,fond.toInt());
                   }
                }
            }
            return result;
        }

        bool retirerFonds(QString fond, int m_id, int m_idcagnotte){
            SimpleCrypt encrypt(this->cleEncrypt);
            bool result = false;
            QSqlQuery query(this->db);
            query.exec("SELECT payement FROM utilisateur WHERE idutil="+QString::fromStdString(std::to_string(m_id)));
            if(query.next()){
                QString verif = query.value(0).toString();
                QString verif2 = encrypt.decryptToString(verif);
                QString verif3 = encrypt.decryptToString(verif2);
                if(verif3 != "ABC" || verif3 !=""){
                   query.exec("SELECT montantDispo FROM cagnotte WHERE idCagnotte="+QString::fromStdString(std::to_string(m_idcagnotte)));
                   if(query.next()){
                       int montant = query.value(0).toInt();
                       int ajout = fond.toInt();
                       if(montant >= ajout){
                           montant -= ajout;
                           result = query.exec("UPDATE cagnotte set montantDispo="+QString::fromStdString(std::to_string(montant))+" WHERE idcagnotte="+QString::fromStdString(std::to_string(m_idcagnotte)));
                           addHistorique(m_idcagnotte, 2, m_id,fond.toInt());
                       }
                   }
                }
            }
            return result;

        }

        ~gestionnaireBDD(){
            this->db.close();
            QSqlDatabase::removeDatabase(this->path);
        }

};
#endif // GESTIONNAIREBDD_H
