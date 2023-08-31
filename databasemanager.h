
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <memory>
#include "logindao.h"
#include "userdao.h"


class QSqlQuery;
class QSqlDatabase;

const QString FILENAME = "library.db";


class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

    static void debugQuery(const QSqlQuery& query);
    void init();
    void initialiseLogin();
    void initialiseBook();
    void initialiseBookAuthor();
    void initialiseAuthor();

protected:
    DatabaseManager(const QString& path = FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    //std::unique_ptr<QSqlDatabase> mDatabase;
    QSqlDatabase* mDatabase;

public:
    LoginDao loginDao;
    UserDao userDao;
};

#endif // DATABASEMANAGER_H
