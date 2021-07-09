#include "tableworks.h"
#include "ui_tableworks.h"
#include <QString>

tableWorks::tableWorks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableWorks)
{
    ui->setupUi(this);
    QSqlQuery* query = new QSqlQuery();
    query->exec("SELECT Smeny_id FROM Smeny");
    while (query->next())
    {
        ui->comboBox_2->addItem(query->value(0).toString());
    }
    combo_id=0;

}

tableWorks::~tableWorks()
{
    delete ui;
}

void tableWorks::on_tableView_clicked(const QModelIndex &index)
{
    QString prim_key;
    prim_key=ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    ui->lineEdit->setText(prim_key);

    QSqlQuery* query=new QSqlQuery();
    query->prepare("SELECT WorkName,Pay, Work_Smena FROM Works WHERE WorkName=:WorkName");
    query->bindValue(":WorkName",prim_key);

}

void tableWorks::on_update_clicked()
{
    work_model = new QSqlQueryModel();
    work_model->setQuery("SELECT WorkName,Pay,Work_Smena FROM Works");

    work_model->setHeaderData(0,Qt::Horizontal,"Название работы");
    work_model->setHeaderData(1,Qt::Horizontal,"Оплата");
    work_model->setHeaderData(2,Qt::Horizontal,"Номер смены");

    ui->tableView->setModel(work_model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();

}

void tableWorks::on_Change_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("UPDATE Works SET Pay=:Pay, Work_Smena=:Smeny_id WHERE WorkName=:WorkName");
    query->bindValue(":Pay",ui->lineEdit_2->text());
    query->bindValue(":WorkName",ui->lineEdit->text());
    query->bindValue(":Smeny_id",ui->comboBox_2->itemText(combo_id));


    query->exec();
    on_update_clicked();
}

void tableWorks::on_Delete_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("DELETE FROM Works WHERE WorkName=:WorkName");
    query->bindValue(":WorkName",ui->lineEdit->text());

    query->exec();
    on_update_clicked();
}

void tableWorks::on_Add_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("INSERT INTO Works (WorkName,Pay,Work_Smena) VALUES (:WorkName, :Pay, :Smeny_id)");
    query->bindValue(":WorkName",ui->lineEdit->text());
    query->bindValue(":Pay",ui->lineEdit_2->text());
    query->bindValue(":Smeny_id",ui->comboBox_2->itemText(combo_id));

    query->exec();
    on_update_clicked();
}

void tableWorks::on_comboBox_2_currentIndexChanged(int index)
{
    combo_id=index;
}
