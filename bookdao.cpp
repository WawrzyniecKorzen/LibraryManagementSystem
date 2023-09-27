
#include "bookdao.h"
#include "databasemanager.h"
#include <QSqlQuery>



BookDao::BookDao(QSqlDatabase &database) : mDatabase(database)
{

}

BookDao::~BookDao()
{

}

Book *BookDao::getBookDataTitle(QString title)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT * FROM book "
               "WHERE title = '" + title + "'");
    DatabaseManager::debugQuery(query);
    query.next();
    Book* book = new Book();

    book->setId(query.value("id").toInt());
    book->setTitle(query.value("title").toString());
    book->setPublicationYear(query.value("publicationYear").toInt());
    book->setCopies(query.value("copies").toInt());

    query.exec("SELECT firstName, lastName FROM book "
                        "INNER JOIN bookAuthor ON book.id = bookAuthor.bookID "
                        "INNER JOIN author ON bookAuthor.authorID  = author.id "
                        "WHERE title = '" + title + "'");
    while (query.next())
        {
        Person p;
        QString temp = query.value("firstName").toString();
        p.setFirstName(temp);
        temp = query.value("lastName").toString();
        p.setLastName(temp);
        book->setAuthor(p);
        }

    return book;
}

std::vector<QString> BookDao::getBookTitles()
{
    std::vector<QString> titles;

    QSqlQuery query(mDatabase);
    query.exec("SELECT title FROM book LIMIT 5");
    while (query.next())
    {
        titles.push_back(query.value("title").toString());
    }
    return titles;

}

void BookDao::addBook(Book book)
{

    QSqlQuery query(mDatabase);
    query.exec("INSERT INTO book (title, publicationYear, copies) "
               "VALUES('" + book.getTitle() + "', '" + QString::number(book.getPublicationYear()) + "', '"+ QString::number(book.getCopies()) + "')");
    DatabaseManager::debugQuery(query);
    query.clear();

    query.exec("SELECT id FROM book WHERE title ='" + book.getTitle() + "'");
    query.next();
    book.setId(query.value("id").toInt());

    int authorID = Id::NOT_EXIST;
    std::vector<Person> authors = book.getAuthors();
    for (Person& author : authors)
    {
        authorID = checkAuthorExists(author);

        if (authorID ==Id::NOT_EXIST)
            authorID = addAuthor(author);

        addBookAuthor(book.getId(), authorID);

    }

}

int BookDao::checkAuthorExists(Person author)
{
    int result = Id::NOT_EXIST;

    QSqlQuery query(mDatabase);

    query.exec("SELECT id FROM author WHERE firstName = '" + author.getFirstName() + "' AND lastName = '" + author.getLastName() + "'");

    while (query.next())
    {
        qDebug() << "inner loop! " << query.value("id").toInt();
        result = query.value("id").toInt();
    }
    qDebug() << "obtained id: " << result;
    DatabaseManager::debugQuery(query);
    return result;
}

int BookDao::addAuthor(Person author)
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO author (firstName, lastName) "
                  "VALUES ((:first), (:last))");
    query.bindValue(":first", author.getFirstName());
    query.bindValue(":last", author.getLastName());
    query.exec();
    DatabaseManager::debugQuery(query);

    int id = checkAuthorExists(author);
    qDebug() << "add author id = " << id;
    return id;
}

void BookDao::addBookAuthor(int bookID, int authorID)
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO bookAuthor (bookID, authorID)"
                  "VALUES ((:book), (:author))");
    query.bindValue(":book", bookID);
    query.bindValue(":author", authorID);
    query.exec();
    DatabaseManager::debugQuery(query);

}

int BookDao::countBooks(Person author)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT COUNT(title) FROM book "
               "INNER JOIN bookAuthor ON book.id = bookAuthor.bookID "
               "INNER JOIN author ON bookAuthor.authorID  = author.id "
               "WHERE author.firstName = '" + author.getFirstName() + "' AND author.lastName = '" + author.getLastName() + "'");
    query.next();
    return query.value("COUNT(title)").toInt();
}

void BookDao::removeAuthor(Person author)
{
    QSqlQuery query(mDatabase);
    query.exec("DELETE FROM author WHERE firstName = '"+ author.getFirstName() + "' AND lastName = '" + author.getLastName() + "'");
    DatabaseManager::debugQuery(query);
}

void BookDao::removeBook(Book* book)
{
    int numberOfBooks;
    for (Person& person : book->getAuthors())
    {
        numberOfBooks = countBooks(person);
        if (numberOfBooks == 1)
            removeAuthor(person);
    }

    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM book WHERE id = (:id)");
    query.bindValue(":id", book->getId());
    query.exec();

    DatabaseManager::debugQuery(query);
    query.prepare("DELETE FROM bookAuthor WHERE bookID = (:id)");
    query.bindValue(":id", book->getId());
    query.exec();

    DatabaseManager::debugQuery(query);
}
