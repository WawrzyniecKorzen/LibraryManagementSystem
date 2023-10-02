
#ifndef PERSON_H
#define PERSON_H


#include <QString>


class Person
{
public:
    Person(QString first = "", QString last = "");
    Person(const Person &p);

    void operator=(const Person &p);

    void setFirstName(QString first);
    void setLastName(QString last);
    QString getFirstName();
    QString getLastName();

    QString getFullName();
    bool isEqual(Person &person);

private:
    QString firstName;
    QString lastName;
};

#endif // PERSON_H
