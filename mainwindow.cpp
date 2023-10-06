
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userdatawidget.h"


#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    :  QMainWindow(parent),
     ui(new Ui::MainWindow),
    mDb(DatabaseManager::instance()),
    user(new User)
{

    userWidget = new UserDataWidget(this, user);
    ui->setupUi(this);
    this->setWindowTitle("The Library");

    userWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    ui->centralwidget->layout()->addWidget(userWidget);


    this->show();
    QObject::connect(userWidget, &UserDataWidget::logOutClicked, this, &MainWindow::logOut);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete user;
}

void MainWindow::logUser(QString name)
{
    user = mDb.userDao.getUserData(name);
    userWidget->setUser(user);
    userWidget->update();

    if (user->getStatus()==AccountType::Member)
        setMemberAccount();
    else if (user->getStatus()==AccountType::Admin)
        setAdminAccount();
    this->repaint();
}

void MainWindow::logOut()
{
    this->close();
    this->deleteLater();
}

void MainWindow::setMemberAccount()
{
    libraryWidget = new libraryDataWidget(this, mDb);
    //libraryWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->centralwidget->layout()->addWidget(libraryWidget);
}

void MainWindow::setAdminAccount()
{
    adminWidget = new AdminDataWidget(this, mDb, user);
    ui->centralwidget->layout()->addWidget(adminWidget);
}





User *MainWindow::passUser()
{
    return user;
}



