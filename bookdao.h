
#ifndef BOOKDAO_H
#define BOOKDAO_H

#include "book.h"
#include <QSqlDatabase>
#include <vector>
#include <memory>


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
    std::shared_ptr<Book> getBookDataId(int bookID);

    void addBook(Book book);
    int checkAuthorExists(Person author);
    void updateAuthors(Book book);
    void removeAuthors(std::vector<Person> authors);
    int addAuthor(Person author);
    void addBookAuthor(int bookID, int authorID);
    void updateBookAuthors(int bookID, std::vector<Person> removedAuthors);
    void changeBookData(Book book);

    int countBooks(Person author);
    void removeAuthor(Person author);
    void removeBook(Book* book);

    void changeTitle(int id, QString newTitle);
    void changePublicationYear(int id, int year);
    void changeNumberOfAvailable(int id, int available);
    void changeNumberOfCopies(int id, int copies);



private:
    QSqlDatabase& mDatabase;
};

#endif // BOOKDAO_H




