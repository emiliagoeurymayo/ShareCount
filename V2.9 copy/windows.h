#ifndef WINDOWS_H
#define WINDOWS_H

#include <QWidget>
#include <QStringListModel>
#include <QInputDialog>
#include "gestionnaireDialogue.h"

namespace Ui {
class windows;
}

/** @brief Classe windows utilisant ui.windows
 **
 ** Elle contient
 ** @ref windows(QWidget *)
 ** @ref ~windows()
 ** @ref QString getLineEditNom()
 ** @ref QString getLineEditeMail()
 ** @ref QString getLineEditMdp()
 ** @ref QString getLineEditPrenom()
 ** @ref QString getLineEditPseudo()
 ** @ref QString getLineEditeMailInscription();
 ** @ref QString getLineEditMdpInscription();
 ** @ref void attachGestionnaireDialogue(GestionnaireDialogue *)
 ** @ref void on_retour_accueil_clicked();
 ** @ref void on_retour_cagnotte_clicked();
 ** @ref void on_retour_comptepartage_clicked();
 ** @ref void on_listComptePartage_clicked(const QModelIndex &index);
 ** @ref void on_listCagnotte_clicked(const QModelIndex &index);
 ** @ref void on_addPart_cagnotte_clicked();
 ** @ref void on_addPart_compte_clicked();
 ** @ref void on_boutton_connexion_clicked();
 ** @ref void on_retourAccueil_connexion_clicked();
 ** @ref void on_retourAccueil_inscription_clicked();
 ** @ref void on_boutton_Inscription_clicked();
 ** @ref void on_bouttonInscription_clicked();
 ** @ref void on_bouttonConnexion_clicked();
 ** @ref void on_addFond_clicked();
 ** @ref void  on_retirerFond_clicked();
 **
 ** @version 2.8
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/
class windows : public QWidget
{
    Q_OBJECT

public:
    explicit windows(QWidget *parent = nullptr);
    ~windows();
    ///@brief Permet de definir le modele
    void attachGestionnaireDialogue(GestionnaireDialogue *g);
    ///@brief Identifie l'utilisateur pour l'affichage graphique de l'accueil utilisateur
    void identifierUtilisateur(QMap <QString, QString> q);
    ///@brief Retourne le texte qui se situe dans le champs mail de l'interface dans connexion
    QString getLineEditeMail();
    ///@brief Retourne le texte qui se situe dans le champs mdp de l'interface dans connexion
    QString getLineEditMdp();
    ///@brief Retourne le texte qui se situe dans le champs nom de l'interface dans inscription
    QString getLineEditNom();
    ///@brief Retourne le texte qui se situe dans le champs mail de l'interface dans inscription
    QString getLineEditeMailInscription();
    ///@brief Retourne le texte qui se situe dans le champs mdp de l'interface dans inscription
    QString getLineEditMdpInscription();
    ///@brief Retourne le texte qui se situe dans le champs prenom de l'interface dans inscription
    QString getLineEditPrenom();
    ///@brief Retourne le texte qui se situe dans le champs pseudo de l'interface dans inscription
    QString getLineEditPseudo();


private slots:
    ///@brief Slot s'activant lorsque le bouton retour dans la page accueil utilisateur est cliqué
    void on_retour_accueil_clicked();
    ///@brief Slot s'activant lorsque le bouton retour dans la page cagnotte est cliqué
    void on_retour_cagnotte_clicked();
    ///@brief Slot s'activant lorsque le bouton retour dans la page compte partagé est cliqué
    void on_retour_comptepartage_clicked();
    ///@brief Slot s'activant lorsque un élément de la liste de compte partagee est cliquée
    ///
    /// @param QModelIndex index de l'element cliqué
    void on_listComptePartage_clicked(const QModelIndex &index);
    ///@brief Slot s'activant lorsque un élément de la liste des cagnottes est cliquée
    ///
    /// @param QModelIndex index de l'element cliqué
    void on_listCagnotte_clicked(const QModelIndex &index);
    ///@brief Slot s'activant lorsque le bouton d'ajout de participant à une cagnotte est cliqué
    void on_addPart_cagnotte_clicked();
    ///@brief Slot s'activant lorsque le bouton d'ajout de participant à un compte partagé
    void on_addPart_compte_clicked();
    ///@brief Slot s'activant lorsque le bouton Connexion est cliqué
    void on_boutton_connexion_clicked();
    ///@brief Slot s'activant lorsque le bouton retour dans la page de Connexion est cliqué
    void on_retourAccueil_connexion_clicked();
    ///@brief Slot s'activant lorsque le bouton retour dans la page d'Inscription est cliqué
    void on_retourAccueil_inscription_clicked();
    ///@brief Slot s'activant lorsque le bouton créer un compte dans la page d'Inscription est cliqué
    void on_boutton_Inscription_clicked();
    ///@brief Slot s'activant lorsque le bouton inscription dans la page de Connexion/Inscription est cliqué
    void on_bouttonInscription_clicked();
    ///@brief Slot s'activant lorsque le bouton connexion dans la page de Connexion/Inscription est cliqué
    void on_bouttonConnexion_clicked();
    ///@brief Slot s'activant lorsque le bouton d'ajout de fond est cliqué
    void on_addFond_clicked();
    ///@brief Slot s'activant lorsque le bouton de retrait de fond cliqué
    void on_retirerFond_clicked();

private:
    Ui::windows *ui;
    ///@brief modele
    GestionnaireDialogue m_gestionnaireDialogue;
    ///@brief id du compte partagee selectionné
    int m_idCompte;
    ///@brief id de la cagnotte selectionné
    int m_idCagnotte;
    ///@brief id de l'utilisateur actuel
    int m_id;
    QMap <QString, QString> m_utilisateur;
    QStringListModel *m_modelCompte;
    QStringListModel *m_modelCagnotte;
    QStringListModel *m_model_listeparticipant_compte;
    QStringListModel *m_model_listeparticipant_cagnotte;
    QStringListModel *m_model_listeHistorique;
    QStringListModel *m_model_listeDettes;
};

#endif // WINDOWS_H
