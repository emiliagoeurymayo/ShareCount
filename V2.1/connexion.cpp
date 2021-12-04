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

void Connexion::attachGestionnaireDialogue(GestionnaireDialogue *g)
{
    m_gestionnaireDialogue=*g;
}


void Connexion::on_retourAccueil_clicked()
{
    this->close();
    QWidget::parentWidget()->show();
}


void Connexion::on_boutton_connexion_clicked()
{
    std::string mail,mdp;
    mail=this->getLineEditeMail().toStdString();
    mdp=this->getLineEditMdp().toStdString();
    if(m_gestionnaireDialogue.verifConnexion(mail,mdp)){
        std::cout << "Compte existant Bonjour" << std::endl;
    }
    else{
        std::cout << "Compte Inconnu Aurevoir" << std::endl;
    }
}

