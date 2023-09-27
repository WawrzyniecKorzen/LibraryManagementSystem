
#include "book.h"




Book::Book(int id_num, QString booktitle, std::vector<Person> author, int publication, int noCopies) :
    id(id_num), title(booktitle), authors(author), publicationYear(publication), copies(noCopies)
{

}

Book::~Book()
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

void Book::setAuthor(Person author)
{
    authors.push_back(author);
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

QString Book::printAuthor()
{
    if (authors.size() == 1)
        return authors[0].getFullName();

    QString result;
    for (auto it = authors.begin(); it != authors.end() -1; it++)
    {
        result += (*it).getFullName();
        result += ", ";
    }
    result += (authors.end() -1)->getFullName();
    return result;
}

std::vector<Person> Book::getAuthors()
{
    return authors;
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
