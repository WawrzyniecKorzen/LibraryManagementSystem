
#include "reservation.h"
#include <QDate>


Reservation::Reservation(int reservationId, int bookId, int userId, QDate date, std::shared_ptr<Book> book, std::shared_ptr<User> user) :
    id(reservationId),
    bookID(bookId),
    memberID(userId),
    reservationDate(date),
    mBook(book),
    mUser(user)
{

}

Reservation::~Reservation()
{

}

void Reservation::setID(int reservationId)
{
    id = reservationId;
}

void Reservation::setBookID(int bookId)
{
    bookID = bookId;
}

void Reservation::setUserID(int userId)
{
    memberID = userId;
}

void Reservation::setDate(QDate date)
{
    reservationDate = date;
}

void Reservation::setBook(std::shared_ptr<Book> book)
{
    mBook = book;
}

void Reservation::setUser(std::shared_ptr<User> user)
{
    mUser = user;
}

int Reservation::getID()
{
    return id;
}

int Reservation::getBookID()
{
    return bookID;
}

int Reservation::getMemberID()
{
    return memberID;
}

std::shared_ptr<Book> Reservation::getBook()
{
    return mBook;
}

std::shared_ptr<User> Reservation::getUser()
{
    return mUser;
}

QDate Reservation::getDate()
{
    return reservationDate;
}

