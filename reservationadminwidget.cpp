#include "reservationadminwidget.h"
#include "ui_reservationadminwidget.h"

ReservationAdminWidget::ReservationAdminWidget(QWidget *parent, DatabaseManager& database) :
    QWidget(parent),
    ui(new Ui::ReservationAdminWidget), mDatabase(database)
{
    ui->setupUi(this);
}

ReservationAdminWidget::~ReservationAdminWidget()
{
    delete ui;
}
