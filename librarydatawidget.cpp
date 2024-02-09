#include "librarydatawidget.h"
#include "ui_librarydatawidget.h"

#include "bookwidget.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QDebug>
#include <QPushButton>
#include <QSpacerItem>

libraryDataWidget::libraryDataWidget(QWidget *parent, DatabaseManager& database, User* user) :
    QWidget(parent),
    ui(new Ui::libraryDataWidget),
    mDatabase(database),
    mUser(user)
{
    ui->setupUi(this);

    stackedPanel = new QStackedWidget(this);

    tabBar = new QWidget(this);
    QHBoxLayout* tabLayout = new QHBoxLayout(tabBar);
    tabBar->setLayout(tabLayout);

    QPushButton* myBooks = new QPushButton(tabBar);
    myBooks->setText("My Books");
    myBooks->setCheckable(true);
    myBooks->setChecked(true);
    myBooks->setAutoExclusive(true);
    tabBar->layout()->addWidget(myBooks);

    QPushButton* mySearch = new QPushButton(tabBar);
    mySearch->setText("My Search");
    mySearch->setCheckable(true);
    mySearch->setAutoExclusive(true);
    tabBar->layout()->addWidget(mySearch);

    tabLayout->addStretch();


    QVBoxLayout* lay = qobject_cast<QVBoxLayout*>(this->layout());
    lay->insertWidget(0, tabBar);

    mLoans = new QWidget(this);
    mLoans->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    mLoans->setLayout(new QVBoxLayout(mLoans));



    QSpacerItem* spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    mLoans->layout()->addItem(spacer);

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    searchWidget = new SearchWidget(this, mDatabase, mUser);
    searchWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);



    stackedPanel->addWidget(mLoans);
    stackedPanel->addWidget(searchWidget);
    ui->scrollArea->setWidget(stackedPanel);

    QObject::connect(myBooks, &QPushButton::clicked, this, &libraryDataWidget::onMyBooks);
    QObject::connect(mySearch, &QPushButton::clicked, this, &libraryDataWidget::onMySearch);

    this->show();

}

libraryDataWidget::~libraryDataWidget()
{
    delete ui;
}


void libraryDataWidget::onMyBooks()
{
    stackedPanel->setCurrentWidget(mLoans);

}

void libraryDataWidget::onMySearch()
{
    stackedPanel->setCurrentWidget(searchWidget);
}
