#include "windows.h"
#include "ui_windows.h"

/** @brief Classe Windows
 **
 ** classe de la fenetre principale
 **
 ** @version 2.8
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/

///@brief Constructeur
///
///@param parent : parent = null
windows::windows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::windows)
{
    ui->setupUi(this);
}

///@brief Destructeur
windows::~windows()
{
    delete ui;
}

///@brief Slot s'activant lorsque le bouton retour dans la page accueil utilisateur est cliqué
void windows::on_retour_accueil_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
}

///@brief Slot s'activant lorsque le bouton retour dans la page cagnotte est cliqué
void windows::on_retour_cagnotte_clicked(){
    ui->stackedWidget->setCurrentIndex(3);
}

///@brief Slot s'activant lorsque le bouton retour dans la page compte partagé est cliqué
void windows::on_retour_comptepartage_clicked(){
    ui->stackedWidget->setCurrentIndex(3);
}

///@brief Permet de definir le modele dans ConnexionInscription
///
/// @param GestionnaireDialogue * g : Pointeur du modele
void windows::attachGestionnaireDialogue(GestionnaireDialogue * g){
    m_gestionnaireDialogue=*g;
}

///@brief Identifie l'utilisateur pour l'affichage graphique de AccueilUtilisateur
///
/// @param QMap contenant la liste des compte identifié
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

///@brief Slot s'activant lorsque un élément de la liste de compte partagee est cliquée
///
/// @param QModelIndex index de l'element cliqué
void windows::on_listComptePartage_clicked(const QModelIndex &index)
{
    QString stcstring = index.data(Qt::DisplayRole).toString();
    int id = stcstring.split(".")[0].toInt();
    this->m_idCompte = id;

    m_model_listeparticipant_compte = new QStringListModel(this);
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(1, this->m_idCompte);
    QStringList stc;
        for(const auto &e : map.toStdMap()){
            stc.append(e.first+" "+e.second);
        }
    m_model_listeparticipant_compte->setStringList(stc);

    m_model_listeDettes = new QStringListModel(this);
    QStringList dettes = m_gestionnaireDialogue.getListeDettes(m_idCompte);
    m_model_listeDettes->setStringList(dettes);

    QString str = m_gestionnaireDialogue.getNomCompte(this->m_idCompte);
    ui->liste_compte->setModel(m_model_listeparticipant_compte);
    ui->listeDettes->setModel(m_model_listeDettes);
    ui->nomCompte->setText(str);
    ui->stackedWidget->setCurrentIndex(5);
}

///@brief Slot s'activant lorsque un élément de la liste des cagnottes est cliquée
///
/// @param QModelIndex index de l'element cliqué
void windows::on_listCagnotte_clicked(const QModelIndex &index){
    QString stcstring = index.data(Qt::DisplayRole).toString();
    int id = stcstring.split(".")[0].toInt();

    m_model_listeparticipant_cagnotte = new QStringListModel(this);
    this->m_idCagnotte = id;
    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(2, this->m_idCagnotte);
    QStringList stc;
        for(const auto &e : map.toStdMap()){stc.append(e.first+" "+e.second);}
    m_model_listeparticipant_cagnotte->setStringList(stc);

    m_model_listeHistorique = new QStringListModel(this);
    QStringList histo = m_gestionnaireDialogue.getListeHistorique(m_idCagnotte);
    m_model_listeHistorique->setStringList(histo);

    QString str = m_gestionnaireDialogue.getNomCagnotte(this->m_idCagnotte);
    ui->liste_cagnotte->setModel(m_model_listeparticipant_cagnotte);
    ui->liste_Historique->setModel(m_model_listeHistorique);
    ui->nomCagnotte->setText(str);
    ui->fondDispo->setText("Fonds disponibles : "+QString::number(m_gestionnaireDialogue.getFondsDispo(this->m_idCagnotte))+"€");
    ui->stackedWidget->setCurrentIndex(4);
}

///@brief Slot s'activant lorsque le bouton d'ajout de participant à une cagnotte est cliqué
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

///@brief Slot s'activant lorsque le bouton d'ajout de participant à un compte partagé
void windows::on_addPart_compte_clicked()
{
    QString email = QInputDialog::getText(this, "Input dialog","Adresse Email du nouveau participant", QLineEdit::Normal);

    qDebug() <<"result addPartCompt" <<m_gestionnaireDialogue.addPartCompt(email, this->m_idCompte);

    QMap <QString, QString> map = m_gestionnaireDialogue.getParticipants(1,this->m_idCompte);
    QStringList stc;
    for(const auto &e : map.toStdMap()){stc.append(e.first+" "+e.second);}
    m_model_listeparticipant_compte->setStringList(stc);
    ui->liste_compte->setModel(m_model_listeparticipant_compte);
    this->show();
}


///@brief Retourne le texte qui se situe dans le champs Mail de l'interface de Connexion
///
/// @return retourne le texte qui se situe dans le champs Mail de l'interface de Connexion
QString windows::getLineEditeMail(){return ui->lineEdit_eMail->text();}

///@brief Retourne le texte qui se situe dans le champs Mdp de l'interface de Connexion
///
/// @return retourne le texte qui se situe dans le champs Mdp de l'interface de Connexion
QString windows::getLineEditMdp(){return ui->lineEdit_Mdp->text();}

///@brief Retourne le texte qui se situe dans le champs Nom de l'interface d'inscription
///
/// @return retourne le texte qui se situe dans le champs Nom de l'interface d'inscription
QString windows::getLineEditNom(){return ui->lineEdit_Nom->text();}

///@brief Retourne le texte qui se situe dans le champs Mail de l'interface d'inscription
///
/// @return retourne le texte qui se situe dans le champs Mail de l'interface d'inscription
QString windows::getLineEditeMailInscription(){return ui->lineEdit_eMail_inscription->text();}

///@brief Retourne le texte qui se situe dans le champs Mdp de l'interface d'inscription
///
/// @return retourne le texte qui se situe dans le champs Mdp de l'interface d'inscription
QString windows::getLineEditMdpInscription(){return ui->lineEdit_Mdp_inscription->text();}

///@brief Retourne le texte qui se situe dans le champs Prenom de l'interface d'inscription
///
/// @return retourne le texte qui se situe dans le champs Prenom de l'interface d'inscription
QString windows::getLineEditPrenom(){return ui->lineEdit_Prenom->text();}

///@brief Retourne le texte qui se situe dans le champs Pseudo de l'interface d'inscription
///
/// @return retourne le texte qui se situe dans le champs Pseudo de l'interface d'inscription
QString windows::getLineEditPseudo(){return ui->lineEdit_Pseudo->text();}

///@brief Slot s'activant lorsque le bouton Connexion est cliqué
void windows::on_boutton_connexion_clicked()
{
    std::string mail,mdp;
    mail=this->getLineEditeMail().toStdString();
    mdp=this->getLineEditMdp().toStdString();
    m_id = m_gestionnaireDialogue.verifConnexion(mail,mdp);
    if(m_id != 0 ){
        identifierUtilisateur(m_gestionnaireDialogue.identifierUtilisateur(m_id));
        ui->stackedWidget->setCurrentIndex(3);
    }
}

///@brief Slot s'activant lorsque le bouton retour dans la page de Connexion est cliqué
void windows::on_retourAccueil_connexion_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

///@brief Slot s'activant lorsque le bouton retour dans la page d'Inscription est cliqué
void windows::on_retourAccueil_inscription_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

///@brief Slot s'activant lorsque le bouton créer un compte dans la page d'Inscription est cliqué
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

///@brief Slot s'activant lorsque le bouton inscription dans la page de Connexion/Inscription est cliqué
void windows::on_bouttonInscription_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

///@brief Slot s'activant lorsque le bouton connexion dans la page de Connexion/Inscription est cliqué
void windows::on_bouttonConnexion_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

///@brief Slot s'activant lorsque le bouton d'ajout de fond est cliqué
void windows::on_addFond_clicked(){
    QString fond = QInputDialog::getText(this, "Input dialog","Fonds à ajouter", QLineEdit::Normal);
    if(m_gestionnaireDialogue.addFonds(fond, m_id, m_idCagnotte)){
        ui->fondDispo->setText("Fonds disponibles : "+QString::number(m_gestionnaireDialogue.getFondsDispo(this->m_idCagnotte))+"€");
        QStringList histo = m_gestionnaireDialogue.getListeHistorique(m_idCagnotte);
        m_model_listeHistorique->setStringList(histo);
        ui->liste_Historique->setModel(m_model_listeHistorique);
    }
}

///@brief Slot s'activant lorsque le bouton de retrait de fond cliqué
void windows::on_retirerFond_clicked(){
    QString fond = QInputDialog::getText(this, "Input dialog","Fonds à retirer", QLineEdit::Normal);
    if(m_gestionnaireDialogue.retirerFonds(fond, m_id, m_idCagnotte)){
        ui->fondDispo->setText("Fonds disponibles : "+QString::number(m_gestionnaireDialogue.getFondsDispo(this->m_idCagnotte))+"€");
        QStringList histo = m_gestionnaireDialogue.getListeHistorique(m_idCagnotte);
        m_model_listeHistorique->setStringList(histo);
        ui->liste_Historique->setModel(m_model_listeHistorique);
    }
}


void windows::on_addDep_clicked(){
    QModelIndex index = ui->liste_compte->currentIndex();
    QString stcstring = index.data(Qt::DisplayRole).toString();
    int id = stcstring.split(".")[0].toInt();
    if(id!=0 && id!=m_id){
        QString montant = QInputDialog::getText(this, "Input dialog","Montant de votre dette", QLineEdit::Normal);
        if(m_gestionnaireDialogue.addDettes(m_idCompte, m_id, id, montant.toInt())){
            m_model_listeDettes = new QStringListModel(this);
            QStringList dettes = m_gestionnaireDialogue.getListeDettes(m_idCompte);
            m_model_listeDettes->setStringList(dettes);
            ui->listeDettes->setModel(m_model_listeDettes);
        }
    }
}

