#include "connexioninscription.h"
#include "ui_connexioninscription.h"

/** @brief Classe ConnexionInscription
 **
 ** classe de la fenetre ConnexionInscription
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/

///@brief Constructeur
///
///@param parent : fenetre parent de la fenetre ConnexionInscription
ConnexionInscription::ConnexionInscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionInscription){ui->setupUi(this);}

///@brief Destructeur
ConnexionInscription::~ConnexionInscription()
{
    delete ui;
}

///@brief Permet de definir le modele dans ConnexionInscription
///
/// @param GestionnaireDialogue * g : Pointeur du modele
void ConnexionInscription::attachGestionnaireDialogue(GestionnaireDialogue * g)
{
    m_gestionnaireDialogue=*g;
}

///@brief Slot s'activant lorsque le bouton Connexion est cliqué
void ConnexionInscription::on_bouttonConnexion_clicked()
{
    Connexion* m = new Connexion(this);
    m->attachGestionnaireDialogue(&m_gestionnaireDialogue);
    m->show();
    this->hide();
}

///@brief Slot s'activant lorsque le bouton Inscription est cliqué
void ConnexionInscription::on_bouttonInscription_clicked()
{
    Inscription* m = new Inscription(this);
    m->attachGestionnaireDialogue(&m_gestionnaireDialogue);
    m->show();
    this->hide();
}

