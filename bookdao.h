
#ifndef BOOKDAO_H
#define BOOKDAO_H

#include "book.h"
#include <QSqlDatabase>
#include <vector>


class BookDao
{
public:
    BookDao(QSqlDatabase &database);
    ~BookDao();

    Book *getBookDataTitle(QString title);
    std::vector<QString> getBookTitles();

private:
    QSqlDatabase& mDatabase;
};

#endif // BOOKDAO_H




