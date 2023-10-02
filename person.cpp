
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

QString Person::getFirstName()
{
    return firstName;
}

QString Person::getLastName()
{
    return lastName;
}

QString Person::getFullName()
{
    return firstName + " " + lastName;
}

bool Person::isEqual(Person &person)
{
    bool result = false;
    if (firstName == person.getFirstName() && lastName == person.getLastName())
        result = true;
    return result;
}



