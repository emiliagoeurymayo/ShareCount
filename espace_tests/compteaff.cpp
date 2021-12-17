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
    m_model = new QStringListModel(this);
    this->m_idCompte = id;

    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(1, this->m_idCompte);
    QStringList stc;

        for(const auto &e : map.toStdMap()){
         //qDebug() << e.first << "," << e.second << '\n';
               stc.append(e.first+" "+e.second);
        }

    m_model->setStringList(stc);
    QString str = m_gestionnaireDialogue.getNomCompte(this->m_idCompte);
    ui->liste->setModel(m_model);
    ui->nomCompte->setText(str);
}

void compteAff::on_addPart_clicked(){
    QString email = QInputDialog::getText(this, "Input dialog",
                                            "Adresse Email du nouveau participant", QLineEdit::Normal);

    qDebug() <<"result addPartCompt" <<m_gestionnaireDialogue.addPartCompt(email, this->m_idCompte);
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(1,this->m_idCompte);
    QStringList stc;
    for(const auto &e : map.toStdMap()){
        //qDebug() << e.first << "," << e.second << '\n';
        stc.append(e.first+" "+e.second);
    }
    m_model->setStringList(stc);
    ui->liste->setModel(m_model);
    this->show();
}

void compteAff::on_addDep_clicked(){
    QString depense = QInputDialog::getText(this, "Input dialog",
                                            "Nouvelle dépense", QLineEdit::Normal);
    qDebug() <<"result addDepenseCompt" <<m_gestionnaireDialogue.addDepCompt(depense, this->m_idCompte);
    QMap <QString, QString> map = m_gestionnaireDialogue.getDepenses(1,this->m_idCompte);
    QStringList stc;
    for(const auto &e : map.toStdMap()){
        //qDebug() << e.first << "," << e.second << '\n';
        stc.append(e.first+" "+e.second);
    }
    m_model->setStringList(stc);
    ui->liste->setModel(m_model);
    this->show();
}
