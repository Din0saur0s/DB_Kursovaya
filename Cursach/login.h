#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
//#include <QSqlTableModel>
//#include <QSqlQueryModel>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    QMessageBox* message;

private slots:
    void on_DB_Connected_clicked();

private:
    Ui::login *ui;
    QSqlDatabase db;

};

#endif // LOGIN_H
