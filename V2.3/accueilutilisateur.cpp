#include "accueilutilisateur.h"
#include "ui_accueilutilisateur.h"

AccueilUtilisateur::AccueilUtilisateur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AccueilUtilisateur)
{
    ui->setupUi(this);

}

AccueilUtilisateur::~AccueilUtilisateur()
{
    delete ui;
}

void AccueilUtilisateur::attachGestionnaireDialogue(GestionnaireDialogue * g)
{
    m_gestionnaireDialogue=*g;
}
void AccueilUtilisateur::identifierUtilisateur(QMap <QString, QString> q)
{
    m_utilisateur=q;

    QString nomprenom;

    for(const auto &e : m_utilisateur.toStdMap()){
            nomprenom.append(e.first+"\n"+e.second);
        }

    ui->NomPrenom->setText("Bonjour, "+nomprenom);
    //ui->Nom->setText(nomprenom.takeAt(0));

    model = new QStringListModel(this);
    QMap<int, QString> map = m_gestionnaireDialogue.getListeCompte();
    QStringList stc;

    for(const auto &e : map.toStdMap()){
        //qDebug() << e.first << "," << e.second << '\n';
        stc.append(QString::fromStdString(std::to_string(e.first))+"."+e.second);
    }

    if(!stc.isEmpty()){
        model->setStringList(stc);
        ui->listCompte->setModel(model);
    }
}

void AccueilUtilisateur::on_listCompte_clicked(const QModelIndex &index){
    compteAff* c = new compteAff(this);
    QString stc = index.data(Qt::DisplayRole).toString();
    int result = stc.split(".")[0].toInt();
    c->attachGestionnaireDialogue(&m_gestionnaireDialogue,result);
    c->show();
    this->hide();
}

