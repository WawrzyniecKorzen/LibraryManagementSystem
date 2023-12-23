#include "reservationadminwidget.h"
#include "ui_reservationadminwidget.h"

ReservationAdminWidget::ReservationAdminWidget(QWidget *parent, DatabaseManager& database) :
    QWidget(parent),
    ui(new Ui::ReservationAdminWidget), mDatabase(database)
{
    ui->setupUi(this);
    initializeReservationListWidget();
    QObject::connect(ui->loadReservationsButton, &QPushButton::clicked, this, &ReservationAdminWidget::onGetReservations);
}

ReservationAdminWidget::~ReservationAdminWidget()
{
    delete ui;
    delete reservationListWidget;
}

void ReservationAdminWidget::initializeReservationListWidget()
{
    reservationListWidget = new QWidget(this);
    reservationListWidget->setLayout(new QVBoxLayout());
    ui->verticalLayout->insertWidget(1, reservationListWidget);
}

void ReservationAdminWidget::addReservationWidget(std::shared_ptr<Reservation> reservation)
{
    QHBoxLayout* layout = new QHBoxLayout(reservationListWidget);
    QRadioButton* radio = new QRadioButton(reservationListWidget);
    ReservationWidget* reservationWidget = new ReservationWidget(reservationListWidget, reservation);
    layout->addWidget(radio);
    layout->addWidget(reservationWidget);
    layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    QVBoxLayout* listLayout = qobject_cast<QVBoxLayout*>(reservationListWidget->layout());
    listLayout->addLayout(layout);

    widgetList.push_back(radio);
    reservationListMap.insert(radio, reservationWidget);
}

void ReservationAdminWidget::onGetReservations()
{
    qDebug() << "onGetReservations";
    delete reservationListWidget;
    initializeReservationListWidget();
    std::vector<std::shared_ptr<Reservation>> reservations = mDatabase.reservationDao.getReservations();
    qDebug() << "taken " << QString::number(reservations.size());
    for (std::shared_ptr<Reservation> &reservation : reservations)
    {
        addReservationWidget(reservation);
    }
    /*if ((*reservationsPtr).size() !=0)
    {
        QHBoxLayout* reserveLayout = new QHBoxLayout(reservationListWidget);
        reserveLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));

        reserveButton = new QPushButton("Reserve selected book", this);
        reserveLayout->addWidget(reserveButton);

        QVBoxLayout* listLayout = qobject_cast<QVBoxLayout*>(reservationListWidget->layout());
        listLayout->addLayout(reserveLayout);

        //QObject::connect(reserveButton, &QPushButton::clicked, this, &SearchWidget::onReserveButton);
    }*/
}
