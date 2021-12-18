#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QMainWindow>
#include "gestionnaireDialogue.h"
#include "ui_inscription.h"
#pragma once
#include"connexioninscription.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Inscription; }
QT_END_NAMESPACE

/** @brief Classe Inscription utilisant ui.inscription
 **
 ** Elle contient
 ** @ref Inscription(QWidget *)
 ** @ref ~Inscription()
 ** @ref QString getLineEditNom()
 ** @ref QString getLineEditeMail()
 ** @ref QString getLineEditMdp()
 ** @ref QString getLineEditPrenom()
 ** @ref QString getLineEditPseudo()
 ** @ref void attachGestionnaireDialogue(GestionnaireDialogue *)
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/
class Inscription : public QMainWindow
{
    Q_OBJECT

public:
    ///@brief Constructeur
    Inscription(QWidget *parent = nullptr);
    ///@brief Destructeur
    ~Inscription();
    ///@brief Retourne le texte qui se situe dans le champs Nom de l'interface
    QString getLineEditNom();
    ///@brief Retourne le texte qui se situe dans le champs eMail de l'interface
    QString getLineEditeMail();
    ///@brief Retourne le texte qui se situe dans le champs Mdp de l'interface
    QString getLineEditMdp();
    ///@brief Retourne le texte qui se situe dans le champs Prenom de l'interface
    QString getLineEditPrenom();
    ///@brief Retourne le texte qui se situe dans le champs Pseudo de l'interface
    QString getLineEditPseudo();
    ///@brief Permet de definir le modele dans Inscription
    void attachGestionnaireDialogue(GestionnaireDialogue *g);

private slots:
    ///@brief Slot s'activant lorsque le bouton Compte est cliqué
    void on_boutton_Compte_clicked();
    ///@brief Slot s'activant lorsque le bouton retourAccueil est cliqué
    void on_retourAccueil_clicked();

private:
    Ui::Inscription *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
};
#endif // INSCRIPTION_H
