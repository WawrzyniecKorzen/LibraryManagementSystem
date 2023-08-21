
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

