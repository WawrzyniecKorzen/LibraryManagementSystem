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

    std::vector<QRadioButton*> widgetList;
    QMap<QRadioButton*, ReservationWidget*> reservationListMap;

    void initializeReservationListWidget();
    void addReservationWidget(std::shared_ptr<Reservation> reservation);
    void onGetReservations();


private:
    Ui::ReservationAdminWidget *ui;
    DatabaseManager& mDatabase;
    QWidget* reservationListWidget;
    QPushButton* reserveButton;
};

#endif // RESERVATIONADMINWIDGET_H
