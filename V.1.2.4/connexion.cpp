#include "connexion.h"
#include "ui_mainwindow.h"
#include <iostream>

Connexion::Connexion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Connexion");
}

Connexion::~Connexion()
{
    delete ui;
}

QString Connexion::getLineEditNom()
{
    return ui->lineEdit_Nom->text();
}

QString Connexion::getLineEditeMail()
{
    return ui->lineEdit_eMail->text();
}

QString Connexion::getLineEditMdp()
{
    return ui->lineEdit_Mdp->text();
}

QString Connexion::getLineEditPrenom()
{
    return ui->lineEdit_Prenom->text();
}

QString Connexion::getLineEditPseudo()
{
    return ui->lineEdit_Pseudo->text();
}

void Connexion::on_boutton_Compte_clicked()
{
    std::string nom,mail,mdp,pseudo,prenom;
    nom=this->getLineEditNom().toStdString();
    mail=this->getLineEditeMail().toStdString();
    mdp=this->getLineEditMdp().toStdString();
    prenom=this->getLineEditPrenom().toStdString();
    pseudo=this->getLineEditPseudo().toStdString();
    m_gestionnaireDialogue.verifInformations(nom,mail,mdp,prenom,pseudo);
}

void Connexion::attachGestionnaireDialogue(GestionnaireDialogue g)
{
    m_gestionnaireDialogue=g;
}


void Connexion::on_retourAccueil_clicked()
{
    this->close();
    QWidget::parentWidget()->show();
}

