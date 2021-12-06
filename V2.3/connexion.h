#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMainWindow>
#include "gestionnaireDialogue.h"
#include "accueilutilisateur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Connexion; }
QT_END_NAMESPACE

class Connexion : public QMainWindow
{
    Q_OBJECT

public:
    Connexion(QWidget *parent = nullptr);
    ~Connexion();
    QString getLineEditeMail();
    QString getLineEditMdp();
    void attachGestionnaireDialogue(GestionnaireDialogue *g);

private slots:
    void on_retourAccueil_clicked();

    void on_boutton_connexion_clicked();

private:
    Ui::Connexion *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
};
#endif // CONNEXION_H
