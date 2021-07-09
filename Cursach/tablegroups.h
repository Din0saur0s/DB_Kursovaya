#ifndef TABLEGROUPS_H
#define TABLEGROUPS_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql>


namespace Ui {
class tableGroups;
}

class tableGroups : public QWidget
{
    Q_OBJECT

public:
    explicit tableGroups(QWidget *parent = nullptr);
    ~tableGroups();
    QString prim_key;

private slots:
    void on_update_clicked();

    void on_Change_clicked();

    void on_Delete_clicked();

    void on_Add_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::tableGroups *ui;
    QSqlQueryModel *groups_model;
};

#endif // TABLEGROUPS_H
