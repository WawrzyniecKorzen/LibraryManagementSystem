#include "editbookdialog.h"
#include "ui_editbookdialog.h"

#include <QDebug>
#include <QMessageBox>

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

    QObject::connect(ui->changeTitleButton, &QPushButton::clicked, this, &EditBookDialog::onNewTitle);
    QObject::connect(ui->changeYearButton, &QPushButton::clicked, this, &EditBookDialog::onNewPublicationYear);
    QObject::connect(ui->changeCopiesButton, &QPushButton::clicked, this, &EditBookDialog::onNumberOfCopies);

    QObject::connect(ui->saveButton, &QPushButton::clicked, this, &EditBookDialog::onSave);
    QObject::connect(ui->clearButton, &QPushButton::clicked, this, &EditBookDialog::onClearChanges);
    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &EditBookDialog::onCancel);
}

EditBookDialog::~EditBookDialog()
{
    delete ui;
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

    if (mBook->getTitle() != ui->bookTitleLabel->text())
        mDatabase.bookDao.changeTitle(mBook->getId(), ui->bookTitleLabel->text());

    if (mBook->getPublicationYear() != ui->yearLabel->text().toInt())
        mDatabase.bookDao.changePublicationYear(mBook->getId(), ui->yearLabel->text().toInt());

    if (mBook->getCopies() != ui->copiesLabel->text().toInt())
        mDatabase.bookDao.changeNumberOfCopies(mBook->getId(), ui->copiesLabel->text().toInt());

    onCancel();
}

void EditBookDialog::onClearChanges()
{
    ui->bookTitleLabel->setText(mBook->getTitle());
    ui->bookTitleLabel->setStyleSheet("QLabel { color : black; }");

    ui->authorListLabel->setText(mBook->printAuthor());

    ui->yearLabel->setText(QString::number(mBook->getPublicationYear()));
    ui->yearLabel->setStyleSheet("QLabel { color : black; }");

    ui->copiesLabel->setText(QString::number(mBook->getCopies()));
    ui->copiesLabel->setStyleSheet("QLabel { color : black; }");
}

void EditBookDialog::onCancel()
{

    this->close();
    this->deleteLater();
}
