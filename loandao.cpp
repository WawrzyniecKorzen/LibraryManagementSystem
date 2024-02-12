
#include "loandao.h"
#include "databasemanager.h"
#include <QSqlQuery>



LoanDao::LoanDao(QSqlDatabase &database, std::shared_ptr<BookDao> bookDao, std::shared_ptr<UserDao> userDao) :
    mDatabase(database), mBookDao(bookDao), mUserDao(userDao)
{

}

LoanDao::~LoanDao()
{

}

void LoanDao::addLoan(Loan loan)
{
    if (!checkLoan(loan.getBookID(), loan.getUserID()))
    {
        QSqlQuery query(mDatabase);
        query.exec("INSERT INTO loan (bookID, userID, loanStartDate) "
                   "VALUES (" + QString::number(loan.getBookID()) + ", " + QString::number(loan.getUserID()) + ", '"
                   + loan.getStartDate().toString("dd.MM.yyyy") + "')");
        DatabaseManager::debugQuery(query);
    }
}

void LoanDao::removeLoan(int loanID)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT bookID FROM loan WHERE id = " + QString::number(loanID));
    query.next();
    int bookID = query.value("bookID").toInt();
    query.prepare("DELETE FROM loan WHERE id = (:id)");
    query.bindValue(":id", loanID);
    query.exec();
    mBookDao->returnBook(bookID);
}

std::vector<std::shared_ptr<Loan> >  LoanDao::getLoans(int number)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT * FROM loan LIMIT " + QString::number(number) + ";");
    std::vector<std::shared_ptr<Loan>> loansVector;
    while(query.next())
    {
        std::shared_ptr<Loan> loanPtr = std::make_shared<Loan>(Loan());
        loanPtr->setID(query.value("id").toInt());
        loanPtr->setBookID(query.value("bookID").toInt());
        loanPtr->setUserID(query.value("userID").toInt());
        loanPtr->setStartDate(QDate::fromString(query.value("loanStartDate").toString(),"dd.MM.yyyy"));
        loansVector.push_back(loanPtr);
    }
    qDebug() << QString::number(loansVector[0]->getBookID());
    for (std::shared_ptr<Loan> loan : loansVector)
        loan->setBook(mBookDao->getBookDataId(loan->getBookID()));
    qDebug() << "books iterated";
    for (std::shared_ptr<Loan> loan : loansVector)
        loan->setUser((mUserDao->getUserDataId(loan->getUserID())));
    qDebug() << "users iterated";

    return loansVector;
}

std::vector<std::shared_ptr<Loan> > LoanDao::getUsersLoans(int id)
{
    QSqlQuery query(mDatabase);
    std::vector<std::shared_ptr<Loan> > loansVector;
    query.exec("SELECT * FROM loan WHERE userID = " + QString::number(id) +";");
    while (query.next())
    {
        std::shared_ptr<Loan> loanPtr = std::make_shared<Loan>(Loan());
        loanPtr->setID(query.value("id").toInt());
        loanPtr->setBookID(query.value("bookID").toInt());
        loanPtr->setUserID(query.value("userID").toInt());
        loanPtr->setStartDate(QDate::fromString(query.value("loanStartDate").toString(),"dd.MM.yyyy"));
        loansVector.push_back(loanPtr);
    }
    for (std::shared_ptr<Loan> loan : loansVector)
        loan->setBook(mBookDao->getBookDataId(loan->getBookID()));

    for (std::shared_ptr<Loan> loan : loansVector)
        loan->setUser((mUserDao->getUserDataId(loan->getUserID())));

    return loansVector;
}

bool LoanDao::checkLoan(int bookID, int userID)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT EXISTS(SELECT * from loan WHERE (bookID = " + QString::number(bookID) +
               " AND userID = " + QString::number(userID) + "))");
    query.next();
    return query.value(0).toInt();
}

std::vector<QString> LoanDao::getUsersBookTitles(int userID)
{
    std::vector<QString> titlesVector;
    QSqlQuery query(mDatabase);
    query.exec("SELECT title FROM loan INNER JOIN book ON loan.bookID=book.id WHERE userID = " + QString::number(userID) + ";");

    while (query.next())
    {
        titlesVector.push_back(query.value("title").toString());
    }
    return titlesVector;
}





