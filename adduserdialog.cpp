#include "adduserdialog.h"
#include "ui_adduserdialog.h"

AddUserDialog::AddUserDialog(QWidget *parent, DatabaseManager& database) :
    QDialog(parent),
    ui(new Ui::AddUserDialog), mDatabase(database)
{
    ui->setupUi(this);
    ui->memberRadioButton->setChecked(true);

    this->setModal(true);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}
