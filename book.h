
#ifndef BOOK_H
#define BOOK_H


#include <QString>


class Book
{
public:
    Book(int id_num = -1, QString booktitle = "", QString first = "", QString last = "", int publication = -1, int noCopies = -1);
    ~Book();

    void setId(int id_num);
    void setTitle(QString booktitle);
    void setAuthorFirstName(QString first);
    void setAuthorLastName(QString last);
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
    QString authorFirstName;
    QString authorLastName;
    int publicationYear;
    int copies;
};

#endif // BOOK_H
