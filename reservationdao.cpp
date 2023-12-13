
#include "reservationdao.h"
#include "databasemanager.h"
#include <QSqlQuery>



ReservationDao::ReservationDao(QSqlDatabase &database, std::shared_ptr<BookDao> bookDao, std::shared_ptr<UserDao> userDao) :
    mDatabase(database), mBookDao(bookDao), mUserDao(userDao)
{

}

ReservationDao::~ReservationDao()
{

}

void ReservationDao::addReservation(Reservation reservation)
{
    if (!checkReservation(reservation.getBookID(), reservation.getUserID()))
    {
        QSqlQuery query(mDatabase);
        query.exec("INSERT INTO reservation (bookID, userID, reservationDate) "
               "VALUES (" + QString::number(reservation.getBook()->getId()) + ", " + QString::number(reservation.getUser()->getId()) + ", '"
               + reservation.getDate().toString("dd.MM.yyyy") + "')");
        DatabaseManager::debugQuery(query);
        mBookDao->reserveBook(reservation.getBookID());
    }
}

std::unique_ptr<std::vector<std::shared_ptr<Reservation> > > ReservationDao::getReservations(int number)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT * FROM reservation LIMIT " + QString::number(number) + ";");

    std::vector<std::shared_ptr<Reservation>> reservationsVector;
    while(query.next())
    {
        std::shared_ptr<Reservation> reservationPtr = std::make_shared<Reservation>(Reservation());
        reservationPtr->setID(query.value("id").toInt());
        reservationPtr->setBookID(query.value("bookID").toInt());
        reservationPtr->setUserID(query.value("userID").toInt());

        reservationPtr->setBook(mBookDao->getBookDataId(reservationPtr->getBookID()));
        reservationPtr->setUser(mUserDao->getUserDataId(reservationPtr->getUserID()));
        reservationsVector.push_back(reservationPtr);
    }
    return std::make_unique<std::vector<std::shared_ptr<Reservation>>>(reservationsVector);



}

bool ReservationDao::checkReservation(int bookID, int userID)
{
    QSqlQuery query(mDatabase);
    query.exec("SELECT EXISTS(SELECT * from reservation WHERE (bookID = " + QString::number(bookID) +
               " AND userID = " + QString::number(userID) + "))");
    query.next();
    return query.value(0).toInt();
}



