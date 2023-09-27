#include "searchwidget.h"
#include "ui_searchwidget.h"


#include <QDebug>

SearchWidget::SearchWidget(QWidget *parent, DatabaseManager& database) :
    QWidget(parent),
    ui(new Ui::SearchWidget),
    mDatabase(database)
{
    ui->setupUi(this);
    ui->titleRadio->setChecked(true);
    ui->authorEdit->setDisabled(true);
    ui->searchButton->setDefault(true);
    ui->titleEdit->setFocus();

    setBookList();
    QObject::connect(ui->searchButton, &QPushButton::clicked, this, &SearchWidget::onSearchButton);
    QObject::connect(ui->titleRadio, &QRadioButton::clicked, this, &SearchWidget::onTitleRadio);
    QObject::connect(ui->authorRadio, &QRadioButton::clicked, this, &SearchWidget::onAuthorRadio);
}

SearchWidget::~SearchWidget()
{
    delete ui;
}

void SearchWidget::onSearchButton()
{
    qDebug() << "search button clicked with title: " << ui->titleEdit->text() << " and author: " << ui->authorEdit->text();

    std::vector<QString> titles;
    if (ui->titleRadio->isChecked())    
    {
        if (ui->titleEdit->text().isEmpty())
            return;
        titles = mDatabase.findBookTitles(ui->titleEdit->text());
    }
    else
    {
        if (ui->authorEdit->text().isEmpty())
            return;
        qDebug() << "search button else branch";
        titles = mDatabase.findBookAuthors(ui->authorEdit->text());
    }
    delete bookList;

    setBookList();
    for (QString& title : titles)
    {
        qDebug() << "found book: " << title;
        Book* book = mDatabase.bookDao.getBookDataTitle(title);
        BookWidget* bookWidget = new BookWidget(bookList, book);
        bookList->layout()->addWidget(bookWidget);
    }
    ui->titleEdit->clear();
    ui->authorEdit->clear();
}

void SearchWidget::onTitleRadio()
{
    ui->authorEdit->setDisabled(true);
    ui->titleEdit->setDisabled(false);
}

void SearchWidget::onAuthorRadio()
{
    ui->authorEdit->setDisabled(false);
    ui->titleEdit->setDisabled(true);
}

void SearchWidget::setBookList()
{
    bookList = new QWidget(this);
    bookList->setLayout(new QVBoxLayout());
    ui->verticalLayout->insertWidget(1, bookList);
}
