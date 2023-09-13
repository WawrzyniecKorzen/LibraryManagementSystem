
#include "person.h"

Person::Person(QString first, QString last) :
    firstName(first), lastName(last)
{

}

Person::Person(const Person &p)
{
    firstName = p.firstName;
    lastName = p.lastName;
}

void Person::operator=(const Person &p)
{
    firstName = p.firstName;
    lastName = p.lastName;
}

void Person::setFirstName(QString first)
{
    firstName = first;
}

void Person::setLastName(QString last)
{
    lastName = last;
}

QString Person::getFullName()
{
    return firstName + " " + lastName;
}



