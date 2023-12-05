#include "bookwidget.h"
#include "ui_bookwidget.h"



BookWidget::BookWidget(QWidget *parent, Book *book) :
    QWidget(parent),
    ui(new Ui::BookWidget), mBook(book)
{
    ui->setupUi(this);
    ui->titleLabel->setText(mBook->getTitle());
    ui->titleLabel->setWordWrap(true);
    ui->authorName->setText(mBook->printAuthor());
    ui->publicationNumber->setText(QString::number(mBook->getPublicationYear()));
    ui->copiesNumber->setText(QString::number(mBook->getAvailable()) + "/" + QString::number(mBook->getCopies()));

    ui->titleLabel->setSizePolicy(QSizePolicy ::Fixed , QSizePolicy ::Expanding );
    ui->authorName->setSizePolicy(QSizePolicy ::Fixed , QSizePolicy ::Expanding );
    ui->authorLabel->setSizePolicy(QSizePolicy ::Fixed , QSizePolicy ::Expanding );
    ui->publicationLabel->setSizePolicy(QSizePolicy ::Fixed , QSizePolicy ::Expanding );
    ui->publicationNumber->setSizePolicy(QSizePolicy ::Fixed , QSizePolicy ::Expanding );
    ui->copiesLabel->setSizePolicy(QSizePolicy ::Fixed , QSizePolicy ::Expanding );
    ui->copiesNumber->setSizePolicy(QSizePolicy ::Fixed , QSizePolicy ::Expanding );
    this->layout()->setAlignment(ui->gridLayout,Qt::AlignLeft);


    this->setSizePolicy(QSizePolicy ::Fixed , QSizePolicy ::Expanding );
}

BookWidget::~BookWidget()
{
    delete ui;
}

Book *BookWidget::getBook()
{
    return mBook;
}
