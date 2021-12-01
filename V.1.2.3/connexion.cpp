#include "connexion.h"
#include "ui_connexion.h"
#include <iostream>

Connexion::Connexion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Connexion)
{
    ui->setupUi(this);
    this->setWindowTitle("Connexion");
}

Connexion::~Connexion()
{
    delete ui;
}


QString Connexion::getLineEditeMail()
{
    return ui->lineEdit_eMail->text();
}

QString Connexion::getLineEditMdp()
{
    return ui->lineEdit_Mdp->text();
}

void Connexion::on_boutton_Compte_clicked()
{
    std::string nom,mail,mdp,pseudo,prenom;
    mail=this->getLineEditeMail().toStdString();
    mdp=this->getLineEditMdp().toStdString();
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

