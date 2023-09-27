#include "editbookdialog.h"
#include "ui_editbookdialog.h"

EditBookDialog::EditBookDialog(QWidget *parent, DatabaseManager& database, Book* book, User* admin) :
    QDialog(parent),
    ui(new Ui::EditBookDialog), mDatabase(database), mBook(book), mAdmin(admin)
{
    ui->setupUi(this);
    ui->bookTitleLabel->setText(mBook->getTitle());
    ui->authorListLabel->setText(mBook->printAuthor());
    ui->yearLabel->setText(QString::number(mBook->getPublicationYear()));
    ui->copiesLabel->setText(QString::number(mBook->getCopies()));

    this->setWindowTitle("Edit book data");

    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &EditBookDialog::onCancel);
}

EditBookDialog::~EditBookDialog()
{
    delete ui;
}

void EditBookDialog::onCancel()
{
    this->close();
    this->deleteLater();
}
