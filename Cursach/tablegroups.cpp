#include "tablegroups.h"
#include "ui_tablegroups.h"
#include <QDebug>

tableGroups::tableGroups(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableGroups)
{
    ui->setupUi(this);
}

tableGroups::~tableGroups()
{
    delete ui;
}

void tableGroups::on_update_clicked()
{
    groups_model = new QSqlQueryModel();
    groups_model->setQuery("SELECT GroupName FROM Groups");

    groups_model->setHeaderData(0,Qt::Horizontal,"Название группы");

    ui->tableView->setModel(groups_model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();

}

void tableGroups::on_Change_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("UPDATE Groups SET GroupName=:GroupName_new where GroupName=:GroupName");


    query->bindValue(":GroupName_new",ui->lineEdit->text());
    query->bindValue(":GroupName",prim_key);


    query->exec();
    on_update_clicked();


}

void tableGroups::on_Delete_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("DELETE FROM Groups WHERE GroupName=:GroupName");
    query->bindValue(":GroupName",ui->lineEdit->text());
    query->exec();
    on_update_clicked();
}

void tableGroups::on_Add_clicked()
{
    QSqlQuery* query=new QSqlQuery();
     query->prepare("INSERT INTO Groups (GroupName) VALUES (:GroupName)");
     query->bindValue(":GroupName",ui->lineEdit->text());

     QMessageBox*mes=new QMessageBox();
      if (query->exec()){
      mes->setText(" Запись добавлена. ");
      mes->show();}
      else {mes->setText(" Ошибка при добавлении. ");
      mes->show();};
      on_update_clicked();
}

void tableGroups::on_tableView_clicked(const QModelIndex &index)
{


    prim_key=ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();

    qDebug()<<prim_key;
    ui->lineEdit->setText(prim_key);
    QSqlQuery* query=new QSqlQuery();

    query->prepare("SELECT GroupName FROM Groups WHERE GroupName=:GroupName");
    query->bindValue(":GroupName", prim_key);


}
