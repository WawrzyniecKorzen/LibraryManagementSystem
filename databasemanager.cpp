
#include "databasemanager.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>



DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
}

void DatabaseManager::debugQuery(const QSqlQuery &query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError)
        qDebug() << "Query OK: "<<query.lastQuery();
    else
    {
        qWarning() << "Query KO: " << query.lastError().text();
        qWarning() << "Query text: " << query.lastQuery();
    }
}

void DatabaseManager::init()
{
    initialiseLogin();
    initialiseBook();
    initialiseAuthor();
    initialiseBookAuthor();
    initialiseReservation();
    initialiseLoan();
}

void DatabaseManager::initialiseLogin()
{
    QDate date = QDate::currentDate();
    QSqlQuery query(*mDatabase);
    query.exec("CREATE TABLE login (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, password TEXT, joined TEXT, status INTEGER)");
    DatabaseManager::debugQuery(query);
    query.exec("INSERT INTO login (name, password, joined, status) "
               "VALUES('admin', '9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08','" + date.toString("dd.MM.yyyy") + "','0')");
    query.exec("INSERT INTO login (name, password, joined, status) "
               "VALUES('user', '9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08','" + date.toString("dd.MM.yyyy") + "', '1')");
    DatabaseManager::debugQuery(query);
}

void DatabaseManager::initialiseBook()
{

    QSqlQuery query(*mDatabase);
    query.exec("CREATE TABLE book (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT, publicationYear INTEGER, available INTEGER, copies INTEGER)");
    DatabaseManager::debugQuery(query);
    query.exec("INSERT INTO book (title, publicationYear, available, copies) "
               "VALUES('The Lord Of The Rings', 2000, 5, 5)");
    DatabaseManager::debugQuery(query);
    query.exec("INSERT INTO book (title, publicationYear, available, copies) "
               "VALUES('Silmarillion', 2002, 3, 4)");
    DatabaseManager::debugQuery(query);
    query.exec("INSERT INTO book (title, publicationYear, available, copies) "
               "VALUES('Surely Youre Joking, Mr. Feynman!: Adventures of a Curious Character', 2018, 10, 10)");
    query.exec("INSERT INTO book (title, publicationYear, available, copies) "
               "VALUES('An Introduction To Quantum Field Theory', 1995, 1, 1)");

    DatabaseManager::debugQuery(query);
}

void DatabaseManager::initialiseBookAuthor()
{
    QSqlQuery query(*mDatabase);
    query.exec("CREATE TABLE bookAuthor (id INTEGER PRIMARY KEY AUTOINCREMENT, bookID INT, authorID INT)");
    DatabaseManager::debugQuery(query);
    query.exec("INSERT INTO bookAuthor (bookID, authorID) "
               "VALUES(1, 1)");
    query.exec("INSERT INTO bookAuthor (bookID, authorID) "
               "VALUES(2, 1)");
    query.exec("INSERT INTO bookAuthor (bookID, authorID) "
               "VALUES(3, 2)");
    query.exec("INSERT INTO bookAuthor (bookID, authorID) "
               "VALUES(4, 3)");
    query.exec("INSERT INTO bookAuthor (bookID, authorID) "
               "VALUES(4, 4)");
    DatabaseManager::debugQuery(query);
}

void DatabaseManager::initialiseAuthor()
{
    QSqlQuery query(*mDatabase);
    query.exec("CREATE TABLE author (id INTEGER PRIMARY KEY AUTOINCREMENT, firstName TEXT, lastName TEXT)");
    DatabaseManager::debugQuery(query);
    query.exec("INSERT INTO author (firstName, lastName) "
               "VALUES('John R. R.', 'Tolkien')");
    query.exec("INSERT INTO author (firstName, lastName) "
               "VALUES('Richard', 'Feynman')");
    query.exec("INSERT INTO author (firstName, lastName) "
               "VALUES('Michael E.', 'Peskin')");
    query.exec("INSERT INTO author (firstName, lastName) "
               "VALUES('Daniel V.', 'Schroeder')");
    DatabaseManager::debugQuery(query);

}

void DatabaseManager::initialiseReservation()
{
    QSqlQuery query(*mDatabase);
    query.exec("CREATE TABLE reservation (id INTEGER PRIMARY KEY AUTOINCREMENT, bookID INTEGER, userID INTEGER, reservationDate TEXT)");
    DatabaseManager::debugQuery(query);
}

void DatabaseManager::initialiseLoan()
{
    QSqlQuery query(*mDatabase);
    query.exec("CREATE TABLE loan (id INTEGER PRIMARY KEY AUTOINCREMENT, bookID INTEGER, userID INTEGER, loanStartDate TEXT)");
    DatabaseManager::debugQuery(query);
}

std::vector<QString> DatabaseManager::findBookTitles(QString title)
{
    std::vector<QString> titles;
    QSqlQuery query(*mDatabase);
    query.exec("SELECT title FROM book WHERE title LIKE '%" + title + "%'");
    DatabaseManager::debugQuery(query);
    while(query.next())
        titles.push_back(query.value("title").toString());

    return titles;
}

std::vector<QString> DatabaseManager::findBookAuthors(QString name)
{
    //TODO - what happens when someone writes first AND last names!

    std::vector<QString> titles;
    QSqlQuery query(*mDatabase);
    query.exec("SELECT title FROM book "
                                     "INNER JOIN bookAuthor ON book.id = bookAuthor.bookID "
                                     "INNER JOIN author ON bookAuthor.authorID  = author.id "
                                     "WHERE author.firstName LIKE '%" + name + "%' OR author.lastName LIKE '%" + name + "%'");
    DatabaseManager::debugQuery(query);

    while(query.next())
        titles.push_back(query.value("title").toString());

    return titles;
}


DatabaseManager::DatabaseManager(const QString &path) :
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    loginDao(*mDatabase), userDao(*mDatabase), bookDao(*mDatabase),
    reservationDao(*mDatabase, std::make_shared<BookDao>(bookDao), std::make_shared<UserDao>(userDao))
{
    mDatabase->setDatabaseName(path);

    bool openStatus = mDatabase->open();
    qDebug() << "Database connection: " << (openStatus ? "Ok" : "Error");

    if (!mDatabase->tables().contains("login")) {
        DatabaseManager::init();
    }
}
