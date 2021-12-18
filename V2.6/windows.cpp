#include "windows.h"
#include "ui_windows.h"

windows::windows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::windows)
{
    ui->setupUi(this);
}

windows::~windows()
{
    delete ui;
}

void windows::on_retour_accueil_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void windows::on_retour_cagnotte_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void windows::on_retour_comptepartage_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void windows::attachGestionnaireDialogue(GestionnaireDialogue * g)
{
    m_gestionnaireDialogue=*g;
}

void windows::identifierUtilisateur(QMap <QString, QString> q){
    m_utilisateur=q;
    QString prenom;
    for(const auto &e : m_utilisateur.toStdMap()){prenom.append(e.first);}
    ui->NomPrenom->setText("Bonjour, "+prenom);
    m_modelCompte = new QStringListModel(this);
    QMap<int, QString> compte = m_gestionnaireDialogue.getListeCompte();
    QStringList cmp;
    for(const auto &e : compte.toStdMap()){
        cmp.append(QString::fromStdString(std::to_string(e.first))+"."+e.second);
    }
    m_modelCagnotte = new QStringListModel(this);
    QMap<int, QString> cagnotte = m_gestionnaireDialogue.getListeCagnotte();
    QStringList cag;
    for(const auto &e : cagnotte.toStdMap()){
        cag.append(QString::fromStdString(std::to_string(e.first))+"."+e.second);
    }
    if(!cmp.isEmpty()){
        m_modelCompte->setStringList(cmp);
        ui->listComptePartage->setModel(m_modelCompte);
    }
    if(!cag.isEmpty()){
        m_modelCagnotte->setStringList(cag);
        ui->listCagnotte->setModel(m_modelCagnotte);
    }
}

void windows::on_listComptePartage_clicked(const QModelIndex &index)
{
    QString stcstring = index.data(Qt::DisplayRole).toString();
    int id = stcstring.split(".")[0].toInt();
    m_model_listeparticipant_compte = new QStringListModel(this);
    this->m_idCompte = id;
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(1, this->m_idCompte);
    QStringList stc;
        for(const auto &e : map.toStdMap()){
            stc.append(e.first+" "+e.second);
        }
    m_model_listeparticipant_compte->setStringList(stc);
    QString str = m_gestionnaireDialogue.getNomCompte(this->m_idCompte);
    ui->liste_compte->setModel(m_model_listeparticipant_compte);
    ui->nomCompte->setText(str);
    ui->stackedWidget->setCurrentIndex(5);
}

void windows::on_listCagnotte_clicked(const QModelIndex &index)
{
    QString stcstring = index.data(Qt::DisplayRole).toString();
    int id = stcstring.split(".")[0].toInt();
    m_model_listeparticipant_cagnotte = new QStringListModel(this);
    this->m_idCagnotte = id;
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(2, this->m_idCagnotte);
    QStringList stc;
        for(const auto &e : map.toStdMap()){stc.append(e.first+" "+e.second);}
    m_model_listeparticipant_cagnotte->setStringList(stc);
    QString str = m_gestionnaireDialogue.getNomCagnotte(this->m_idCagnotte);
    ui->liste_cagnotte->setModel(m_model_listeparticipant_cagnotte);
    ui->nomCagnotte->setText(str);
    ui->stackedWidget->setCurrentIndex(4);
}

void windows::on_addPart_cagnotte_clicked()
{
    QString email = QInputDialog::getText(this, "Input dialog",
                                            "Adresse Email du nouveau participant", QLineEdit::Normal);
    qDebug() <<"result addPartCompt" << m_gestionnaireDialogue.addPartCagnotte(email, this->m_idCagnotte);
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(1,this->m_idCagnotte);
    QStringList stc;
    for(const auto &e : map.toStdMap()){stc.append(e.first+" "+e.second);}
    m_model_listeparticipant_cagnotte->setStringList(stc);
    ui->liste_cagnotte->setModel(m_model_listeparticipant_cagnotte);
    this->show();
}

void windows::on_addPart_compte_clicked()
{
    QString email = QInputDialog::getText(this, "Input dialog",
                                            "Adresse Email du nouveau participant", QLineEdit::Normal);
    qDebug() <<"result addPartCompt" <<m_gestionnaireDialogue.addPartCompt(email, this->m_idCompte);
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(1,this->m_idCompte);
    QStringList stc;
    for(const auto &e : map.toStdMap()){stc.append(e.first+" "+e.second);}
    m_model_listeparticipant_compte->setStringList(stc);
    ui->liste_compte->setModel(m_model_listeparticipant_compte);
    this->show();
}

QString windows::getLineEditeMail(){return ui->lineEdit_eMail->text();}
QString windows::getLineEditMdp(){return ui->lineEdit_Mdp->text();}
QString windows::getLineEditNom(){return ui->lineEdit_Nom->text();}
QString windows::getLineEditeMailInscription(){return ui->lineEdit_eMail_inscription->text();}
QString windows::getLineEditMdpInscription(){return ui->lineEdit_Mdp_inscription->text();}
QString windows::getLineEditPrenom(){return ui->lineEdit_Prenom->text();}
QString windows::getLineEditPseudo(){return ui->lineEdit_Pseudo->text();}

void windows::on_boutton_connexion_clicked()
{
    std::string mail,mdp;
    mail=this->getLineEditeMail().toStdString();
    mdp=this->getLineEditMdp().toStdString();
    m_id = m_gestionnaireDialogue.verifConnexion(mail,mdp);
    if(m_id != 0 ){
        this->clearList();//Probablement inutile
        identifierUtilisateur(m_gestionnaireDialogue.identifierUtilisateur(m_id));
        ui->stackedWidget->setCurrentIndex(3);
    }
}

void windows::on_retourAccueil_connexion_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void windows::on_retourAccueil_inscription_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void windows::on_boutton_Inscription_clicked()
{
    std::string nom,mail,mdp,pseudo,prenom;
    nom=this->getLineEditNom().toStdString();
    mail=this->getLineEditeMailInscription().toStdString();
    mdp=this->getLineEditMdpInscription().toStdString();
    prenom=this->getLineEditPrenom().toStdString();
    pseudo=this->getLineEditPseudo().toStdString();
    m_gestionnaireDialogue.verifInformations(nom,mail,mdp,prenom,pseudo,ui->buttonmailvalide->isChecked());
}

void windows::on_bouttonInscription_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void windows::on_bouttonConnexion_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void windows::clearList(){
    ui->listComptePartage->setModel(new QStringListModel);
    ui->listCagnotte->setModel(new QStringListModel);
}
