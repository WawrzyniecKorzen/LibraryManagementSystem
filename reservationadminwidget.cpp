#include "reservationadminwidget.h"
#include "ui_reservationadminwidget.h"
#include <QMessageBox>

ReservationAdminWidget::ReservationAdminWidget(QWidget *parent, DatabaseManager& database) :
    QWidget(parent),
    ui(new Ui::ReservationAdminWidget), mDatabase(database)
{
    ui->setupUi(this);
    initializeReservationListWidget();
    QObject::connect(ui->loadReservationsButton, &QPushButton::clicked, this, &ReservationAdminWidget::onGetReservations);
    onGetReservations();
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
    acceptButtons.clear();
    rejectButtons.clear();
    reservationAcceptListMap.clear();
    reservationRejectListMap.clear();
}

void ReservationAdminWidget::addReservationWidget(std::shared_ptr<Reservation> reservation)
{
    QHBoxLayout* layout = new QHBoxLayout(reservationListWidget);
    QPushButton* accept = new QPushButton("Accept", reservationListWidget);
    QPushButton* reject = new QPushButton("Reject", reservationListWidget);
    ReservationWidget* reservationWidget = new ReservationWidget(reservationListWidget, reservation);

    layout->addWidget(reservationWidget);
    layout->addWidget(accept);
    layout->addWidget(reject);
    layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    QVBoxLayout* listLayout = qobject_cast<QVBoxLayout*>(reservationListWidget->layout());
    listLayout->addLayout(layout);

    acceptButtons.push_back(accept);
    rejectButtons.push_back(reject);
    reservationAcceptListMap.insert(accept, reservationWidget);
    reservationRejectListMap.insert(reject, reservationWidget);

    QObject::connect(accept, &QPushButton::clicked, this, &ReservationAdminWidget::onAccept);
    QObject::connect(reject, &QPushButton::clicked, this, &ReservationAdminWidget::onReject);
}

void ReservationAdminWidget::onGetReservations()
{
    delete reservationListWidget;
    initializeReservationListWidget();
    mDatabase.reservationDao.getReservations();
    std::vector<std::shared_ptr<Reservation>> reservations = mDatabase.reservationDao.getReservations();
    for (std::shared_ptr<Reservation> &reservation : reservations)
    {
        addReservationWidget(reservation);
    }
}

void ReservationAdminWidget::onAccept()
{
    QPushButton* button = (QPushButton*)QObject::sender();
    std::shared_ptr<Reservation> reservation = reservationAcceptListMap.value(button)->getReservation();
    QString message = "Are you shure to accept reservation of book \"" + reservation->getBook()->getTitle() + "\" requested by user"
                      " " + reservation->getUser()->getName() + "?\nIf accepted the book will be loaned.";
    if (QMessageBox::warning(this, "Accept clicked", message, QMessageBox::Ok, QMessageBox::No) == QMessageBox::Ok)
    {
        Loan loan;
        loan.setUserID(reservation->getUserID());
        loan.setBookID(reservation->getBookID());
        loan.setStartDate(QDate::currentDate());
        mDatabase.loanDao.addLoan(loan);
        mDatabase.reservationDao.removeReservation(reservation->getID(), 0);
        onGetReservations();
    }
}

void ReservationAdminWidget::onReject()
{
    QPushButton* button = (QPushButton*)QObject::sender();
    std::shared_ptr<Reservation> reservation = reservationRejectListMap.value(button)->getReservation();

    QString message = "Are you shure to reject reservation of book \"" + reservation->getBook()->getTitle() + "\" requested by user"
        " " + reservation->getUser()->getName() + "?\nIf accepted the reservation will be deleted.";
   if (QMessageBox::warning(this, "Reject clicked", message, QMessageBox::Ok, QMessageBox::No) == QMessageBox::Ok)
    {
        mDatabase.reservationDao.removeReservation(reservation->getID());
        onGetReservations();
    }
}
