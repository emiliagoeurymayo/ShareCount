#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMainWindow>
#include "gestionnaireDialogue.h"
#include "accueilutilisateur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Connexion; }
QT_END_NAMESPACE

/** @brief Classe Connexion utilisant ui.connexion
 **
 ** Elle contient
 ** @ref Connexion(QWidget *)
 ** @ref ~Connexion()
 ** @ref QString getLineEditeMail()
 ** @ref QString getLineEditMdp()
 ** @ref void attachGestionnaireDialogue(GestionnaireDialogue *)
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/
class Connexion : public QMainWindow
{
    Q_OBJECT

public:
    ///@brief Constructeur
    Connexion(QWidget *parent = nullptr);
    ///@brief Destructeur
    ~Connexion();
    ///@brief Retourne le texte qui se situe dans le champs eMail de l'interface
    QString getLineEditeMail();
    ///@brief Retourne le texte qui se situe dans le champs Mdp de l'interface
    QString getLineEditMdp();
    ///@brief Permet de definir le modele dans Inscription
    void attachGestionnaireDialogue(GestionnaireDialogue *g);

private slots:
    ///@brief Slot s'activant lorsque le bouton retourAccueil est cliqué
    void on_retourAccueil_clicked();
    ///@brief Slot s'activant lorsque le bouton Connexion est cliqué
    void on_boutton_connexion_clicked();

private:
    Ui::Connexion *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
};
#endif // CONNEXION_H
