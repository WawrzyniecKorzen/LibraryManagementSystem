#include "changeauthordialog.h"
#include "ui_changeauthordialog.h"

#include "editbookdialog.h"

ChangeAuthorDialog::ChangeAuthorDialog(QWidget *parent, Person author) :
    QDialog(parent),
    ui(new Ui::ChangeAuthorDialog), mAuthor(author)
{
    ui->setupUi(this);
    ui->firstNameEdit->setText(mAuthor.getFirstName());
    ui->lastNameEdit->setText(mAuthor.getLastName());

    QObject::connect(ui->saveChangesButton, &QPushButton::clicked, this, &ChangeAuthorDialog::onSaveChanges);
    QObject::connect(ui->clearButton, &QPushButton::clicked, this, &ChangeAuthorDialog::onClear);
    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &ChangeAuthorDialog::onCancel);
}


ChangeAuthorDialog::~ChangeAuthorDialog()
{
    delete ui;
}

void ChangeAuthorDialog::onSaveChanges()
{
    Person newAuthor(ui->firstNameEdit->text(), ui->lastNameEdit->text());
    EditBookDialog* edit = qobject_cast<EditBookDialog*>(this->parent());
    edit->editAuthor(mAuthor, newAuthor);
    edit->setAuthors();
    onCancel();
}

void ChangeAuthorDialog::onClear()
{
    ui->firstNameEdit->setText(mAuthor.getFirstName());
    ui->lastNameEdit->setText(mAuthor.getLastName());
}

void ChangeAuthorDialog::onCancel()
{
    this->close();
    this->deleteLater();
}
