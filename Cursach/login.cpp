#include "login.h"
#include "ui_login.h"


login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    message = new QMessageBox();
}


login::~login()
{
    delete ui;
}

void login::on_DB_Connected_clicked()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER=ACADEMY;DATABASE=Cursach;");
    db.setUserName(ui->lineEdit->text());
    db.setPassword(ui->lineEdit_2->text());
    if(db.open())
    {
        message->setText("Соединение успешно");
    }
    else
    {
        message->setText("Соединение не установлено");
    }
    message->show();
}

