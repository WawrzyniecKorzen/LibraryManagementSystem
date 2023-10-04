#include "addauthordialog.h"
#include "ui_addauthordialog.h"

#include <QMessageBox>

#include "editbookdialog.h"


AddAuthorDialog::AddAuthorDialog(QWidget *parent, DatabaseManager& database, std::vector<Person> *authors) :
    QDialog(parent),
    ui(new Ui::AddAuthorDialog), mDatabase(database), mAuthors(authors)
{
    ui->setupUi(this);

    QObject::connect(ui->addButton, &QPushButton::clicked, this, &AddAuthorDialog::onAdd);
    QObject::connect(ui->clearButton, &QPushButton::clicked, this, &AddAuthorDialog::onClear);
    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &AddAuthorDialog::onCancel);
}



AddAuthorDialog::~AddAuthorDialog()
{
    delete ui;
    delete mAuthor;
}

void AddAuthorDialog::onAdd()
{
    if (ui->firstNameEdit->text().isEmpty() || ui->lastNamEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Empty input", "One of input lines is empty! Fill it to add a new Author.", QMessageBox::Ok);
        return;
    }

    mAuthor = new Person(ui->firstNameEdit->text(), ui->lastNamEdit->text());
    bool repetition = false;

    for (Person& author : (*mAuthors))
    {
        repetition = mAuthor->isEqual(author);

        if (repetition)
        {
            break;
        }
    }
    if (repetition)
    {
        QMessageBox::warning(this, "Wrong input", "The Author provided already exists and is listed as one of the Authors of this book!", QMessageBox::Ok);
        onClear();
    }
    else
    {
        mAuthors->push_back(*mAuthor);
    }
    onCancel();


}

void AddAuthorDialog::onClear()
{
    ui->firstNameEdit->clear();
    ui->lastNamEdit->clear();
}

void AddAuthorDialog::onCancel()
{
    EditBookDialog* edit = qobject_cast<EditBookDialog*>(this->parent());
    edit->setAuthors();
    this->close();
}
