#ifndef TABLESTUDENTS_H
#define TABLESTUDENTS_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql>

namespace Ui {
class tableStudents;
}

class tableStudents : public QWidget
{
    Q_OBJECT

public:
    explicit tableStudents(QWidget *parent = nullptr);
    ~tableStudents();
    int combo_strotr, combo_group;

private slots:
    void on_update_clicked();

    void on_Add_clicked();

    void on_Delete_clicked();

    void on_Change_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboGroup_currentIndexChanged(int index);

    void on_comboStrOtr_currentIndexChanged(int index);

private:
    Ui::tableStudents *ui;
    QSqlQueryModel *stud_model;
};

#endif // TABLESTUDENTS_H
