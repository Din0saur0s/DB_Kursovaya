#include "tablesmeny.h"
#include "ui_tablesmeny.h"
//#include <QString>

tableSmeny::tableSmeny(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableSmeny)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
}

tableSmeny::~tableSmeny()
{
    delete ui;
}

void tableSmeny::on_update_clicked()
{
    smeny_model = new QSqlQueryModel();
    smeny_model->setQuery("SELECT * FROM Smeny");

    smeny_model->setHeaderData(0,Qt::Horizontal,"Номер смены");
    smeny_model->setHeaderData(1,Qt::Horizontal,"Дата начала");
    smeny_model->setHeaderData(2,Qt::Horizontal,"Дата окончания");

    ui->tableView->setModel(smeny_model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void tableSmeny::on_Change_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("UPDATE Smeny SET DataStart=:DataStart, DataEnd=:DataEnd WHERE :DataStart=DataStart");


    query->bindValue(":DataStart",ui->dateEdit->text());
    query->bindValue(":DataEnd",ui->dateEdit_2->text());

    query->exec();
    on_update_clicked();

}

void tableSmeny::on_Delete_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("DELETE FROM Smeny WHERE DataStart=:DataStart");
    query->bindValue(":DataStart",ui->dateEdit->text());

    query->exec();
    on_update_clicked();
}

void tableSmeny::on_Add_clicked()
{
   QSqlQuery* query=new QSqlQuery();
    query->prepare("INSERT INTO Smeny (DataStart,DataEnd) VALUES ( :DataStart, :DataEnd)");
    query->bindValue(":DataStart",ui->dateEdit->text());
    query->bindValue(":DataEnd",ui->dateEdit_2->text());




     QMessageBox*mes=new QMessageBox();
      if (query->exec()){
      mes->setText(" Запись добавлена. ");
      mes->show();}
      else {mes->setText(" Ошибка при добавлении. ");
      mes->show();};
      on_update_clicked();
}

void tableSmeny::on_tableView_clicked(const QModelIndex &index)
{
    int prim_key;
    prim_key=ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();

    ui->ID_Smeny->setText(QString::number(prim_key));

    QSqlQuery* query=new QSqlQuery();
    query->prepare("SELECT * FROM Smeny WHERE Smeny_id=:Smeny_id");
    query->bindValue(":Smeny_id",prim_key);

    if (query->exec()){
    query->next();
    ui->dateEdit->setDate(QDate(query->value(1).toDate()));
    ui->dateEdit_2->setDate(QDate(query->value(2).toDate()));
    }
}
