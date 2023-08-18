
#include "logindao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "databasemanager.h"


LoginDao::LoginDao(QSqlDatabase& database) : mDatabase(database)
{

}

bool LoginDao::login(QString name, QString password)
{
    QSqlQuery query(mDatabase);
    //query.prepare("SELECT password FROM login WHERE name = '" + name + "';");

    query.exec("SELECT password FROM login WHERE name = '" + name + "'");
    DatabaseManager::debugQuery(query);
    query.next();
    QString result =  query.value(0).toString();

    if (password == result)
        return true;
    return false;
}
/*
QString LoginDao::searchLogin(QString name)
{


    QSqlQuery query(mDatabase);
    query.prepare("SELECT password FROM login WHERE name = (:name)");
    query.bindValue(":name", name);
    query.exec();
    DatabaseManager::debugQuery(query);
    return query.value(0).toString();
}
*/
