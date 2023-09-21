#include "adduserdialog.h"
#include "ui_adduserdialog.h"

#include <QRandomGenerator>
#include <QMessageBox>
#include <QDebug>

static char characters[36] = "abcdefghijklmnoprqstuwxyz0123456789";

AddUserDialog::AddUserDialog(QWidget *parent, DatabaseManager& database) :
    QDialog(parent),
    ui(new Ui::AddUserDialog), mDatabase(database)
{
    ui->setupUi(this);
    ui->memberRadioButton->setChecked(true);

    QObject::connect(ui->addUserButton, &QPushButton::clicked, this, &AddUserDialog::onAddUser);
    QObject::connect(ui->clearButton, &QPushButton::clicked, this, &AddUserDialog::onClear);
    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &AddUserDialog::onCancel);
    QObject::connect(ui->generatButton, &QPushButton::clicked, this, &AddUserDialog::onGenerate);
    this->setModal(true);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::onAddUser()
{
    if(ui->userNameEdit->text().isEmpty() || ui->passwordEdit->text().isEmpty() || ui->repeatEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Empty input line", "One or more input lines are empty. Please fill the missing input", QMessageBox::Ok);
        return;
    }
    //check more problems:
    //too short name
    //too short password

    if(mDatabase.userDao.findUserName(ui->userNameEdit->text()))
    {
        QMessageBox::warning(this, "User name error", "This user name is already used. Try another one!", QMessageBox::Ok);
        ui->userNameEdit->clear();
        return;
    }

    if(ui->passwordEdit->text() != ui->repeatEdit->text())
    {
        QMessageBox::warning(this, "Password error", "Password and repeated passwords do not match. Try again!", QMessageBox::Ok);
        ui->passwordEdit->clear();
        ui->repeatEdit->clear();
        return;
    }

    AccountType status;
    if (ui->memberRadioButton->isChecked())
        status = AccountType::Member;
    else
        status = AccountType::Admin;
    QDate date = QDate::currentDate();
    User* user = new User();
    user->setName(ui->userNameEdit->text());
    user->setJoined(date);
    user->setStatus(status);

    mDatabase.userDao.addUser(user, ui->passwordEdit->text());
    onCancel();

}

void AddUserDialog::onClear()
{
    ui->userNameEdit->clear();
    ui->passwordEdit->clear();
    ui->repeatEdit->clear();
    ui->memberRadioButton->setChecked(true);
}

void AddUserDialog::onCancel()
{
    this->close();
    this->deleteLater();
}

void AddUserDialog::onGenerate()
{
    int length = 8;
    QString password;
    for (int i = 0; i < length; i++)
        password.append(characters[QRandomGenerator::global()->bounded(36)]);
    ui->passwordEdit->setText(password);
}
