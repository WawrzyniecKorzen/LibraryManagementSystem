
#include "userdao.h"
#include "databasemanager.h"
#include <QSqlQuery>


UserDao::UserDao(QSqlDatabase &database) : mDatabase(database)
{

}

UserDao::~UserDao()
{

}

User *UserDao::getUserData(QString name)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT * FROM login WHERE name = '" + name + "'");
    DatabaseManager::debugQuery(query);
    query.next();
    User* user = new User();
    qDebug() << query.value("id").toInt();
    user->setId(query.value("id").toInt());
    user->setName(query.value("name").toString());
    user->setStatus(query.value("status").toInt());
    return user;
}
