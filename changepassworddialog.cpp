#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"

#include <QMessageBox>
#include <QDebug>

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent, User* user, User* logged) :
    QDialog(parent),
    ui(new Ui::ChangePasswordDialog),
    mDatabase(DatabaseManager::instance()),
    mUser(user), mLoggedUser(logged)
{
    ui->setupUi(this);
    this->setWindowTitle("Change password");
    ui->oldEdit->setEchoMode(QLineEdit::Password);
    ui->changeButton->setDefault(true);


    connect(ui->changeButton, &QPushButton::clicked, this, &ChangePasswordDialog::onChangeButton);
    connect(ui->clearButton, &QPushButton::clicked, this, &ChangePasswordDialog::onClearButton);
    connect(ui->cancelButton, &QPushButton::clicked, this, &ChangePasswordDialog::onCancelButton);
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
    qDebug() << "change password dialog deleted";
}

void ChangePasswordDialog::onChangeButton()
{
    if((ui->oldEdit->text().isEmpty()) || (ui->newEdit->text().isEmpty()) || (ui->repeatEdit->text().isEmpty()))
    {
        QMessageBox::warning(this, "Change password error", "Cannot change password - one of edits is empty!", QMessageBox::Ok);
    }
    else
    {
        if (!(mDatabase.loginDao.checkPassword(mLoggedUser->getId(), ui->oldEdit->text())))
        {
            QMessageBox::warning(this, "Change password error","Wrong password, try again!", QMessageBox::Ok);
            onClearButton();
        }
        else
        {
            if (ui->newEdit->text() == ui->repeatEdit->text())
            {
                mDatabase.loginDao.changePassword(mUser->getId(),ui->newEdit->text());
                this->close();
                this->deleteLater();
            }
            else
            {
                QMessageBox::warning(this, "Change password error", "New passwords do not match, try again!", QMessageBox::Ok);
                onClearButton();
            }
        }
    }

}

void ChangePasswordDialog::onClearButton()
{
    ui->oldEdit->clear();
    ui->newEdit->clear();
    ui->repeatEdit->clear();
}

void ChangePasswordDialog::onCancelButton()
{
    this->close();
    this->deleteLater();
}

void ChangePasswordDialog::setAdminMode()
{
    ui->oldPassLabel->setText("Admin password: ");
}
