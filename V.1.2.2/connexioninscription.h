#ifndef CONNEXIONINSCRIPTION_H
#define CONNEXIONINSCRIPTION_H

#include <QDialog>
#include "inscription.h"
#include "gestionnaireDialogue.h"

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

    void on_bouttonConnexion_clicked();

private:
    Ui::ConnexionInscription *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
};

#endif // CONNEXIONINSCRIPTION_H
