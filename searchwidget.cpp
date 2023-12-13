#include "searchwidget.h"
#include "ui_searchwidget.h"


#include <QDebug>
#include <QMessageBox>

SearchWidget::SearchWidget(QWidget *parent, DatabaseManager& database, User* user) :
    QWidget(parent),
    ui(new Ui::SearchWidget),
    mDatabase(database),
    mUser(user)
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
        titles = mDatabase.findBookAuthors(ui->authorEdit->text());
    }
    delete bookList;

    setBookList();

    for (QString& title : titles)
    {

        Book* book = mDatabase.bookDao.getBookDataTitle(title);
        addBookWidget(book);
    }
    if (titles.size() !=0)
    {
        QHBoxLayout* reserveLayout = new QHBoxLayout(bookList);
        reserveLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));

        reserveButton = new QPushButton("Reserve selected book", this);
        reserveLayout->addWidget(reserveButton);

        QVBoxLayout* listLayout = qobject_cast<QVBoxLayout*>(bookList->layout());
        listLayout->addLayout(reserveLayout);

        QObject::connect(reserveButton, &QPushButton::clicked, this, &SearchWidget::onReserveButton);
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

void SearchWidget::onReserveButton()
{
    Book* book = findPickedBook();
    if(book != nullptr && book->getAvailable() > 0)
    {
        QString message = "Do you want to reserve \"" + book->getTitle() + "\" by " + book->printAuthor() + "?";
        int decision = QMessageBox::question(this, "Book reservation", message, QMessageBox::Ok, QMessageBox::No);
        if (decision == QMessageBox::Ok)
            reserveBook(book);
    }
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
    layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
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

void SearchWidget::reserveBook(Book *book)
{
    //check if this reservation is already done

    Reservation reservation;
    reservation.setBookID(book->getId());
    reservation.setUserID(mUser->getId());
    reservation.setDate(QDate::currentDate());
    reservation.setUser(std::make_shared<User>(*mUser));
    reservation.setBook(std::make_shared<Book>(*book));
    if(mDatabase.reservationDao.checkReservation(reservation.getBookID(), reservation.getUserID()))
        QMessageBox::warning(this, "Reservation error", "This book is already reservaed by you", QMessageBox::Ok);
    else
        mDatabase.reservationDao.addReservation(reservation);
}
