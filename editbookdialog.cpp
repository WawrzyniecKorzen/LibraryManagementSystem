#include "editbookdialog.h"
#include "ui_editbookdialog.h"

EditBookDialog::EditBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBookDialog)
{
    ui->setupUi(this);
}

EditBookDialog::~EditBookDialog()
{
    delete ui;
}
