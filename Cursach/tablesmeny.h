#ifndef TABLESMENY_H
#define TABLESMENY_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql>

namespace Ui {
class tableSmeny;
}

class tableSmeny : public QWidget
{
    Q_OBJECT

public:
    explicit tableSmeny(QWidget *parent = nullptr);
    ~tableSmeny();

private slots:
    void on_update_clicked();

    void on_Change_clicked();

    void on_Delete_clicked();

    void on_Add_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::tableSmeny *ui;
    QSqlQueryModel *smeny_model;
};

#endif // TABLESMENY_H
