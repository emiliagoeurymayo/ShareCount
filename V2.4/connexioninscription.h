#ifndef CONNEXIONINSCRIPTION_H
#define CONNEXIONINSCRIPTION_H

#include <QDialog>
#include <QCloseEvent>
#pragma once    //A VOIR SI ON GARDE
#include "inscription.h"
#include "connexion.h"
#include "gestionnaireDialogue.h"

namespace Ui {
class ConnexionInscription;
}

/** @brief Classe ConnexionInscription utilisant ui.connexioninscription
 **
 ** Elle contient
 ** @ref ConnexionInscription(QWidget *)
 ** @ref virtual ~ConnexionInscription()
 ** @ref void attachGestionnaireDialogue(GestionnaireDialogue *)
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/
class ConnexionInscription : public QDialog
{
    Q_OBJECT

public:
    ///@brief Constructeur
    explicit ConnexionInscription(QWidget *parent = nullptr);
    ///@brief Destructeur
    ~ConnexionInscription();
    ///@brief Permet de definir le modele dans Inscription
    void attachGestionnaireDialogue(GestionnaireDialogue * g);

private slots:
    ///@brief Slot s'activant lorsque le bouton Connexion est cliqué
    void on_bouttonConnexion_clicked();
    ///@brief Slot s'activant lorsque le bouton Inscription est cliqué
    void on_bouttonInscription_clicked();

private:
    Ui::ConnexionInscription *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
};

#endif // CONNEXIONINSCRIPTION_H
