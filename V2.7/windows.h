#ifndef WINDOWS_H
#define WINDOWS_H

#include <QWidget>
#include <QStringListModel>
#include <QInputDialog>
#include "gestionnaireDialogue.h"

namespace Ui {
class windows;
}

class windows : public QWidget
{
    Q_OBJECT

public:
    explicit windows(QWidget *parent = nullptr);
    ~windows();
    ///@brief Permet de definir le modele dans Inscription
    void attachGestionnaireDialogue(GestionnaireDialogue *g);
    ///@brief Identifie l'utilisateur pour l'affichage graphique de AccueilUtilisateur
    void identifierUtilisateur(QMap <QString, QString> q);
    QString getLineEditeMail();
    QString getLineEditMdp();
    QString getLineEditNom();
    QString getLineEditeMailInscription();
    QString getLineEditMdpInscription();
    QString getLineEditPrenom();
    QString getLineEditPseudo();


private slots:
    void on_retour_accueil_clicked();
    void on_retour_cagnotte_clicked();
    void on_retour_comptepartage_clicked();
    void on_listComptePartage_clicked(const QModelIndex &index);
    void on_listCagnotte_clicked(const QModelIndex &index);
    void on_addPart_cagnotte_clicked();
    void on_addPart_compte_clicked();
    void on_boutton_connexion_clicked();
    void on_retourAccueil_connexion_clicked();
    void on_retourAccueil_inscription_clicked();
    void on_boutton_Inscription_clicked();
    void on_bouttonInscription_clicked();
    void on_bouttonConnexion_clicked();
    void clearList();

    void on_addFond_clicked();

    void on_retirerFond_clicked();

private:
    Ui::windows *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
    int m_idCompte;
    int m_idCagnotte;
    int m_id;
    QMap <QString, QString> m_utilisateur;
    QStringListModel *m_modelCompte;
    QStringListModel *m_modelCagnotte;
    QStringListModel *m_model_listeparticipant_compte;
    QStringListModel *m_model_listeparticipant_cagnotte;
    QStringListModel *m_model_listeHistorique;
};

#endif // WINDOWS_H
