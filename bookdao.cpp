
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
    book->setAvailable(query.value("available").toInt());
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

std::shared_ptr<Book> BookDao::getBookDataId(int bookID)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT * FROM book WHERE id =" + QString::number(bookID));
    std::shared_ptr<Book> book = std::make_shared<Book>(Book());

    //may be replaced later??
    book->setId(query.value("id").toInt());
    book->setTitle(query.value("title").toString());
    book->setPublicationYear(query.value("publicationYear").toInt());
    book->setAvailable(query.value("available").toInt());
    book->setCopies(query.value("copies").toInt());

    query.exec("SELECT firstName, lastName FROM book "
               "INNER JOIN bookAuthor ON book.id = bookAuthor.bookID "
               "INNER JOIN author ON bookAuthor.authorID  = author.id "
               "WHERE title = '" + book->getTitle() + "'");
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

void BookDao::addBook(Book book)
{

    QSqlQuery query(mDatabase);
    query.exec("INSERT INTO book (title, publicationYear, available, copies) "
               "VALUES('" + book.getTitle() + "', '" + QString::number(book.getPublicationYear()) + "', '"+ QString::number(book.getAvailable()) +
               "', '"+ QString::number(book.getCopies()) + "')");
    DatabaseManager::debugQuery(query);
    query.clear();

    query.exec("SELECT id FROM book WHERE title ='" + book.getTitle() + "'");
    query.next();
    book.setId(query.value("id").toInt());

    updateAuthors(book);

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

void BookDao::updateAuthors(Book book)
{
    int authorID = Id::NOT_EXIST;
    std::vector<Person> authorsToAdd = book.compareAuthors(*getBookDataTitle(book.getTitle()));
    for (Person& author : authorsToAdd)
    {
        authorID = checkAuthorExists(author);

        if (authorID ==Id::NOT_EXIST)
            authorID = addAuthor(author);

        addBookAuthor(book.getId(), authorID);

    }
}

void BookDao::removeAuthors(std::vector<Person> authors)
{
    int authorID;
    int titlesNumber;

    for (Person& author : authors)
    {
        authorID = checkAuthorExists(author);
        titlesNumber = countBooks(author);

        if (authorID != Id::NOT_EXIST && titlesNumber == 0)
            removeAuthor(author);
    }

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

void BookDao::updateBookAuthors(int bookID, std::vector<Person> removedAuthors)
{
    QSqlQuery query(mDatabase);

    for (Person& author : removedAuthors)
    {
        int authorID = checkAuthorExists(author);
        query.exec("DELETE FROM bookAuthor WHERE bookID = " + QString::number(bookID) +
                   " AND authorID = " + QString::number(authorID));
        DatabaseManager::debugQuery(query);

    }

}

void BookDao::changeBookData(Book book)
{
    QSqlQuery query(mDatabase);
    query.exec("UPDATE book"
               "SET title = " + book.getTitle() + ", "
               "publicationYear = " + QString::number(book.getPublicationYear()) + ", "
               "available = " + QString::number(book.getAvailable()) + ", "
               "copies = " + QString::number(book.getCopies()) + ", "
               "WHERE id = " + QString::number(book.getId()));
    DatabaseManager::debugQuery(query);

    updateAuthors(book);
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

    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM book WHERE id = (:id)");
    query.bindValue(":id", book->getId());
    query.exec();

    DatabaseManager::debugQuery(query);
    query.prepare("DELETE FROM bookAuthor WHERE bookID = (:id)");
    query.bindValue(":id", book->getId());
    query.exec();

    DatabaseManager::debugQuery(query);

    std::vector<Person> authorsToRemove = book->getAuthors();
    removeAuthors(authorsToRemove);
}

void BookDao::changeTitle(int id, QString newTitle)
{
    QSqlQuery query(mDatabase);
    query.exec("UPDATE book SET title = '" + newTitle + "' WHERE id = " + QString::number(id));
    DatabaseManager::debugQuery(query);

}

void BookDao::changePublicationYear(int id, int year)
{
    QSqlQuery query(mDatabase);
    query.exec("UPDATE book SET publicationYear = '" + QString::number(year) + "' WHERE id = " + QString::number(id));
    DatabaseManager::debugQuery(query);
}

void BookDao::changeNumberOfAvailable(int id, int available)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT copies FROM book WHERE id = " + QString::number(id));
    if (available >=0 && available <= query.value("copies").toInt())
    {
        query.exec("UPDATE book SET available = '" + QString::number(available) + "' WHERE id = " + QString::number(id));
    }
    DatabaseManager::debugQuery(query);
}

void BookDao::changeNumberOfCopies(int id, int copies)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT available FROM book WHERE id = " + QString::number(id));
    if (query.value("available").toInt() <= copies)
        query.exec("UPDATE book SET copies = '" + QString::number(copies) + "' WHERE id = " + QString::number(id));
    DatabaseManager::debugQuery(query);
}
