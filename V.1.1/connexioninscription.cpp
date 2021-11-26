#include "connexioninscription.h"
#include "ui_connexioninscription.h"
#include "mainwindow.h"

ConnexionInscription::ConnexionInscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionInscription)
{
    ui->setupUi(this);
}

ConnexionInscription::~ConnexionInscription()
{
    delete ui;
}

void ConnexionInscription::on_bouttonAccueil_clicked()
{
    //MainWindow m; NOT WORKING
    //m.show();
    this->close();
}

