#include "inscription.h"
#include "ui_connexion.h"
#include <iostream>

/** @brief Classe Inscription
 **
 ** classe de la fenetre d'inscription
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/

///@brief Constructeur
///
///@param parent : fenetre parent de la fenetre Inscription
Inscription::Inscription(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Inscription)
{
    ui->setupUi(this);
    this->setWindowTitle("Inscription");
    ui->buttonmailvalide->setChecked(true);
    qApp->setStyleSheet("QGroupBox  {  border: 0px;}");
}

///@brief Destructeur
Inscription::~Inscription()
{
    delete ui;
}

///@brief Retourne le texte qui se situe dans le champs Nom de l'interface
///
/// @return retourne le texte qui se situe dans le champs Nom de l'interface
QString Inscription::getLineEditNom()
{
    return ui->lineEdit_Nom->text();
}

///@brief Retourne le texte qui se situe dans le champs Mail de l'interface
///
/// @return retourne le texte qui se situe dans le champs eMail de l'interface
QString Inscription::getLineEditeMail()
{
    return ui->lineEdit_eMail->text();
}

///@brief Retourne le texte qui se situe dans le champs Mdp de l'interface
///
/// @return retourne le texte qui se situe dans le champs Mdp de l'interface
QString Inscription::getLineEditMdp()
{
    return ui->lineEdit_Mdp->text();
}

///@brief Retourne le texte qui se situe dans le champs Prenom de l'interface
///
/// @return retourne le texte qui se situe dans le champs Prenom de l'interface
QString Inscription::getLineEditPrenom()
{
    return ui->lineEdit_Prenom->text();
}

///@brief Retourne le texte qui se situe dans le champs Pseudo de l'interface
///
/// @return retourne le texte qui se situe dans le champs Pseudo de l'interface
QString Inscription::getLineEditPseudo()
{
    return ui->lineEdit_Pseudo->text();
}

///@brief Slot s'activant lorsque le bouton Compte est cliqué
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

///@brief Permet de definir le modele dans Inscription
///
/// @param GestionnaireDialogue * g : Pointeur du modele
void Inscription::attachGestionnaireDialogue(GestionnaireDialogue *g)
{
    m_gestionnaireDialogue=*g;
}

///@brief Slot s'activant lorsque le bouton retourAccueil est cliqué
void Inscription::on_retourAccueil_clicked()
{
    QWidget::parentWidget()->show();
    this->close();
}

