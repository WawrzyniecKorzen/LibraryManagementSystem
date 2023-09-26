#include "changelogindialog.h"
#include "ui_changelogindialog.h"

#include <QMessageBox>

ChangeLoginDialog::ChangeLoginDialog(QWidget *parent, DatabaseManager& database, User* user) :
    QDialog(parent),
    ui(new Ui::ChangeLoginDialog), mDatabase(database), mUser(user)
{
    ui->setupUi(this);
    this->setWindowTitle("Change login");
    ui->loginLabel->setText(user->getName());

    QObject::connect(ui->changeButton, &QPushButton::clicked, this, &ChangeLoginDialog::onChange);
    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &ChangeLoginDialog::onCancel);
}

ChangeLoginDialog::~ChangeLoginDialog()
{
    delete ui;
}

void ChangeLoginDialog::onChange()
{
    if (ui->newEdit->text().isEmpty() || ui->repeatEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Empty input line", "One or more input lines are empty. Please fill the missing input", QMessageBox::Ok);
        return;
    }

    if (!mDatabase.userDao.checkNameLength(ui->newEdit->text()))
    {
        QString message = "New username too short or too long (it should be at least " + QString::number(USERNAME_MIN) +
                          " and maximally " + QString::number(USERNAME_MAX) + " characters).";

        QMessageBox::warning(this, "Name length error", message, QMessageBox::Ok);
    }
    if(mDatabase.userDao.findUserName(ui->newEdit->text()))
    {
        QMessageBox::warning(this, "User name error", "This user name is already used. Try another one!", QMessageBox::Ok);
        ui->newEdit->clear();
        ui->repeatEdit->clear();
        return;
    }

    if(ui->newEdit->text() != ui->repeatEdit->text())
    {
        QMessageBox::warning(this, "Name error", "Name and repeated name do not match. Try again!", QMessageBox::Ok);
        ui->newEdit->clear();
        ui->repeatEdit->clear();
        return;
    }

    mDatabase.userDao.changeUserName(mUser->getId(), ui->newEdit->text());

    onCancel();
}

void ChangeLoginDialog::onCancel()
{
    this->close();
    this->deleteLater();
}
