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
    QMap <QString, QString> map = db.getParticipants(1,1);
    QStringList stc;

    for(const auto &e : map.toStdMap()){
     //qDebug() << e.first << "," << e.second << '\n';
           stc.append(e.first+" "+e.second);
    }

    this->db = db;
    this->idCompte = id;
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
}

