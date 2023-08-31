
#ifndef USERDAO_H
#define USERDAO_H

#include <QSqlDatabase>
#include "user.h"

class UserDao
{
public:
    UserDao(QSqlDatabase& database);
    ~UserDao();

    User *getUserData(QString name);
private:
    QDate toQDate(QString date);
private:
    QSqlDatabase& mDatabase;
};

#endif // USERDAO_H
