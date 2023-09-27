
#ifndef BOOKDAO_H
#define BOOKDAO_H

#include "book.h"
#include <QSqlDatabase>
#include <vector>


class BookDao
{
public:
    enum Id {
        NOT_EXIST = -1
    };
    BookDao(QSqlDatabase &database);
    ~BookDao();

    Book *getBookDataTitle(QString title);
    std::vector<QString> getBookTitles();

    void addBook(Book book);
    int checkAuthorExists(Person author);
    int addAuthor(Person author);
    void addBookAuthor(int bookID, int authorID);

    int countBooks(Person author);
    void removeAuthor(Person author);
    void removeBook(Book* book);


private:
    QSqlDatabase& mDatabase;
};

#endif // BOOKDAO_H




