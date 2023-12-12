
#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDate>
#include <memory>

#include "user.h"
#include "book.h"


class Reservation
{
public:
    Reservation(int reservationId = -1, int bookId = -1, int userId = -1, QDate date = QDate(0,0,0), std::shared_ptr<Book> book = nullptr, std::shared_ptr<User> user = nullptr);
    ~Reservation();

    void setID(int reservationId);
    void setBookID(int bookId);
    void setUserID(int userId);
    void setDate(QDate date);
    void setBook(std::shared_ptr<Book> book);
    void setUser(std::shared_ptr<User> user);

    int getID();
    int getBookID();
    int getMemberID();
    std::shared_ptr<Book> getBook();
    std::shared_ptr<User> getUser();
    QDate getDate();

private:
    int id;
    int bookID;
    int memberID;
    QDate reservationDate;
    std::shared_ptr<Book> mBook;
    std::shared_ptr<User> mUser;
};

#endif // RESERVATION_H
