
#ifndef BOOKDAO_H
#define BOOKDAO_H

#include "book.h"
#include <QSqlDatabase>


class BookDao
{
public:
    BookDao(QSqlDatabase &database);
    ~BookDao();

    Book *getBookDataTitle(QString title);

private:
    QSqlDatabase& mDatabase;
};

#endif // BOOKDAO_H




