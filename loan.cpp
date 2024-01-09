
#include "loan.h"



Loan::Loan(int loanId, int bookId, int userId, QDate date, std::shared_ptr<Book> book, std::shared_ptr<User> user) :
    id(loanId), bookID(bookId), userID(userId), loanStartDate(date), mBook(book), mUser(user)
{

}

Loan::~Loan()
{

}

void Loan::setID(int loanId)
{
    id = loanId;
}

void Loan::setBookID(int bookId)
{
    bookID = bookId;
}

void Loan::setUserID(int userId)
{
    userID = userId;
}

void Loan::setStartDate(QDate date)
{
    loanStartDate = date;
}

void Loan::setBook(std::shared_ptr<Book> book)
{
    mBook = book;
}

void Loan::setUser(std::shared_ptr<User> user)
{
    mUser = user;
}

int Loan::getID()
{
    return id;
}

int Loan::getBookID()
{
    return bookID;
}

int Loan::getUserID()
{
    return userID;
}

std::shared_ptr<Book> Loan::getBook()
{
    return mBook;
}

std::shared_ptr<User> Loan::getUser()
{
    return mUser;
}

QDate Loan::getStartDate()
{
    return loanStartDate;
}
