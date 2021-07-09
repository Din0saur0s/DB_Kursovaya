#ifndef TABLESTROTRYADY_H
#define TABLESTROTRYADY_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql>

namespace Ui {
class tableStrOtryady;
}

class tableStrOtryady : public QWidget
{
    Q_OBJECT

public:
    explicit tableStrOtryady(QWidget *parent = nullptr);
    ~tableStrOtryady();
    int location, smena;

private slots:
    void on_update_clicked();

    void on_Change_clicked();

    void on_Delete_clicked();

    void on_Add_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

private:
    Ui::tableStrOtryady *ui;
    QSqlQueryModel* strotr_model;
};

#endif // TABLESTROTRYADY_H
