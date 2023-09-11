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

    stackedPanel = new QStackedWidget(this);

    tabBar = new QWidget(this);
    QHBoxLayout* tabLayout = new QHBoxLayout(tabBar);
    tabBar->setLayout(tabLayout);

    QPushButton* myBooks = new QPushButton(tabBar);
    myBooks->setText("My Books");
    myBooks->setCheckable(true);
    myBooks->setChecked(true);
    myBooks->setAutoExclusive(true);
    tabBar->layout()->addWidget(myBooks);

    QPushButton* mySearch = new QPushButton(tabBar);
    mySearch->setText("My Search");
    mySearch->setCheckable(true);
    mySearch->setAutoExclusive(true);
    tabBar->layout()->addWidget(mySearch);

    tabLayout->addStretch();


    QVBoxLayout* lay = qobject_cast<QVBoxLayout*>(this->layout());
    lay->insertWidget(0, tabBar);

    mWidget = new QWidget(this);
    mWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    mWidget->setLayout(new QVBoxLayout(mWidget));


    Book* book = new Book(0, "Wojna peloponeska", "Tukidydes", "Grek", 2010, 2);
    BookWidget* bookWidget = new BookWidget(this, book);

    mWidget->layout()->addWidget(bookWidget);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


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

    searchWidget = new QWidget(this);
    searchWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    searchWidget->setLayout(new QVBoxLayout(searchWidget));


    stackedPanel->addWidget(mWidget);
    stackedPanel->addWidget(searchWidget);
    ui->scrollArea->setWidget(stackedPanel);

    QObject::connect(myBooks, &QPushButton::clicked, this, &libraryDataWidget::onMyBooks);
    QObject::connect(mySearch, &QPushButton::clicked, this, &libraryDataWidget::onMySearch);

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

void libraryDataWidget::onMyBooks()
{
    stackedPanel->setCurrentWidget(mWidget);

}

void libraryDataWidget::onMySearch()
{
    stackedPanel->setCurrentWidget(searchWidget);
}
