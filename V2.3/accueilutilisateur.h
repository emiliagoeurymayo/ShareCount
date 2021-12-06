#ifndef ACCUEILUTILISATEUR_H
#define ACCUEILUTILISATEUR_H

#include <QMainWindow>
#include "gestionnaireDialogue.h"

namespace Ui {
class AccueilUtilisateur;
}

class AccueilUtilisateur : public QMainWindow
{
    Q_OBJECT

public:
    explicit AccueilUtilisateur(QWidget *parent = nullptr);
    ~AccueilUtilisateur();
    void attachGestionnaireDialogue(GestionnaireDialogue *g);
    void identifierUtilisateur(QMap <QString, QString> q);

private:
    Ui::AccueilUtilisateur *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
    QMap <QString, QString> m_utilisateur;
};

#endif // ACCUEILUTILISATEUR_H
