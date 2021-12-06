#include "connexion.h"
#include "ui_connexion.h"
#include <iostream>

/** @brief Classe Connexion
 **
 ** classe de la fenetre Connexion
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/

///@brief Constructeur
///
///@param parent : fenetre parent de la fenetre Connexion
Connexion::Connexion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Connexion)
{
    ui->setupUi(this);
    this->setWindowTitle("Connexion");
}

///@brief Destructeur
Connexion::~Connexion()
{
    delete ui;
}

///@brief Retourne le texte qui se situe dans le champs Email de l'interface
///
/// @return retourne le texte qui se situe dans le champs Email de l'interface
QString Connexion::getLineEditeMail()
{
    return ui->lineEdit_eMail->text();
}

///@brief Retourne le texte qui se situe dans le champs Mdp de l'interface
///
/// @return retourne le texte qui se situe dans le champs Mdp de l'interface
QString Connexion::getLineEditMdp()
{
    return ui->lineEdit_Mdp->text();
}

///@brief Permet de definir le modele dans Connexion
///
/// @param GestionnaireDialogue * g : Pointeur du modele
void Connexion::attachGestionnaireDialogue(GestionnaireDialogue *g)
{
    m_gestionnaireDialogue=*g;
}

///@brief Slot s'activant lorsque le bouton retourAccueil est cliqué
void Connexion::on_retourAccueil_clicked()
{
    this->close();
    QWidget::parentWidget()->show();
}

///@brief Slot s'activant lorsque le bouton Connexion est cliqué
void Connexion::on_boutton_connexion_clicked()
{
    std::string mail,mdp;
    mail=this->getLineEditeMail().toStdString();
    mdp=this->getLineEditMdp().toStdString();
    int id = m_gestionnaireDialogue.verifConnexion(mail,mdp);
    if(id != 0 ){
        //std::cout << "Compte existant Bonjour" << std::endl;
        AccueilUtilisateur* m = new AccueilUtilisateur(this);
        m->attachGestionnaireDialogue(&m_gestionnaireDialogue);
        m->identifierUtilisateur(m_gestionnaireDialogue.identifierUtilisateur(id));
        m->show();
        this->hide();
    }
    else{
        //std::cout << "Compte Inconnu Aurevoir" << std::endl;
    }
}

