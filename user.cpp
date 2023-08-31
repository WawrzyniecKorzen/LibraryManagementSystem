
#include "user.h"




User::User(int id, QString name, QDate date, int status) : id(id), name(name), joined(date), status(status)
{

}

User::~User()
{

}

void User::setId(int num)
{
    id = num;
}

void User::setName(QString text)
{
    name = text;
}

void User::setJoined(QDate date)
{
    joined = date;
}

void User::setStatus(int s)
{
    status = s;
}

int User::getId()
{
    return id;
}

QString User::getName()
{
    return name;
}

QDate User::getJoined()
{
    return joined;
}

int User::getStatus()
{
    return status;
}
