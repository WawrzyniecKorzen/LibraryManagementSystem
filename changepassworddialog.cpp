#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"

#include <QMessageBox>

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent, User* us) :
    QDialog(parent),
    ui(new Ui::ChangePasswordDialog),
    mDb(DatabaseManager::instance()),
    user(us)
{
    ui->setupUi(this);
    ui->oldEdit->setEchoMode(QLineEdit::Password);
    ui->changeButton->setDefault(true);


    connect(ui->changeButton, &QPushButton::clicked, this, &ChangePasswordDialog::onChangeButton);
    connect(ui->clearButton, &QPushButton::clicked, this, &ChangePasswordDialog::onClearButton);
    connect(ui->cancelButton, &QPushButton::clicked, this, &ChangePasswordDialog::onCancelButton);
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::onChangeButton()
{
    if((ui->oldEdit->text().isEmpty()) || (ui->newEdit->text().isEmpty()) || (ui->repeatEdit->text().isEmpty()))
    {
        int ret = QMessageBox::warning(this, "Change password error", "Cannot change password - one of edits is empty!", QMessageBox::Ok);
    }
    else
    {
        if (!(mDb.loginDao.checkPassword(user->getId(), ui->oldEdit->text())))
        {
            int ret = QMessageBox::warning(this, "Change password error","Wrong password, try again!", QMessageBox::Ok);
            onClearButton();
        }
        else
        {
            if (ui->newEdit->text() == ui->repeatEdit->text())
            {
                mDb.loginDao.changePassword(user->getId(),ui->newEdit->text());
                this->close();
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
}
