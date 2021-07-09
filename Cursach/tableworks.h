#ifndef TABLEWORKS_H
#define TABLEWORKS_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql>


namespace Ui {
class tableWorks;
}

class tableWorks : public QWidget
{
    Q_OBJECT

public:
    explicit tableWorks(QWidget *parent = nullptr);
    ~tableWorks();
    int combo_id;
private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_update_clicked();

    void on_Change_clicked();

    void on_Delete_clicked();

    void on_Add_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::tableWorks *ui;
    QSqlQueryModel *work_model;
};

#endif // TABLEWORKS_H
