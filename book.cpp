
#include "book.h"

#include <algorithm>


Book::Book(int id_num, QString booktitle, std::vector<Person> author, int publication, int noAvailable, int noCopies) :
    id(id_num), title(booktitle), authors(author), publicationYear(publication), available(noAvailable), copies(noCopies)
{

}

Book::Book(const Book &b)
{
    id = b.id;
    title = b.title;
    authors = b.authors;
    publicationYear = b.publicationYear;
    available = b.available;
    copies = b.copies;
}

void Book::operator=(const Book &b)
{
    id = b.id;
    title = b.title;
    authors = b.authors;
    publicationYear = b.publicationYear;
    available = b.available;
    copies = b.copies;
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

void Book::setAuthors(std::vector<Person> authorsList)
{
    authors = authorsList;
}





void Book::setPublicationYear(int publication)
{
    publicationYear = publication;
}

void Book::setAvailable(int noAvailable)
{
    available = noAvailable;
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

int Book::getAvailable()
{
    return available;
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
    if (available > 0)
    {
        available--;
        return true;
    }
    else
        return false;
}

std::vector<Person> Book::compareAuthors(Book& book)
{
    std::vector<Person> notMatchingAuthors = authors;


    for (Person& otherAuthor : book.getAuthors())
    {
        auto it = std::remove_if(notMatchingAuthors.begin(), notMatchingAuthors.end(), [otherAuthor](Person& person){return person.isEqual(otherAuthor);});
        notMatchingAuthors.erase(it, notMatchingAuthors.end());
    }

    return notMatchingAuthors;
}
