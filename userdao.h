
#ifndef USERDAO_H
#define USERDAO_H

#include "user.h"

#include <QSqlDatabase>
#include <vector>


class UserDao
{
public:
    UserDao(QSqlDatabase &database);
    ~UserDao();

    std::vector<QString> getUserNames(QString name);
    User* getUserData(QString name);


private:
    QSqlDatabase& mDatabase;
};

#endif // USERDAO_H
