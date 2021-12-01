#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QMainWindow>
#include "GestionnaireDialogue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Inscription : public QMainWindow
{
    Q_OBJECT

public:
    Inscription(QWidget *parent = nullptr);
    ~Inscription();
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
#endif // INSCRIPTION_H
