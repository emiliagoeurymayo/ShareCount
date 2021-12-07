#ifndef ACCUEILUTILISATEUR_H
#define ACCUEILUTILISATEUR_H

#include <QMainWindow>
#include "gestionnaireDialogue.h"
#include <QStringListModel>
#include "compteaff.h"
#include "cagnotteaff.h"

namespace Ui {
class AccueilUtilisateur;
}

/** @brief Classe AccueilUtilisateur utilisant ui.accueilutilisateur
 **
 ** Elle contient
 ** @ref AccueilUtilisateur(QWidget *)
 ** @ref ~AccueilUtilisateur()
 ** @ref void attachGestionnaireDialogue(GestionnaireDialogue *)
 ** @ref void identifierUtilisateur(QMap <QString, QString>)
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/
class AccueilUtilisateur : public QMainWindow
{
    Q_OBJECT

public:
    ///@brief Constructeur
    explicit AccueilUtilisateur(QWidget *parent = nullptr);
    ///@brief Destructeur
    ~AccueilUtilisateur();
    ///@brief Permet de definir le modele dans Inscription
    void attachGestionnaireDialogue(GestionnaireDialogue *g);
    ///@brief Identifie l'utilisateur pour l'affichage graphique de AccueilUtilisateur
    void identifierUtilisateur(QMap <QString, QString> q);

private slots:
    ///@brief Slot s'activant lorsque la liste de compte est cliqué
    void on_listCompte_clicked(const QModelIndex &index);

    void on_listCagnotte_clicked(const QModelIndex &index);

private:
    Ui::AccueilUtilisateur *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
    QMap <QString, QString> m_utilisateur;
    QStringListModel *m_modelCompte;
    QStringListModel *m_modelCagnotte;

};

#endif // ACCUEILUTILISATEUR_H
