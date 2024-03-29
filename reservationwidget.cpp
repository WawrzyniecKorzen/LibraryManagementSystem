#include "reservationwidget.h"
#include "ui_reservationwidget.h"

ReservationWidget::ReservationWidget(QWidget *parent, std::shared_ptr<Reservation> reservation) :
    QWidget(parent),
    ui(new Ui::ReservationWidget),
    mReservation(reservation)
{
    ui->setupUi(this);
    ui->dateLabel->setText(mReservation->getDate().toString("dd.MM.yyyy"));
    ui->userNameLabel->setText(mReservation->getUser()->getName());
    ui->bookTitleLabel->setText(mReservation->getBook()->getTitle());
    ui->authorsLabel->setText(mReservation->getBook()->printAuthor());
}


ReservationWidget::~ReservationWidget()
{
    delete ui;
}

std::shared_ptr<Reservation> ReservationWidget::getReservation()
{
    return mReservation;
}
