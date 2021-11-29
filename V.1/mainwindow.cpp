#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

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

void MainWindow::on_boutton_Compte_clicked()
{
    std::string nom,mail,mdp;
    nom=this->getLineEditNom().toStdString();
    mail=this->getLineEditeMail().toStdString();
    mdp=this->getLineEditMdp().toStdString();
    m_gestionnaireDialogue.verifInformations(nom,mail,mdp);
}

void MainWindow::attachGestionnaireDialogue(GestionnaireDialogue g)
{
    m_gestionnaireDialogue=g;
}



