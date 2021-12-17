#include "accueilutilisateur.h"
#include "ui_accueilutilisateur.h"

/** @brief Classe AccueilUtilisateur
 **
 ** classe de la fenetre AccueilUtilisateur
 **
 ** @version 2.4
 **
 ** @author Thibault Odor, Marie-Luc Moselle, Emilia Goeury-Mayo
 **/

///@brief Constructeur
///
///@param parent : fenetre parent de la fenetre AccueilUtilisateur
AccueilUtilisateur::AccueilUtilisateur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AccueilUtilisateur)
{
    ui->setupUi(this);

}

///@brief Destructeur
AccueilUtilisateur::~AccueilUtilisateur()
{
    delete ui;
}

///@brief Permet de definir le modele dans AccueilUtilisateur
///
/// @param GestionnaireDialogue * g : Pointeur du modele
void AccueilUtilisateur::attachGestionnaireDialogue(GestionnaireDialogue * g)
{
    m_gestionnaireDialogue=*g;
}

///@brief Identifie l'utilisateur pour l'affichage graphique de AccueilUtilisateur
///
/// @param QMap contenant la liste des compte identifié
void AccueilUtilisateur::identifierUtilisateur(QMap <QString, QString> q)
{
    m_utilisateur=q;

    //prenom nom utilisateur
    QString prenom;

    for(const auto &e : m_utilisateur.toStdMap()){prenom.append(e.first);}

    ui->NomPrenom->setText("Bonjour, "+prenom);
    //ui->Nom->setText(nomprenom.takeAt(0));

    //liste compte
    m_modelCompte = new QStringListModel(this);
    QMap<int, QString> compte = m_gestionnaireDialogue.getListeCompte();
    QStringList cmp;

    for(const auto &e : compte.toStdMap()){
        //qDebug() << e.first << "," << e.second << '\n';
        cmp.append(QString::fromStdString(std::to_string(e.first))+"."+e.second);
    }

    //liste cagnotte
    m_modelCagnotte = new QStringListModel(this);

    QMap<int, QString> cagnotte = m_gestionnaireDialogue.getListeCagnotte();
    QStringList cag;

    for(const auto &e : cagnotte.toStdMap()){
        //qDebug() << e.first << "," << e.second << '\n';
        cag.append(QString::fromStdString(std::to_string(e.first))+"."+e.second);
    }

    //ajout liste compte//cagnotte
    if(!cmp.isEmpty()){
        m_modelCompte->setStringList(cmp);
        ui->listCompte->setModel(m_modelCompte);
    }
    if(!cag.isEmpty()){
        m_modelCagnotte->setStringList(cag);
        ui->listCagnotte->setModel(m_modelCagnotte);
    }
}

///@brief Slot s'activant lorsque la liste de compte est cliquée
///
/// @param QModelIndex index de l'element cliqué
void AccueilUtilisateur::on_listCompte_clicked(const QModelIndex &index){
    compteAff* c = new compteAff(this);
    QString stc = index.data(Qt::DisplayRole).toString();
    int result = stc.split(".")[0].toInt();
    c->attachGestionnaireDialogue(&m_gestionnaireDialogue,result);
    c->show();
    this->hide();
}

///@brief Slot s'activant lorsque la liste de cagnotte est cliquée
///
/// @param QModelIndex index de l'element cliqué
void AccueilUtilisateur::on_listCagnotte_clicked(const QModelIndex &index){
    cagnotteAff* c = new cagnotteAff(this);
    QString stc = index.data(Qt::DisplayRole).toString();
    int result = stc.split(".")[0].toInt();
    c->attachGestionnaireDialogue(&m_gestionnaireDialogue,result);
    c->show();
    this->hide();
}


void AccueilUtilisateur::on_retour_clicked()
{
    this->close();
    QWidget::parentWidget()->show();
}

