#include "editbookdialog.h"
#include "ui_editbookdialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <algorithm>

#include "addauthordialog.h"

EditBookDialog::EditBookDialog(QWidget *parent, DatabaseManager& database, Book* book, User* admin) :
    QDialog(parent),
    ui(new Ui::EditBookDialog), mDatabase(database), mBook(book), mAdmin(admin)
{
    ui->setupUi(this);
    ui->bookTitleLabel->setText(mBook->getTitle());
    mAuthors = new std::vector<Person>();
    initializeAuthors();
    setAuthors();
    ui->yearLabel->setText(QString::number(mBook->getPublicationYear()));
    ui->copiesLabel->setText(QString::number(mBook->getCopies()));

    this->setWindowTitle("Edit book data");

    QObject::connect(ui->changeTitleButton, &QPushButton::clicked, this, &EditBookDialog::onNewTitle);
    QObject::connect(ui->changeYearButton, &QPushButton::clicked, this, &EditBookDialog::onNewPublicationYear);
    QObject::connect(ui->changeCopiesButton, &QPushButton::clicked, this, &EditBookDialog::onNumberOfCopies);
    QObject::connect(ui->addAuthorButton, &QPushButton::clicked, this, &EditBookDialog::onAddAuthor);
    QObject::connect(ui->changeAuthorsButton, &QPushButton::clicked, this, &EditBookDialog::onChangeAuthor);
    QObject::connect(ui->removeAuthorButton, &QPushButton::clicked, this, &EditBookDialog::onRemoveAuthor);

    QObject::connect(ui->saveButton, &QPushButton::clicked, this, &EditBookDialog::onSave);
    QObject::connect(ui->clearButton, &QPushButton::clicked, this, &EditBookDialog::onClearChanges);
    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &EditBookDialog::onCancel);

    for (Person& person : *mAuthors)
        qDebug() << person.getFullName() << "\n";
}

EditBookDialog::~EditBookDialog()
{
    delete ui;
    delete mAuthors;
}

void EditBookDialog::initializeAuthors()
{
    std::vector<Person> authors = mBook->getAuthors();
    for (Person& author : authors)
    {
        mAuthors->push_back(author);
    }
}

void EditBookDialog::setAuthors()
{

    ui->authorsList->clear();

    for (Person& author : (*mAuthors))
    {
        QListWidgetItem* item = new QListWidgetItem(author.getFullName());
        ui->authorsList->addItem(item);
        itemNameMap.insert(item, author);

    }
}

void EditBookDialog::onNewTitle()
{
    if (ui->newTitleEdit->text().isEmpty())
        return;
    QString message = "Do you want to change book title from " + mBook->getTitle() + " to " + ui->newTitleEdit->text() + "?";
    int result = QMessageBox::question(this, "Confirm new title", message, QMessageBox::Ok | QMessageBox::Abort);

    if (result == QMessageBox::Ok)
    {

        ui->bookTitleLabel->setText(ui->newTitleEdit->text());
        ui->newTitleEdit->clear();
        ui->bookTitleLabel->setStyleSheet("QLabel { color : red; }");
    }
}

void EditBookDialog::onChangeAuthor()
{
    for (Person& person : *mAuthors)
        qDebug() << person.getFullName() << "\n";
}

void EditBookDialog::onAddAuthor()
{
    AddAuthorDialog* addDialog = new AddAuthorDialog(this, mDatabase, mAuthors);
    addDialog->show();
}

void EditBookDialog::onRemoveAuthor()
{
    Person author = itemNameMap.value(ui->authorsList->currentItem());
    int result = QMessageBox::warning(this, "Delete author", "Are you sure you want to delete author " + author.getFullName() + "?",
                                      QMessageBox::Ok | QMessageBox::Abort);
    if (result == QMessageBox::Ok)
    {
        auto it = std::remove_if(mAuthors->begin(), mAuthors->end(), [author](Person& person){return author.isEqual(person);});
        mAuthors->erase(it, mAuthors->end());
        setAuthors();
    }
}

void EditBookDialog::onNewPublicationYear()
{

    if (ui->newPublicationEdit->text().isEmpty())
        return;
    QString message = "Do you want to change publication year from " + QString::number(mBook->getPublicationYear()) + " to "
                      + ui->newPublicationEdit->text() + "?";
    int result = QMessageBox::question(this, "Confirm new publication year", message, QMessageBox::Ok | QMessageBox::Abort);

    if (result == QMessageBox::Ok)
    {

        ui->yearLabel->setText(ui->newPublicationEdit->text());
        ui->newPublicationEdit->clear();
        ui->yearLabel->setStyleSheet("QLabel { color : red; }");
    }
}

void EditBookDialog::onNumberOfCopies()
{
    if (ui->newCopiesEdit->text().isEmpty())
        return;

    if (ui->newCopiesEdit->text().toInt() <0)
    {
        QMessageBox::warning(this, "Number of copies error", "The input is lesser than 0.");
        ui->newCopiesEdit->clear();
        return;
    }

    QString message = "Do you want to change publication year from " + QString::number(mBook->getCopies()) + " to "
                      + ui->newCopiesEdit->text() + "?";
    int result = QMessageBox::question(this, "Confirm new number of copies", message, QMessageBox::Ok | QMessageBox::Abort);

    if (result == QMessageBox::Ok)
    {

        ui->copiesLabel->setText(ui->newCopiesEdit->text());
        ui->newCopiesEdit->clear();
        ui->copiesLabel->setStyleSheet("QLabel { color : red; }");
    }
}

void EditBookDialog::onSave()
{
    int result = QMessageBox::question(this, "Confirm save changes", "Do you want to save changes (in red)?", QMessageBox::Ok | QMessageBox::Abort);

    if (result == QMessageBox::Abort)
        return;

    Book newBook = *mBook;

    if (newBook.getTitle() != ui->bookTitleLabel->text())
        newBook.setTitle(ui->bookTitleLabel->text());

    if (newBook.getPublicationYear() != ui->yearLabel->text().toInt())
        newBook.setPublicationYear(ui->yearLabel->text().toInt());

    if (newBook.getCopies() != ui->copiesLabel->text().toInt())
        newBook.setCopies(ui->copiesLabel->text().toInt());
    newBook.setAuthors(*mAuthors);

    std::vector<Person> authorsToRemove = mBook->compareAuthors(newBook);
    mDatabase.bookDao.updateBookAuthors(mBook->getId(), authorsToRemove);
    mDatabase.bookDao.removeAuthors(authorsToRemove);
    mDatabase.bookDao.changeBookData(newBook);
    onCancel();
}

void EditBookDialog::onClearChanges()
{
    ui->bookTitleLabel->setText(mBook->getTitle());
    ui->bookTitleLabel->setStyleSheet("QLabel { color : black; }");
    ui->authorsList->clear();

    itemNameMap.clear();
    mAuthors->clear();

    initializeAuthors();
    setAuthors();

    ui->yearLabel->setText(QString::number(mBook->getPublicationYear()));
    ui->yearLabel->setStyleSheet("QLabel { color : black; }");

    ui->copiesLabel->setText(QString::number(mBook->getCopies()));
    ui->copiesLabel->setStyleSheet("QLabel { color : black; }");
}

void EditBookDialog::onCancel()
{
    itemNameMap.clear();
    this->close();
    this->deleteLater();
}
