
#include "logindao.h"
#include "databasemanager.h"
#include "sha256.h"

#include <QSqlDatabase>
#include <QSqlQuery>



LoginDao::LoginDao(QSqlDatabase& database) : mDatabase(database)
{

}

LoginDao::~LoginDao()
{

}

bool LoginDao::login(QString name, QString password)
{
    SHA256 temp = SHA256(password);
    password = temp.hash();

    if (password == LoginDao::searchLogin(name))
        return true;
    return false;
}

QString LoginDao::searchLogin(QString name)
{

    QSqlQuery query(mDatabase);
    query.exec("SELECT password FROM login WHERE name = '" + name + "'");
    DatabaseManager::debugQuery(query);
    query.next();

    return query.value(0).toString();
}

bool LoginDao::checkPassword(int id, QString pass)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT password FROM login WHERE id = "+ QString::number(id));
    DatabaseManager::debugQuery(query);
    query.next();

    QString password = query.value(0).toString();
    qDebug() << password;
    if (SHA256(pass).hash() == password)
        return true;
    return false;

}

void LoginDao::changePassword(int id, QString newPassword)
{
    QSqlQuery query(mDatabase);
    query.exec("UPDATE login SET password ='" + SHA256(newPassword).hash() +"' WHERE id = " + QString::number(id));
    DatabaseManager::debugQuery(query);
}

