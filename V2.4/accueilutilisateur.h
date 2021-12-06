#ifndef ACCUEILUTILISATEUR_H
#define ACCUEILUTILISATEUR_H

#include <QMainWindow>
#include "gestionnaireDialogue.h"
#include <QStringListModel>
#include "compteaff.h"

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

private slots:
    void on_listCompte_clicked(const QModelIndex &index);

private:
    Ui::AccueilUtilisateur *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
    QMap <QString, QString> m_utilisateur;
    QStringListModel *model;
};

#endif // ACCUEILUTILISATEUR_H
