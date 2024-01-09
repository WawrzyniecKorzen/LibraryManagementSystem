
#ifndef LOAN_H
#define LOAN_H


#include <QDate>
#include <memory>

#include "user.h"
#include "book.h"


class Loan
{
public:
    Loan(int loanId = -1, int bookId = -1, int userId = -1, QDate date = QDate(0,0,0), std::shared_ptr<Book> book = nullptr, std::shared_ptr<User> user = nullptr);
    ~Loan();

    void setID(int loanId);
    void setBookID(int bookId);
    void setUserID(int userId);
    void setStartDate(QDate date);
    void setBook(std::shared_ptr<Book> book);
    void setUser(std::shared_ptr<User> user);

    int getID();
    int getBookID();
    int getUserID();
    std::shared_ptr<Book> getBook();
    std::shared_ptr<User> getUser();
    QDate getStartDate();

private:
    int id;
    int bookID;
    int userID;
    QDate loanStartDate;
    std::shared_ptr<Book> mBook;
    std::shared_ptr<User> mUser;
};


#endif // LOAN_H
