#include "compteaff.h"
#include "ui_compteAff.h"

compteAff::compteAff(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::compteAff){
    ui->setupUi(this);
}

compteAff::~compteAff(){
    delete ui;
}

void compteAff::attachGestionnaireDialogue(GestionnaireDialogue *g, int id){
    m_gestionnaireDialogue=*g;
    model = new QStringListModel(this);
    this->idCompte = id;
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(1, this->idCompte);
    QStringList stc;

    for(const auto &e : map.toStdMap()){
        //qDebug() << e.first << "," << e.second << '\n';
        stc.append(e.first+" "+e.second);
    }

    model->setStringList(stc);
    QString str = m_gestionnaireDialogue.getNomCompte(this->idCompte);
    ui->liste->setModel(model);
    ui->nomCompte->setText(str);
}

void compteAff::on_addPart_clicked(){
    QString text = QInputDialog::getText(0, "Input dialog",
                                            "Adresse Email du nouveau participant", QLineEdit::Normal);

    qDebug() << m_gestionnaireDialogue.addPartCompt(text, this->idCompte);
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(1,this->idCompte);
    QStringList stc;

    for(const auto &e : map.toStdMap()){
        qDebug() << e.first << "," << e.second << '\n';
        stc.append(e.first+" "+e.second);
    }
    model->setStringList(stc);
    ui->liste->setModel(model);
}

