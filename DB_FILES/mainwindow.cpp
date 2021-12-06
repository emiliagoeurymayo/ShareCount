#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestionnaireBDD.h"
#include <QInputDialog>

MainWindow::MainWindow(gestionnaireBDD db,int id, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    this->idCompte = id;
    QMap <QString, QString> map = db.getParticipants(this->idCompte,this->idCompte);
    QStringList stc;

    for(const auto &e : map.toStdMap()){
     //qDebug() << e.first << "," << e.second << '\n';
           stc.append(e.first+" "+e.second);
    }

    this->db = db;

    model->setStringList(stc);
    QString str = db.getNomCompte(1);
    ui->liste->setModel(model);
    ui->nomCompte->setText(str);
}

void MainWindow::on_pushButton_clicked(){

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addPart_clicked()
{
    QString text = QInputDialog::getText(0, "Input dialog",
                                            "Adresse Email du nouveau participant", QLineEdit::Normal);

    qDebug() << this->db.addPartCompt(text, this->idCompte);

    QMap <QString, QString> map = db.getParticipants(this->idCompte,this->idCompte);
    QStringList stc;

    for(const auto &e : map.toStdMap()){
     //qDebug() << e.first << "," << e.second << '\n';
           stc.append(e.first+" "+e.second);
    }
    model->setStringList(stc);
    ui->liste->setModel(model);
    update();
}

