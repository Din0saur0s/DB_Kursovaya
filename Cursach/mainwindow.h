#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <login.h>
#include <ui_login.h>

#include <tablestudents.h>
#include <ui_tablestudents.h>

#include "tablesmeny.h"
#include "ui_tablesmeny.h"

#include "tablestrotryady.h"
#include "ui_tablestrotryady.h"

#include "tableworks.h"
#include "ui_tableworks.h"

#include "tablegroups.h"
#include "ui_tablegroups.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    login* logwin;
    tableStudents* studwin;
    tableSmeny* smenywin;
    tableStrOtryady* strotrwin;
    tableWorks* workwin;
    tableGroups* groupwin;

private slots:
    void on_BDconnect_triggered();

    void on_tableStudents_clicked();

    void on_tableSmeny_clicked();

    void on_tableStrOtr_clicked();

    void on_tableGroups_clicked();

    void on_tableWorks_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
