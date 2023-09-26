#ifndef USERDAO_H
#define USERDAO_H

#include <QSqlDatabase>
#include <vector>

#include "user.h"

const int USERNAME_MIN = 5;
const int USERNAME_MAX = 20;

class UserDao
{
public:
    UserDao(QSqlDatabase& database);
    ~UserDao();

    User *getUserData(QString name);
    std::vector<QString> getUserNames(QString name);

    bool findUserName(QString name);
    void addUser(User* user, QString password);
    void changeUserName(int id, QString newName);
    void removeUser(int id);

    bool checkNameLength(QString name);

private:
    QDate toQDate(QString date);
private:
    QSqlDatabase& mDatabase;
};

#endif // USERDAO_H
