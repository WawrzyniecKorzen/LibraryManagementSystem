#include "adduserdialog.h"
#include "ui_adduserdialog.h"

#include <QRandomGenerator>

static char characters[36] = "abcdefghijklmnoprqstuwxyz0123456789";

AddUserDialog::AddUserDialog(QWidget *parent, DatabaseManager& database) :
    QDialog(parent),
    ui(new Ui::AddUserDialog), mDatabase(database)
{
    ui->setupUi(this);
    ui->memberRadioButton->setChecked(true);

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
