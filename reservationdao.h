
#ifndef RESERVATIONDAO_H
#define RESERVATIONDAO_H

#include <QSqlDatabase>
#include <memory>
#include <vector>

#include "reservation.h"
#include "bookdao.h"
#include "userdao.h"


class ReservationDao
{
public:
    ReservationDao(QSqlDatabase& database, std::shared_ptr<BookDao> bookDao, std::shared_ptr<UserDao> userDao);

    ~ReservationDao();

    void addReservation(Reservation reservation);
    void removeReservation(int reservationID);
    std::vector<std::shared_ptr<Reservation>> getReservations(int number = 5);
    bool checkReservation(int bookID, int userID);

private:
    QDate toQDate(QString date);
private:
    QSqlDatabase& mDatabase;
    std::shared_ptr<BookDao> mBookDao;
    std::shared_ptr<UserDao> mUserDao;
};

#endif // RESERVATIONDAO_H
