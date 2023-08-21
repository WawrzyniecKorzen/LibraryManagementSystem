
#include "user.h"




User::User(int id, QString name, int status) : id(id), name(name), status(status)
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

int User::getStatus()
{
    return status;
}
