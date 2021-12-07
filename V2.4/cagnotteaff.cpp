#include "cagnotteaff.h"
#include "ui_cagnotteAff.h"


cagnotteAff::cagnotteAff(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cagnotteAff){
    ui->setupUi(this);
}

cagnotteAff::~cagnotteAff(){
    delete ui;
}

void cagnotteAff::attachGestionnaireDialogue(GestionnaireDialogue *g, int id){
    m_gestionnaireDialogue=*g;
    m_idCagnotte = id;
    m_model = new QStringListModel(this);
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(2, this->m_idCagnotte);
    QStringList stc;

    for(const auto &e : map.toStdMap()){
     //qDebug() << e.first << "," << e.second << '\n';
           stc.append(e.first+" "+e.second);
    }

    m_model->setStringList(stc);
    QString str = m_gestionnaireDialogue.getNomCagnotte(this->m_idCagnotte);
    ui->liste->setModel(m_model);
    ui->nomCagnotte->setText(str);
}

void cagnotteAff::on_addPart_clicked(){
    QString email = QInputDialog::getText(this, "Input dialog",
                                            "Adresse Email du nouveau participant", QLineEdit::Normal);

    //m_model = new QStringListModel(this);
    qDebug() <<"result addPartCompt" << m_gestionnaireDialogue.addPartCagnotte(email, this->m_idCagnotte);
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(1,this->m_idCagnotte);
    QStringList stc;
    for(const auto &e : map.toStdMap()){
        //qDebug() << e.first << "," << e.second << '\n';
        stc.append(e.first+" "+e.second);
    }
    m_model->setStringList(stc);
    ui->liste->setModel(m_model);
    this->show();
}
