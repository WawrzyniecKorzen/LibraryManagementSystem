
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
    query.exec("SELECT * FROM books "
               "INNER JOIN bookAuthor ON book.id = bookAuthor.bookID "
               "INNER JOIN author ON bookAuthor.authorID  = author.id "
               "WHERE title = '" + title + "'");
    DatabaseManager::debugQuery(query);
    query.next();
    Book* book = new Book();

    book->setId(query.value("id").toInt());
    book->setTitle(query.value("title").toString());
    book->setPublicationYear(query.value("publicationYear").toInt());
    book->setCopies(query.value("copies").toInt());
    book->setAuthorFirstName(query.value("firstName").toString());
    book->setAuthorLastName(query.value("lastName").toString());

    //missing author;
    return book;
}
