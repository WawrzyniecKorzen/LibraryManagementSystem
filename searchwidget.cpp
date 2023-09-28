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

        Book* book = mDatabase.bookDao.getBookDataTitle(title);
        addBookWidget(book);

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

    widgetList.clear();
    bookListMap.clear();
}

void SearchWidget::addBookWidget(Book *book)
{
    QHBoxLayout* layout = new QHBoxLayout(bookList);
    QRadioButton* radio = new QRadioButton(bookList);
    BookWidget* bookWidget = new BookWidget(bookList, book);
    layout->addWidget(radio);
    layout->addWidget(bookWidget);
    QVBoxLayout* listLayout = qobject_cast<QVBoxLayout*>(bookList->layout());
    listLayout->addLayout(layout);

    widgetList.push_back(radio);
    bookListMap.insert(radio, bookWidget);
}

Book *SearchWidget::findPickedBook()
{
    if (widgetList.size() == 0)
    {
        return nullptr;
    }
    QRadioButton* radio = nullptr;
    for (QRadioButton* button : widgetList)
    {
        if (button->isChecked())
        {
            radio = button;
            break;
        }
    }
    if (radio == nullptr)
        return nullptr;
    return bookListMap.value(radio)->getBook();
}

void SearchWidget::removePickedBook()
{

    QRadioButton* radio = nullptr;
    int i;
    for (i = 0; i < widgetList.size(); i++)
    {
        if (widgetList[i]->isChecked())
        {
            radio = widgetList[i];

            break;
        }
    }

    if (radio != nullptr)
    {
    widgetList.erase(widgetList.begin()+i);
    BookWidget* bookWidget = bookListMap.value(radio);
    bookListMap.remove(radio);
    radio->hide();
    bookWidget->hide();

    radio->deleteLater();
    bookWidget->deleteLater();
    }
}
