#ifndef RESERVATIONADMINWIDGET_H
#define RESERVATIONADMINWIDGET_H

#include <QWidget>
#include <QMap>
#include <QRadioButton>
#include <QPushButton>
#include "reservationwidget.h"
#include "databasemanager.h"

namespace Ui {
class ReservationAdminWidget;
}

class ReservationAdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReservationAdminWidget(QWidget *parent, DatabaseManager& database);
    ~ReservationAdminWidget();

    std::vector<QPushButton*> acceptButtons;
    std::vector<QPushButton*> rejectButtons;
    QMap<QPushButton*, ReservationWidget*> reservationAcceptListMap;
    QMap<QPushButton*, ReservationWidget*> reservationRejectListMap;

    void initializeReservationListWidget();
    void addReservationWidget(std::shared_ptr<Reservation> reservation);
    void onGetReservations();
    void onAccept();
    void onReject();


private:
    Ui::ReservationAdminWidget *ui;
    DatabaseManager& mDatabase;
    QWidget* reservationListWidget;
    QPushButton* activeButton;
};

#endif // RESERVATIONADMINWIDGET_H
