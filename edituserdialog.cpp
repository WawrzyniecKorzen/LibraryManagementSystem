#include "edituserdialog.h"
#include "ui_edituserdialog.h"

#include "changepassworddialog.h"
#include "changelogindialog.h"

EditUserDialog::EditUserDialog(QWidget *parent, DatabaseManager& database, User* user, User* admin) :
    QDialog(parent),
    ui(new Ui::EditUserDialog), mDatabase(database), mUser(user), mAdmin(admin)
{
    ui->setupUi(this);
    ui->userName->setText(mUser->getName());
    this->setWindowTitle("Edit user account");

    QObject::connect(ui->changeLoginButton, &QPushButton::clicked, this, &EditUserDialog::onChangeLogin);
    QObject::connect(ui->changePasswordButton, &QPushButton::clicked, this, &EditUserDialog::onChangePassowrd);
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

void EditUserDialog::onChangeLogin()
{
    ChangeLoginDialog* login = new ChangeLoginDialog(this, mDatabase, mUser);
    login->show();
}

void EditUserDialog::onChangePassowrd()
{
    ChangePasswordDialog* pass = new ChangePasswordDialog(this, mUser, mAdmin);
    pass->setAdminMode();
    pass->show();
}
