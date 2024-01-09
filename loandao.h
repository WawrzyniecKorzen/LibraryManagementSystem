
#ifndef LOANDAO_H
#define LOANDAO_H


#include <QSqlDatabase>
#include <memory>
#include <vector>

#include "loan.h"
#include "bookdao.h"
#include "userdao.h"


class LoanDao
{
public:
    LoanDao(QSqlDatabase& database, std::shared_ptr<BookDao> bookDao, std::shared_ptr<UserDao> userDao);

    ~LoanDao();

    void addLoan(Loan loan);
    void removeLoan(int loanID);
    std::vector<std::shared_ptr<Loan>> getLoans(int number = 5);
    bool checkLoan(int bookID, int userID);

private:
    QDate toQDate(QString date);
private:
    QSqlDatabase& mDatabase;
    std::shared_ptr<BookDao> mBookDao;
    std::shared_ptr<UserDao> mUserDao;
};

#endif // LOANDAO_H
