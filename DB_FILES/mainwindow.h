#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QLabel>
#include "gestionnaireBDD.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(gestionnaireBDD db, int id, QWidget *parent = nullptr);
    void on_pushButton_clicked();
    ~MainWindow();

private slots:
    void on_addPart_clicked();

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    QLabel *label;
    gestionnaireBDD db;
    int idCompte;
};
#endif // MAINWINDOW_H
