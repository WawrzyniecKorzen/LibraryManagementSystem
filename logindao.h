
#ifndef LOGINDAO_H
#define LOGINDAO_H
#include <QString>
#include <vector>


class QSqlDatabase;


class LoginDao
{
public:
    LoginDao(QSqlDatabase& database);

    bool login(QString name, QString password);

    //QString searchLogin(QString name);

private:
    QSqlDatabase& mDatabase;
};

#endif // LOGINDAO_H
