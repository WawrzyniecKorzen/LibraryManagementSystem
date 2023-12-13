#ifndef RESERVATIONWIDGET_H
#define RESERVATIONWIDGET_H

#include "reservation.h"

#include <QWidget>

namespace Ui {
class ReservationWidget;
}

class ReservationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReservationWidget(QWidget *parent = nullptr, std::shared_ptr<Reservation> reservation = nullptr);
    ~ReservationWidget();

private:
    Ui::ReservationWidget *ui;
    std::shared_ptr<Reservation> mReservation;
};

#endif // RESERVATIONWIDGET_H
