#ifndef CONNEXIONINSCRIPTION_H
#define CONNEXIONINSCRIPTION_H

#include <QDialog>

namespace Ui {
class ConnexionInscription;
}

class ConnexionInscription : public QDialog
{
    Q_OBJECT

public:
    explicit ConnexionInscription(QWidget *parent = nullptr);
    ~ConnexionInscription();

private slots:
    void on_bouttonAccueil_clicked();

private:
    Ui::ConnexionInscription *ui;
};

#endif // CONNEXIONINSCRIPTION_H
