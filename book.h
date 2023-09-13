
#ifndef BOOK_H
#define BOOK_H

#include "person.h"

#include <QString>
#include <vector>


class Book
{
public:
    Book(int id_num = -1, QString booktitle = "", std::vector<Person> author = std::vector<Person>(), int publication = -1, int noCopies = -1);
    ~Book();

    void setId(int id_num);
    void setTitle(QString booktitle);
    void setAuthor(Person author);
    void setPublicationYear(int publication);
    void setCopies(int noCopies);

    int getId();
    QString getTitle();
    QString getAuthor();
    int getPublicationYear();
    int getCopies();

    void addCopy();
    bool subtractCopy();


private:
    int id;
    QString title;
    std::vector<Person> authors;
    int publicationYear;
    int copies;
};

#endif // BOOK_H
