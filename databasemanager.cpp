
#include "databasemanager.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>



DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
}

void DatabaseManager::debugQuery(const QSqlQuery &query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError)
        qDebug() << "Query OK: "<<query.lastQuery();
    else
    {
        qWarning() << "Query KO: " << query.lastError().text();
        qWarning() << "Query text: " << query.lastQuery();
    }
}

void DatabaseManager::init()
{

    QSqlQuery query(*mDatabase);
    query.exec("CREATE TABLE login (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, password TEXT, status INTEGER)");
    DatabaseManager::debugQuery(query);
    query.exec("INSERT INTO login (name, password, status) "
               "VALUES('admin', '9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08', '0')");
    query.exec("INSERT INTO login (name, password, status) "
               "VALUES('user', '9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08', '1')");
    DatabaseManager::debugQuery(query);
}

DatabaseManager::DatabaseManager(const QString &path) :
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    loginDao(*mDatabase), userDao(*mDatabase)
{
    mDatabase->setDatabaseName(path);

    bool openStatus = mDatabase->open();
    qDebug() << "Database connection: " << (openStatus ? "Ok" : "Error");

    if (!mDatabase->tables().contains("login")) {
        DatabaseManager::init();
    }
}
