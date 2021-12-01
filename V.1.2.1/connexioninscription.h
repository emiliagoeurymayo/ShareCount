#ifndef CONNEXIONINSCRIPTION_H
#define CONNEXIONINSCRIPTION_H

#include <QDialog>
#include "inscription.h"
#include "GestionnaireDialogue.h"

namespace Ui {
class ConnexionInscription;
}

class ConnexionInscription : public QDialog
{
    Q_OBJECT

public:
    explicit ConnexionInscription(QWidget *parent = nullptr);
    ~ConnexionInscription();
    void attachGestionnaireDialogue(GestionnaireDialogue g);

private slots:
    void on_bouttonAccueil_clicked();

private:
    Ui::ConnexionInscription *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
};

#endif // CONNEXIONINSCRIPTION_H
