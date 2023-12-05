#include "addbookdialog.h"
#include "ui_addbookdialog.h"

#include <QMessageBox>
#include <QIntValidator>

AddBookDialog::AddBookDialog(QWidget *parent, DatabaseManager& database) :
    QDialog(parent),
    ui(new Ui::AddBookDialog), mDatabase(database)
{
    ui->setupUi(this);

    this->setWindowTitle("Add book");
    setAuthorList();
    ui->publicationEdit->setValidator(new QIntValidator(1000, 2000, this));


    QObject::connect(ui->addAuthorButton, &QPushButton::clicked, this, &AddBookDialog::onAddAuthor);
    QObject::connect(ui->addBookButton, &QPushButton::clicked, this, &AddBookDialog::onAddBook);
    QObject::connect(ui->clearButton, &QPushButton::clicked, this, &AddBookDialog::onClear);
    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &AddBookDialog::onCancel);
}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}

void AddBookDialog::setAuthorList()
{
    QString authors;
    for (Person person : authorList)
    {
        if (authors.size() != 0)
            authors += ", ";
        authors += person.getFullName();
    }
    ui->authorsListLabel->setText(authors);
}

bool AddBookDialog::isInputEmpty()
{
    return (ui->titleEdit->text().isEmpty() || authorList.size() == 0 || ui->publicationEdit->text().isEmpty() || ui->copiesEdit->text().isEmpty());
}

void AddBookDialog::onAddAuthor()
{
    if (ui->firstNameEdit->text().isEmpty() || ui->LastNameEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Author name error", "To add an author you have to fill first name and last name");
        return;
    }

    Person author;
    author.setFirstName(ui->firstNameEdit->text());
    author.setLastName(ui->LastNameEdit->text());
    authorList.push_back(author);
    qDebug() << author.getFullName();

    ui->firstNameEdit->clear();
    ui->LastNameEdit->clear();
    setAuthorList();
}

void AddBookDialog::onAddBook()
{
    if (authorList.size() == 0)
    {
        onAddAuthor();
    }

    if (isInputEmpty())
    {
        QMessageBox::warning(this, "Input error", "One of the inputs is empty", QMessageBox::Ok);
        return;
    }

    //check if the publication and copies are numbers, maybe restrict it in edits?

    Book book;
    book.setTitle(ui->titleEdit->text());

    for (Person& author : authorList)
        book.setAuthor(author);
    book.setPublicationYear(ui->publicationEdit->text().toInt());
    book.setAvailable(ui->copiesEdit->text().toInt());
    book.setCopies(ui->copiesEdit->text().toInt());
    mDatabase.bookDao.addBook(book);
    onCancel();
}

void AddBookDialog::onClear()
{
    ui->titleEdit->clear();
    ui->firstNameEdit->clear();
    ui->LastNameEdit->clear();
    authorList.clear();
    ui->publicationEdit->clear();
    ui->copiesEdit->clear();
}

void AddBookDialog::onCancel()
{
    this->close();
    this->deleteLater();
}
