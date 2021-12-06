#include "accueilutilisateur.h"
#include "ui_accueilutilisateur.h"

AccueilUtilisateur::AccueilUtilisateur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AccueilUtilisateur)
{
    ui->setupUi(this);
}

AccueilUtilisateur::~AccueilUtilisateur()
{
    delete ui;
}

void AccueilUtilisateur::attachGestionnaireDialogue(GestionnaireDialogue * g)
{
    m_gestionnaireDialogue=*g;
}
void AccueilUtilisateur::identifierUtilisateur(QMap <QString, QString> q)
{
    m_utilisateur=q;

    ui->Prenom->setText("Bonjour, "+m_utilisateur.first());
    ui->Nom->setText(m_utilisateur.last());
}
