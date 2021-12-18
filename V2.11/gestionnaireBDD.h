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


/** @brief Classe qui assure la connection et les opérations sur la base de données
 **
 ** Elle contient
 ** @ref gestionnaireBDD()
 ** @ref void createDB()
 ** @ref bool utilExist(std::string email)
 ** @ref int informationConnexionValide(std::string email,std::string mdp)
 ** @ref bool addUtil(std::string prenom, std::string nom, std::string email, std::string mdp, std::string payement)
 ** @ref bool addComptePartage(std::string nom, std::string listePart)
 ** @ref bool addCagnotte(int respo, int montant, std::string nom, std::string listePart)
 ** @ref bool (int idcompte,int util1, int util2, int dette)
 ** @ref QMap <QString, QString> getUtil(int id)
 ** @ref QMap<QString, QString> getParticipants(int typeCompte, int id)
 ** @ref QMap <QString, QString> getRespo(int idcagnotte)
 ** @ref bool addHistorique(int idcagnotte, int codeaction, int util1, int montant)
 ** @ref QString getNomCompte(int id)
 ** @ref QString getNomCagnotte(int id)
 ** @ref bool addPartCompt(QString email, int id)
 ** @ref bool addPartCagnotte(QString email, int idCagnotte)
 ** @ref QMap<int, QString> getListeCompte(std::string email)
 ** @ref QMap <int,QString> getListeCagnotte(std::string email)
 ** @ref QStringList getListeHistorique(int idCagnotte)
 ** @ref int getFondsDispo(int idCagnotte)
 ** @ref bool addFonds(QString fond, int m_id, int m_idcagnotte)
 ** @ref bool retirerFonds(QString fond, int m_id, int m_idcagnotte)
 ** @ref ~gestionnaireBDD()
 **
 **
 ** @version 2.7
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/

class gestionnaireBDD {
private:
    //base de donnée
    QSqlDatabase db;
    //id propres aux comptes/cagnotte/historique
    int nbCompte;
    int nbCagnotte;
    int nbUtil;
    int nbHistorique;
    int nbDettes;
    //chemin vers la DB
    QString path;

public:
    ///@brief Constructeur de gestionnaireBDD
    gestionnaireBDD(){


        this->db = QSqlDatabase::addDatabase("QSQLITE");
        QString sys = QOperatingSystemVersion::current().name();
        this->path = QDir::currentPath();

        //Determine le système d'exploitation pour créer le chemin vers la base de données
        if(sys == "macOS" || sys=="Linux" || sys==""){
            QStringList list = this->path.split("ShareCount");
            this->path = list[0];
            this->path.append("ShareCount/ressources/database.db");
        }else if(sys =="Windows"){
            QStringList list = this->path.split("ShareCount");
            this->path = list[0];
            this->path.append("ShareCount\\ressources\\database.db");
        }

        //tentative de connection à la DB
        this->db.setDatabaseName(this->path);
        this->db.open();
        try{
            if(this->db.open()){
                qDebug() << "Connection succesful";
                nbCompte = 0;
                nbCagnotte = 0;
                nbUtil = 0;
                nbHistorique = 0;
                nbDettes = 0;
                //appel pour remplir la DB
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

    ///@brief Fonction permettant de remplir la DB si elle est vide
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
            if(!queryDettes.exec("create table if not exists dettes (idDette int primary key, idcompte, util1 int, util2 int, dette int)")){
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

            QSqlQuery queryDette(this->db);
            queryNbHistorique.exec("select max(nbDettes) from dettes");
            if(queryNbHistorique.next()){
                this->nbDettes = queryDette.value(0).toInt();
            }

            if(this->nbUtil == 0){

                addUtil("Thibault","Odor","to@test.fr","mdp", "1234567891234567891");
                addUtil("Marie-Luc","Moselle","mlm@test.fr","mdp", "1234567891234567891");
                addUtil("Emilia","Goeury","egm@test.fr","mdp", "1234567891234567891");
                addUtil("Max", "Illoul", "mi@test.fr", "mdp", "1234567891234567891");
            }

            if(this->nbCompte == 0){
                addComptePartage("Vacances", "1,2,4");
                addComptePartage("Soiree 29/11", "1,2,3");
                addComptePartage("Noel", "2,3,4");
                addComptePartage("Restaurant 12/06","3,4");
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
            if(this->nbDettes){
                addDettes(1, 1, 2, 30);
                addDettes(2, 3, 2, 1);
                addDettes(3, 1, 3, 80);
            }
        }
    }

    ///@brief Verifie qu'un utilisateur existe grace à son adresse mail (unique)
    ///
    /// @param std::string email : mail de l'utilisateur
    bool utilExist(std::string email){
        bool result = false;
        QSqlQuery query(this->db);
        query.exec("SELECT * from utilisateur where email ='"+QString::fromStdString(email)+"'");
        if(query.next()){
            result = true;
        }
        return result;
    }

    ///@brief Verifie que les informations nécessaire à la connection sont valides
    ///
    /// @param std::string email : email de l'utilisateur
    /// @param std::string mdp : mot de passe entré
    /// @return Renvoie l'identifiant de l'utilisateur si les informations sont correctes sinon 0
    int informationConnexionValide(std::string email,std::string mdp){

            QSqlQuery query(this->db);
            int result = 0;
            query.prepare("SELECT idutil, mdp FROM utilisateur WHERE email ='"+QString::fromStdString(email)+"'");
            query.exec();
            if(query.next()){
                if(query.value(1).toString() == QString::fromStdString(mdp)){
                    result = query.value(0).toInt();
                }
            }
            return result;
        }

    ///@brief Ajoute un utilisateur
    ///
    /// @param std::string prenom
    /// @param std::string nom
    /// @param std::string email : email de l'utilisateur
    /// @param std::string mdp
    /// @param std::string payement (non obligatoire)
    /// @return renvoie un boolean, vrai si l'ajout s'est bien passé, faux sinon
    bool addUtil(std::string prenom, std::string nom, std::string email, std::string mdp, std::string payement){
        bool result = false;
        QSqlQuery query(this->db);
        this->nbUtil++;
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

    ///@brief Ajoute un ComptePartagé
    ///
    /// @param std::string nom
    /// @param std::string listePart : liste des participants
    /// @return renvoie un boolean, vrai si l'ajout s'est bien passé, faux sinon
    bool addComptePartage(std::string nom, std::string listePart){
        this->nbCompte++;
        QSqlQuery query(this->db);
        query.prepare("INSERT INTO compte(idcompte,nom,listePart)"
                      "VALUES(?,?,?)");
        query.addBindValue(this->nbCompte);
        query.addBindValue(QString::fromStdString(nom));
        query.addBindValue(QString::fromStdString(listePart));

        return query.exec();
    }

    ///@brief Ajoute une cagnotte
    ///
    /// @param int respo : id de l'utilisateur qui crée la cagnotte
    /// @param int montant : montant ajouté au départ
    /// @param std::string nom
    /// @param std::string listePart
    /// @return renvoie un boolean, vrai si l'ajout s'est bien passé, faux sinon
    bool addCagnotte(int respo, int montant, std::string nom, std::string listePart){
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


    /// @brief Ajoute une dette entre un utilisateur 1 et un utilisateur 2
    ///
    /// @param int idcompte : id du compte concerné
    /// @param int util1
    /// @param int util2
    /// @param int dette : montant de la dette
    /// @return renvoie un boolean, vrai si l'ajout s'est bien passé, faux sinon
    bool addDettes(int idcompte,int util1, int util2, int dette){
        QSqlQuery query(this->db);
        bool result = false;
        query.prepare("SELECT * FROM dettes WHERE(idcompte, util1, util2)""VALUES(?,?,?)");
        query.addBindValue(idcompte);
        query.addBindValue(util1);
        query.addBindValue(util2);
        query.exec();
        if(query.next()){
            query.prepare("SELECT dette FROM dettes WHERE(idcompte, util1, util2)""VALUES(?,?,?)");
            query.addBindValue(idcompte);
            query.addBindValue(util1);
            query.addBindValue(util2);
            result = query.exec();
            int stc = query.value(0).toInt();
            stc += dette;
            query.prepare("UPDATE dettes SET dette="+QString::fromStdString(std::to_string(dette))+" WHERE(idcompte, util1, util2)""VALUES(?,?,?)"); //+QString::fromStdString(std::to_string(idcompte))+" AND util1="+QString::fromStdString(std::to_string(util1))+" AND util2="+QString::fromStdString(std::to_string(util2)));
            query.addBindValue(idcompte);
            query.addBindValue(util1);
            query.addBindValue(util2);
            result = query.exec();
        }else{
            query.prepare("INSERT INTO dettes(idDette, idcompte, util1, util2, dette)""VALUES(?,?,?,?,?)");
            this->nbDettes++;
            query.addBindValue(this->nbDettes);
            query.addBindValue(idcompte);
            query.addBindValue(util1);
            query.addBindValue(util2);
            query.addBindValue(dette);
            result = query.exec();
        }
        return result;
    }

    /// @brief Renvoie le prenom, nom d'un utilisateur
    ///
    /// @param int id : id de l'utilisateur
    /// @return QMap <QString, QString> contenant le prenom et nom
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
    /// @brief Renvoie une QMap contenant tout les id, prenom+nom
    ///
    /// @param int typeCompte : determine si compte partagé(1) ou cagnotte(2)
    /// @param int id : id du compte/cagnotte dont il fau
    /// @return QMap<QString, QString> contenant id, prenom+nom
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

    /// @brief Renvoie prenom, nom du responsable de cagnotte
    ///
    /// @param int idcagnotte
    /// @return QMap <QString, QString> prenom, nom
    QMap <QString, QString> getRespo(int idcagnotte){
        QSqlQuery query(this->db);
        QMap<QString , QString> map;

        query.exec("SELECT idrespo FROM cagnotte WHERE idcagnotte="+QString::fromStdString(std::to_string(idcagnotte)));
        if(query.next()){
            map = this->getUtil(query.value(0).toInt());
        }
        return map;
    }

    /// @brief Ajoute une sauvegarde des cations effectuées sur une cagnotte
    ///
    /// @param int idcagnotte
    /// @param int codeaction : type d'action sur la cagnotte
    /// @param int util1
    /// @param int util2
    /// @param int montant
    /// @return renvoie un boolean, vrai si l'ajout s'est bien passé, faux sinon
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

    /// @brief Renvoie le nom d'un compte
    ///
    /// @param int id : id compte
    /// @return QString
    QString getNomCompte(int id){
            QString result;
            QSqlQuery query(this->db);
            query.exec("SELECT nom FROM compte WHERE idcompte="+QString::fromStdString(std::to_string(id)));
            if(query.next()){
                result = query.value(0).toString();
            }
           return result;
        }

    /// @brief Renvoie le nom d'une cagnotte
    ///
    /// @param int id = id de la cagnotte
    /// @return QString
    QString getNomCagnotte(int id){
        QString result;
        QSqlQuery query(this->db);
        query.exec("SELECT nom FROM cagnotte WHERE idcagnotte="+QString::fromStdString(std::to_string(id)));
        if(query.next()){
            result = query.value(0).toString();
        }
       return result;
    }

        /// @brief Ajoute un utilisateur à un Compte partagé
        ///
        /// @param QString email : email de l'utilisateur
        /// @param int id : id du compte
        /// @return renvoie un boolean, vrai si l'ajout s'est bien passé, faux sinon
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

        /// @brief Ajoute un utilisateur à un Compte partagé
        ///
        /// @param QString email : email de l'utilisateur
        /// @param int id : id du compte
        /// @return renvoie un boolean, vrai si l'ajout s'est bien passé, faux sinon
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


        /// @brief Renvoie la liste des comptes auquel participe un utilisateur
        ///
        /// @param std::string email : email de l'utilisateur
        /// @return QMap<int, QString> contenant idCompte et nom du compte
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

        /// @brief Renvoie la liste des cagnotte auquel participe un utilisateur
        ///
        /// @param std::string email : email de l'utilisateur
        /// @return QMap<int, QString> contenant idCagnotte et nom de la cagnotte
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
        /// @brief Renvoie la liste des actions effectuées dans une cagnotte
        ///
        /// @param int idCagnotte
        /// @return QStringList
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


        /// @brief Renvoie le montant des fonds disponibles d'une cagnotte
        ///
        /// @param int idCagnotte
        /// @return int
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
        /// @brief Rajoute des fonds à une cagnotte
        ///
        /// @param QString fond : montant à rajouter
        /// @param int m_id : id de l'utilisateur qui rajoute
        /// @param int m_idcagnotte
        /// @return renvoie un boolean, vrai si l'ajout s'est bien passé, faux sinon
        bool addFonds(QString fond, int m_id, int m_idcagnotte){
            bool result = false;
            QSqlQuery query(this->db);
            query.exec("SELECT payement FROM utilisateur WHERE idutil="+QString::fromStdString(std::to_string(m_id)));
            if(query.next()){
                QString verif = query.value(0).toString();
                if(verif != "ABC" || verif !="" ){
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

        /// @brief Enlève des fonds à une cagnotte
        ///
        /// @param QString fond : montant à enlever
        /// @param int m_id : id de l'utilisateur qui enlève
        /// @param int m_idcagnotte
        /// @return renvoie un boolean, vrai si l'ajout s'est bien passé, faux sinon
        bool retirerFonds(QString fond, int m_id, int m_idcagnotte){
            bool result = false;
            QSqlQuery query(this->db);
            query.exec("SELECT payement FROM utilisateur WHERE idutil="+QString::fromStdString(std::to_string(m_id)));
            if(query.next()){
                QString verif = query.value(0).toString();
                if(verif != "ABC" || verif !=""){
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


        // @brief Renvoie la liste des dettes dans un compte
                ///
                /// @param int m_idcompte
                /// @return QStringList
                QStringList getListeDettes(int m_idcompte){
                    QStringList result;
                    QSqlQuery query(this->db);
                    query.prepare("SELECT * FROM dettes WHERE idcompte="+QString::fromStdString(std::to_string(m_idcompte)));
                    query.exec();
                    QString action;
                    while(query.next()){
                        //CREATE TABLE dettes (idcompte int primary key, util1 int, util2 int, dette int)
                        QMap <QString, QString> util1 = getUtil(query.value(2).toInt());
                        QMap <QString, QString> util2 = getUtil(query.value(3).toInt());
                        QString util1str ="";
                        QString util2str ="";

                        for(const auto &e : util1.toStdMap()){util1str.append(e.first+" "+e.second);}
                        for(const auto &e : util2.toStdMap()){util2str.append(e.first+" "+e.second);}

                        QString final = util2str+" doit à "+util1str+" "+query.value(4).toString()+"€";
                        result.append(final);
                    }
                    return result;
                }


        /// @brief Destructeur
        ~gestionnaireBDD(){
            this->db.close();
            QSqlDatabase::removeDatabase(this->path);
        }

};
#endif // GESTIONNAIREBDD_H
