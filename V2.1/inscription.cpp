#include "inscription.h"
#include "ui_connexion.h"
#include <iostream>

Inscription::Inscription(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Inscription)
{
    ui->setupUi(this);
    this->setWindowTitle("Inscription");
    ui->buttonmailvalide->setChecked(true);
    qApp->setStyleSheet("QGroupBox  {  border: 0px;}");
}

Inscription::~Inscription()
{
    delete ui;
}

QString Inscription::getLineEditNom()
{
    return ui->lineEdit_Nom->text();
}

QString Inscription::getLineEditeMail()
{
    return ui->lineEdit_eMail->text();
}

QString Inscription::getLineEditMdp()
{
    return ui->lineEdit_Mdp->text();
}

QString Inscription::getLineEditPrenom()
{
    return ui->lineEdit_Prenom->text();
}

QString Inscription::getLineEditPseudo()
{
    return ui->lineEdit_Pseudo->text();
}

void Inscription::on_boutton_Compte_clicked()
{
    std::string nom,mail,mdp,pseudo,prenom;
    nom=this->getLineEditNom().toStdString();
    mail=this->getLineEditeMail().toStdString();
    mdp=this->getLineEditMdp().toStdString();
    prenom=this->getLineEditPrenom().toStdString();
    pseudo=this->getLineEditPseudo().toStdString();
    m_gestionnaireDialogue.verifInformations(nom,mail,mdp,prenom,pseudo,ui->buttonmailvalide->isChecked());
}

void Inscription::attachGestionnaireDialogue(GestionnaireDialogue *g)
{
    m_gestionnaireDialogue=*g;
}


void Inscription::on_retourAccueil_clicked()
{
    QWidget::parentWidget()->show();
    this->close();
}

