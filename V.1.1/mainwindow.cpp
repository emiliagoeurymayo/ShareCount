#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "connexioninscription.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getLineEditNom()
{
    return ui->lineEdit_Nom->text();
}

QString MainWindow::getLineEditeMail()
{
    return ui->lineEdit_eMail->text();
}

QString MainWindow::getLineEditMdp()
{
    return ui->lineEdit_Mdp->text();
}

QString MainWindow::getLineEditPrenom()
{
    return ui->lineEdit_Prenom->text();
}

QString MainWindow::getLineEditPseudo()
{
    return ui->lineEdit_Pseudo->text();
}

void MainWindow::on_boutton_Compte_clicked()
{
    std::string nom,mail,mdp,pseudo,prenom;
    nom=this->getLineEditNom().toStdString();
    mail=this->getLineEditeMail().toStdString();
    mdp=this->getLineEditMdp().toStdString();
    prenom=this->getLineEditPrenom().toStdString();
    pseudo=this->getLineEditPseudo().toStdString();
    m_gestionnaireDialogue.verifInformations(nom,mail,mdp,prenom,pseudo);
}

void MainWindow::attachGestionnaireDialogue(GestionnaireDialogue g)
{
    m_gestionnaireDialogue=g;
}


void MainWindow::on_retourAccueil_clicked()
{
    ConnexionInscription c;
    c.setModal(true);
    this->close();
    c.exec();
}

