#include "edituserdialog.h"
#include "ui_edituserdialog.h"

EditUserDialog::EditUserDialog(QWidget *parent, DatabaseManager& database, User* user) :
    QDialog(parent),
    ui(new Ui::EditUserDialog), mDatabase(database), mUser(user)
{
    ui->setupUi(this);
    ui->userName->setText(mUser->getName());

}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}
