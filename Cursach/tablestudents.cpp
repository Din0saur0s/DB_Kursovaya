#include "tablestudents.h"
#include "ui_tablestudents.h"
#include <QString>

tableStudents::tableStudents(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableStudents)
{
    ui->setupUi(this);
    QSqlQuery* query = new QSqlQuery();
    QSqlQuery* query2 = new QSqlQuery();
    query->exec("SELECT StrOtrName FROM StrOtryady");
    while (query->next())
    {
        ui->comboStrOtr->addItem(query->value(0).toString());
    }
    query2->exec("SELECT GroupName FROM Groups");
    while (query2->next())
    {
        ui->comboGroup->addItem(query2->value(0).toString());
    }
    combo_group=0;
    combo_strotr=0;

}

tableStudents::~tableStudents()
{
    delete ui;
}

void tableStudents::on_update_clicked()
{
    stud_model = new QSqlQueryModel();
    stud_model->setQuery("SELECT StudBilet,Familia, Imya, Otchestvo FROM Students");

    stud_model->setHeaderData(0,Qt::Horizontal,"Номер студ.билета");
    stud_model->setHeaderData(1,Qt::Horizontal,"Фамилия");
    stud_model->setHeaderData(2,Qt::Horizontal,"Имя");
    stud_model->setHeaderData(3,Qt::Horizontal,"Отчество");

    ui->tableView->setModel(stud_model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void tableStudents::on_Add_clicked()
{
    //QString str;
    //int id=0, id_g=0;
    //  ,*query2,*query3
    QSqlQuery* query =new QSqlQuery();

    query->prepare("INSERT INTO Students (StudBilet, Familia, Imya, Otchestvo) VALUES(:StudBilet, :Familia, :Imya, :Otchestvo)");

  //  query->prepare("INSERT INTO Students (StudBilet, Familia, Imya, Otchestvo,Student_StrOtr,Student_Group) VALUES(:StudBilet, :Familia, :Imya, :Otchestvo, :Student_StrOtr, :Student_Group)");
    query->bindValue(":StudBilet",ui->lineEdit->text());
    query->bindValue(":Familia",ui->lineEdit_2->text());
    query->bindValue(":Imya",ui->lineEdit_3->text());
    query->bindValue(":Otchestvo",ui->lineEdit_4->text());
   /* query2->prepare("SELECT StrOtrName, StrOtr_id FROM StrOtryady where StrOtrName=:StrOtrName");
    query2->bindValue(":StrOtrName",ui->comboStrOtr->itemText(combo_strotr));
    query2->bindValue("StrOtr_id",id);
    query3->prepare("SELECT GroupName, Group_id FROM Groups where GroupName=:GroupName");
    query3->bindValue(":GroupName",ui->comboGroup->itemText(combo_group));
    query2->bindValue("Group_id",id_g);
    query->bindValue(":Student_StrOtr",id);
    query->bindValue(":Student_Group",id_g);
*/



     QMessageBox*mes=new QMessageBox();
      if (query->exec()){
      mes->setText(" Запись добавлена. ");
      mes->show();}
      else {mes->setText(" Ошибка при добавлении. ");
      mes->show();};
      on_update_clicked();
}

void tableStudents::on_Delete_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("DELETE FROM Students WHERE StudBilet=:StudBilet");
    query->bindValue(":StudBilet",ui->lineEdit->text());

    query->exec();
    on_update_clicked();
}

void tableStudents::on_Change_clicked()
{
    QSqlQuery* query=new QSqlQuery();
    query->prepare("UPDATE Students SET Familia=:Familia, Imya=:Imya, Otchestvo=:Otchestvo WHERE StudBilet=:StudBilet");
    query->bindValue(":StudBilet",ui->lineEdit->text());
    query->bindValue(":Familia",ui->lineEdit_2->text());
    query->bindValue(":Imya",ui->lineEdit_3->text());
    query->bindValue(":Otchestvo",ui->lineEdit_4->text());

    query->exec();
    on_update_clicked();
}

void tableStudents::on_tableView_clicked(const QModelIndex &index)
{
    QString prim_key;

    prim_key=ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();

    ui->lineEdit->setText(prim_key);

    QSqlQuery* query=new QSqlQuery();
    query->prepare("SELECT Familia,Imya, Otchestvo FROM Students WHERE StudBilet=:StudBilet");
    query->bindValue(":StudBilet",prim_key);

    if (query->exec()){
    query->next();
    ui->lineEdit_2->setText(query->value(0).toString());
    ui->lineEdit_3->setText(query->value(1).toString());
    ui->lineEdit_4->setText(query->value(2).toString());
    }

    //on_update_clicked();

}

void tableStudents::on_comboGroup_currentIndexChanged(int index)
{
    combo_group=index;
}

void tableStudents::on_comboStrOtr_currentIndexChanged(int index)
{
    combo_strotr=index;
}
