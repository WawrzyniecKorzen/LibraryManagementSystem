#include "login.h"
#include "ui_login.h"

#include "databasemanager.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login),
    mDb(DatabaseManager::instance())
{


    ui->setupUi(this);
    ui->passwordInput->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}



void Login::on_clearButton_clicked()
{
    ui->loginInput->clear();
    ui->passwordInput->clear();
}


void Login::on_singInButton_clicked()
{
    bool result = mDb.loginDao.login(ui->loginInput->text(), ui->passwordInput->text());
    if (result)
    {
        this->close();
        this->setResult(QDialog::Accepted);
    }
    else
    {
        int ret = QMessageBox::warning(this, "Sign in error","Signing in unsuccefful, try again!", QMessageBox::Ok);
        on_clearButton_clicked();
    }
}

