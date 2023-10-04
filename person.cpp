
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

QString Person::getFirstName() const
{
    return firstName;
}

QString Person::getLastName() const
{
    return lastName;
}

QString Person::getFullName()
{
    return firstName + " " + lastName;
}

bool Person::isEqual(const Person person) const
{
    bool result = false;
    if (firstName == person.getFirstName() && lastName == person.getLastName())
        result = true;
    return result;
}



