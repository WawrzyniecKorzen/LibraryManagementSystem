
#include "userdao.h"
#include "databasemanager.h"




UserDao::UserDao(QSqlDatabase &database) : mDatabase(database)
{

}

UserDao::~UserDao()
{

}

std::vector<QString> UserDao::getUserNames(QString name)
{
    std::vector<QString> users;
    QSqlQuery query(*mDatabase);
    query.exec("SELECT name FROM login WHERE name LIKE '%" + name + "%'");
    DatabaseManager::debugQuery(query);
    while(query.next())
        users.push_back(query.value("name").toString());

    return users;
}

User *UserDao::getUserData(QString name)
{

    QSqlQuery query(mDatabase);
    query.exec("SELECT * FROM login WHERE name = '" + name + "'");
    DatabaseManager::debugQuery(query);
    query.next();

    User* user = new User();
}
