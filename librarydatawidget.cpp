#include "librarydatawidget.h"
#include "ui_librarydatawidget.h"

#include "bookwidget.h"

#include <QVBoxLayout>

libraryDataWidget::libraryDataWidget(QWidget *parent, DatabaseManager& database) :
    QWidget(parent),
    ui(new Ui::libraryDataWidget),
    mDatabase(database)
{
    ui->setupUi(this);
    layout = new QVBoxLayout(this);
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
        layout->addWidget(new BookWidget(this, *it));
    }

}
