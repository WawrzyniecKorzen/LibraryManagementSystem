
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

    user->setJoined(UserDao::toQDate(query.value("joined").toString()));
    user->setStatus(query.value("status").toInt());
    return user;
}

std::vector<QString> UserDao::getUserNames(QString name)
{
    QSqlQuery query(mDatabase);
    std::vector<QString> users;

    query.exec("SELECT name FROM login WHERE name LIKE '%" + name + "%'");
    DatabaseManager::debugQuery(query);
    while(query.next())
        users.push_back(query.value("name").toString());

    return users;
}

QDate UserDao::toQDate(QString date)
{
    int year, month, day = 0;
    QString temp;
    for (int i = 0; i < 2; i++)
    {
        temp.append(date[i]);
    }
    day = temp.toInt();
    temp.clear();
    for (int i = 3; i < 5; i++)
    {
        temp.append(date[i]);
    }
    month = temp.toInt();
    temp.clear();
    for (int i = 6; i < 10; i++)
    {
        temp.append(date[i]);
    }
    year = temp.toInt();
    temp.clear();

    return QDate(year, month, day);
}
