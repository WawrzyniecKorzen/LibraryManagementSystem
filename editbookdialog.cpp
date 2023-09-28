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
    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &EditBookDialog::onCancel);
}

EditBookDialog::~EditBookDialog()
{
    delete ui;
}

void EditBookDialog::onNewTitle()
{
    qDebug() << "New Title button clicked";
    if (ui->newTitleEdit->text().isEmpty())
        return;
    int result = QMessageBox::question(this, "Confirm new title", "Are you sure?", QMessageBox::Ok | QMessageBox::Abort);

    if (result == QMessageBox::Ok)
    {

        ui->bookTitleLabel->setText(ui->newTitleEdit->text());
        ui->newTitleEdit->clear();
        ui->bookTitleLabel->setStyleSheet("QLabel { color : red; }");
    }
}

void EditBookDialog::onCancel()
{

    this->close();
    this->deleteLater();
}
