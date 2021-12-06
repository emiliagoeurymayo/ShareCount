#ifndef COMPTEAFF_H
#define COMPTEAFF_H

#include <QMainWindow>
#include <QLabel>
#include <QStringListModel>
#include "gestionnaireDialogue.h"
#include <QMap>
#include <QInputDialog>


namespace Ui {
    class compteAff;
}

class compteAff : public QMainWindow
{
     Q_OBJECT
public:
    compteAff(QWidget *parent = nullptr);
    ~compteAff();
    void attachGestionnaireDialogue(GestionnaireDialogue *g, int id);
private slots:
    void on_addPart_clicked();

private:
    Ui::compteAff *ui;
    QStringListModel *m_model;
    QLabel *m_label;
    GestionnaireDialogue m_gestionnaireDialogue;
    int m_idCompte;
};

#endif // COMPTEAFF_H
