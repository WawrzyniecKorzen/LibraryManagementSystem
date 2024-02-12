#include "userloansdialog.h"
#include "ui_userloansdialog.h"

UserLoansDialog::UserLoansDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLoansDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->closeButton, &QPushButton::clicked, this, &UserLoansDialog::onCloseButton);
}

UserLoansDialog::~UserLoansDialog()
{
    delete ui;
}

void UserLoansDialog::onCloseButton()
{
    this->close();
}
