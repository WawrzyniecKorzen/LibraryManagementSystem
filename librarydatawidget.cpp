#include "librarydatawidget.h"
#include "ui_librarydatawidget.h"

#include "bookwidget.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QDebug>
#include <QPushButton>

libraryDataWidget::libraryDataWidget(QWidget *parent, DatabaseManager& database) :
    QWidget(parent),
    ui(new Ui::libraryDataWidget),
    mDatabase(database)
{
    ui->setupUi(this);

    mWidget = new QWidget(this);
    mWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    mWidget->setLayout(new QVBoxLayout(mWidget));
    ui->scrollArea->setWidget(mWidget);
    QPushButton* button = new QPushButton(this);
    button->setText("button");
    mWidget->layout()->addWidget(button);


    Book* book = new Book(0, "Wojna peloponeska", "Tukidydes", "Grek", 2010, 2);
    BookWidget* bookWidget = new BookWidget(this, book);

    mWidget->layout()->addWidget(bookWidget);



    std::vector<QString> titles = mDatabase.bookDao.getBookTitles();
    for (QString& title : titles)
    {
        books.push_back(mDatabase.bookDao.getBookDataTitle(title));
    }

    for (auto it = books.begin(); it != books.end(); it++)
    {
        BookWidget* book = new BookWidget(this, *it);

        //book->setSizePolicy(QSizePolicy ::Fixed , QSizePolicy ::MinimumExpanding );
        //book->resize();
        mWidget->layout()->addWidget(book);
    }
    demo();

    this->show();

}

libraryDataWidget::~libraryDataWidget()
{
    delete ui;
}

void libraryDataWidget::demo()
{
    std::vector<QString> titles = mDatabase.bookDao.getBookTitles();

    for (QString& title : titles)
    {
        books.push_back(mDatabase.bookDao.getBookDataTitle(title));
    }
    for (auto it = books.begin(); it != books.end(); it++)
    {
        BookWidget* book = new BookWidget(this, *it);

        mWidget->layout()->addWidget(book);
    }



}
