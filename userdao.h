#ifndef USERDAO_H
#define USERDAO_H

#include <QSqlDatabase>
#include <vector>

#include "user.h"

class UserDao
{
public:
    UserDao(QSqlDatabase& database);
    ~UserDao();

    User *getUserData(QString name);
    std::vector<QString> getUserNames(QString name);

    void addUser(User* user, QString password);
    void removeUser(int id);

private:
    QDate toQDate(QString date);
private:
    QSqlDatabase& mDatabase;
};

#endif // USERDAO_H
