#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_BDconnect_triggered()
{
   logwin = new login();
   logwin->show();
}

void MainWindow::on_tableStudents_clicked()
{
    studwin = new tableStudents();
    studwin->show();
}

void MainWindow::on_tableSmeny_clicked()
{
    smenywin = new tableSmeny();
    smenywin->show();
}

void MainWindow::on_tableStrOtr_clicked()
{
    strotrwin = new tableStrOtryady();
    strotrwin->show();
}

void MainWindow::on_tableGroups_clicked()
{
    groupwin = new tableGroups();
    groupwin->show();
}

void MainWindow::on_tableWorks_clicked()
{
    workwin = new tableWorks();
    workwin->show();
}
