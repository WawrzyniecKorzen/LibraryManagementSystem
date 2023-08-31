
#ifndef LOGINDAO_H
#define LOGINDAO_H
#include <QString>
#include <vector>


class QSqlDatabase;


class LoginDao
{
public:
    LoginDao(QSqlDatabase& database);
    ~LoginDao();

    bool login(QString name, QString password);


    QString searchLogin(QString name);
    bool checkPassword(int id, QString pass);
    void changePassword(int id, QString newPassword);


private:
    QSqlDatabase& mDatabase;
};

#endif // LOGINDAO_H
