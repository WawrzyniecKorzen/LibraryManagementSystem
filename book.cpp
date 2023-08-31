
#include "book.h"







Book::Book(int id_num, QString booktitle, QString authorName, int publication, int noCopies) :
    id(id_num), title(booktitle), author(authorName), publicationYear(publication), copies(noCopies)
{

}

void Book::setId(int id_num)
{
    id = id_num;
}

void Book::setTitle(QString booktitle)
{
    title = booktitle;
}

void Book::setAuthor(QString authorName)
{
    author = authorName;
}

void Book::setPublicationYear(int publication)
{
    publicationYear = publication;
}

void Book::setCopies(int noCopies)
{
    copies = noCopies;
}

int Book::getId()
{
    return id;
}

QString Book::getTitle()
{
    return title;
}

QString Book::getAuthor()
{
    return author;
}

int Book::getPublicationYear()
{
    return publicationYear;
}

int Book::getCopies()
{
    return copies;
}

void Book::addCopy()
{
    copies++;
}

bool Book::subtractCopy()
{
    if (copies > 0)
    {
        copies--;
        return true;
    }
    else
        return false;
}
