#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GestionnaireDialogue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getLineEditNom();
    QString getLineEditeMail();
    QString getLineEditMdp();
    void attachGestionnaireDialogue(GestionnaireDialogue g);

private slots:
    void on_boutton_Compte_clicked();

private:
    Ui::MainWindow *ui;
    GestionnaireDialogue m_gestionnaireDialogue;
};
#endif // MAINWINDOW_H
