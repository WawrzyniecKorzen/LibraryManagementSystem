#include "bookwidget.h"
#include "ui_bookwidget.h"



BookWidget::BookWidget(QWidget *parent, Book *book) :
    QWidget(parent),
    ui(new Ui::BookWidget), mBook(book)
{
    ui->setupUi(this);
    ui->titleLabel->setText(mBook->getTitle());
    ui->authorName->setText(mBook->getAuthor());
    ui->publicationNumber->setText(QString::number(mBook->getPublicationYear()));
    ui->copiesNumber->setText(QString::number(mBook->getCopies()));
}

BookWidget::~BookWidget()
{
    delete ui;
}
