
#ifndef BOOK_H
#define BOOK_H

#include "person.h"

#include <QString>
#include <vector>


class Book
{
public:
    Book(int id_num = -1, QString booktitle = "", std::vector<Person> author = std::vector<Person>(), int publication = -1, int noAvailable =-1, int noCopies = -1);
    Book(const Book &b);

    void operator=(const Book &b);
    ~Book();

    void setId(int id_num);
    void setTitle(QString booktitle);
    void setAuthor(Person author);
    void setAuthors(std::vector<Person> authorsList);
    void setPublicationYear(int publication);
    void setAvailable(int noAvailable);
    void setCopies(int noCopies);

    int getId();
    QString getTitle();
    QString printAuthor();
    std::vector<Person> getAuthors();
    int getPublicationYear();
    int getAvailable();
    int getCopies();

    void addCopy();
    bool subtractCopy();

    std::vector<Person> compareAuthors(Book& book);


private:
    int id;
    QString title;
    std::vector<Person> authors;
    int publicationYear;
    int available;
    int copies;
};

#endif // BOOK_H
