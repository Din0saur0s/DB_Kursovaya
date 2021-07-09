#include "tablestrotryady.h"
#include "ui_tablestrotryady.h"
#include <QString>

tableStrOtryady::tableStrOtryady(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableStrOtryady)
{
    ui->setupUi(this);
    QSqlQuery* query = new QSqlQuery();
    QSqlQuery* query2 = new QSqlQuery();
    query->exec("SELECT LocationName FROM StrOtryady");
    while (query->next())
    {
        ui->comboBox_2->addItem(query->value(0).toString());
    }
    query2->exec("SELECT Smeny_id FROM Smeny");
    while (query2->next())
    {
        ui->comboBox_3->addItem(query2->value(0).toString());
    }
    location=0;
    smena=0;
}

tableStrOtryady::~tableStrOtryady()
{
    delete ui;
}

void tableStrOtryady::on_update_clicked()
{
    strotr_model = new QSqlQueryModel();
    strotr_model->setQuery("SELECT StrOtrName,LocationName, StrOtryad_Smena FROM StrOtryady");

    strotr_model->setHeaderData(0,Qt::Horizontal,"Название строй.отряда");
    strotr_model->setHeaderData(1,Qt::Horizontal,"Местоположение");
    strotr_model->setHeaderData(2,Qt::Horizontal,"Смена");
   // strotr_model->setHeaderData(3,Qt::Horizontal,"Отчество");

    ui->tableView->setModel(strotr_model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void tableStrOtryady::on_Change_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("UPDATE StrOtryady SET LocationName=:LocationName, StrOtryad_Smena=:StrOtryad_Smena WHERE StrOtrName=:StrOtrName");
    query->bindValue(":StrOtrName",ui->lineEdit->text());
    query->bindValue(":LocationName",ui->comboBox_2->itemText(location));
    query->bindValue(":StrOtryad_Smena",ui->comboBox_3->itemText(smena));

   // query->bindValue(":StrOtrName",ui->lineEdit->text());
   // ui->comboBox_2->addItem(query->value(0).toString());
   // ui->comboBox_3->addItem(query->value(0).toString());
    query->exec();
    on_update_clicked();

}

void tableStrOtryady::on_Delete_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("DELETE FROM StrOtryady WHERE StrOtrName=:StrOtrName");
    query->bindValue(":StrOtrName", ui->lineEdit->text());
    query->exec();
    on_update_clicked();
}

void tableStrOtryady::on_Add_clicked()
{
    QString loc,so;

    QSqlQuery* query=new QSqlQuery();
     query->prepare("INSERT INTO StrOtryady(StrOtrName, LocationName, StrOtryad_Smena) VALUES (:StrOtrName, :LocationName, :StrOtryad_Smena)");
     query->bindValue(":StrOtrName",ui->lineEdit->text());
     query->bindValue(":LocationName",ui->comboBox_2->itemText(location));
     query->bindValue(":StrOtryad_Smena",ui->comboBox_3->itemText(smena));

     QMessageBox*mes=new QMessageBox();
      if (query->exec()){
      mes->setText(" Запись добавлена. ");
      mes->show();}
      else {mes->setText(" Ошибка при добавлении. ");
      mes->show();};
      on_update_clicked();
}

void tableStrOtryady::on_tableView_clicked(const QModelIndex &index)
{
    QString prim_key;
    prim_key=ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();

    ui->lineEdit->setText(prim_key);

    QSqlQuery* query=new QSqlQuery();
    query->prepare("SELECT StrOtrName, LocationName, StrOtryad_Smena FROM StrOtryady WHERE StrOtrName=:StrOtrName");
    query->bindValue(":StrOtrName",prim_key);


}

void tableStrOtryady::on_comboBox_2_currentIndexChanged(int index)
{
    location=index;
}

void tableStrOtryady::on_comboBox_3_currentIndexChanged(int index)
{
    smena=index;
}
