#ifndef RESERVATIONADMINWIDGET_H
#define RESERVATIONADMINWIDGET_H

#include <QWidget>
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

private:
    Ui::ReservationAdminWidget *ui;
    DatabaseManager& mDatabase;
};

#endif // RESERVATIONADMINWIDGET_H
