#include "connexioninscription.h"
#include "ui_connexioninscription.h"

ConnexionInscription::ConnexionInscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionInscription){ui->setupUi(this);}

ConnexionInscription::~ConnexionInscription()
{
    delete ui;
}


void ConnexionInscription::attachGestionnaireDialogue(GestionnaireDialogue g)
{
    m_gestionnaireDialogue=g;
}

void ConnexionInscription::on_bouttonConnexion_clicked()
{
    Connexion* m = new Connexion(this);
    m->attachGestionnaireDialogue(m_gestionnaireDialogue);
    m->show();
    this->hide();
}


void ConnexionInscription::on_bouttonInscription_clicked()
{
    Inscription* m = new Inscription(this);
    m->attachGestionnaireDialogue(m_gestionnaireDialogue);
    m->show();
    this->hide();
}

