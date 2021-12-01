#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMainWindow>
#include "gestionnaireDialogue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Connexion : public QMainWindow
{
    Q_OBJECT

public:
    Connexion(QWidget *parent = nullptr);
    ~Connexion();
    QString getLineEditNom();
    QString getLineEditeMail();
    QString getLineEditMdp();
    QString getLineEditPrenom();
    QString getLineEditPseudo();
    void attachGestionnaireDialogue(GestionnaireDialogue g);

private slots:
    void on_boutton_Compte_clicked();

    void on_retourAccueil_clicked();

private:
    Ui::MainWindow *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
};
#endif // CONNEXION_H
