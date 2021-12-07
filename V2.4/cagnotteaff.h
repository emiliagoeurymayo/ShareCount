#ifndef CAGNOTTEAFF_H
#define CAGNOTTEAFF_H

#include <QMainWindow>
#include <QLabel>
#include <QStringListModel>
#include "gestionnaireDialogue.h"
#include <QMap>
#include <QInputDialog>


namespace Ui {
    class cagnotteAff;
}

class cagnotteAff : public QMainWindow
{
     Q_OBJECT
public:
    cagnotteAff(QWidget *parent = nullptr);
    ~cagnotteAff();
    void attachGestionnaireDialogue(GestionnaireDialogue *g, int id);

private slots:
    void on_addPart_clicked();

private:
    Ui::cagnotteAff *ui;
    QStringListModel *m_model;
    QLabel *m_label;
    GestionnaireDialogue m_gestionnaireDialogue;
    int m_idCagnotte;
};


#endif // CAGNOTTEAFF_H
