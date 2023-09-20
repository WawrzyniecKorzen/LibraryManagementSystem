#include "adduserdialog.h"
#include "ui_adduserdialog.h"

AddUserDialog::AddUserDialog(QWidget *parent, DatabaseManager& database) :
    QDialog(parent),
    ui(new Ui::AddUserDialog), mDatabase(database)
{
    ui->setupUi(this);
    ui->memberRadioButton->setChecked(true);

    QObject::connect(ui->clearButton, &QPushButton::clicked, this, &AddUserDialog::onClear);
    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &AddUserDialog::onCancel);
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

}
