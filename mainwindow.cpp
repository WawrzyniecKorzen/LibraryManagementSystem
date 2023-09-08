
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userdatawidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent, DatabaseManager& database )
    :  QMainWindow(parent),
     ui(new Ui::MainWindow),
    mDb(DatabaseManager::instance()),
    user(new User)
{

    userWidget = new UserDataWidget(this, user);
    ui->setupUi(this);
    libraryWidget = new libraryDataWidget(this, mDb);
    //libraryWidget->setSizePolicy(QSizePolicy::Fixed, );
    userWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    libraryWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->centralwidget->layout()->addWidget(userWidget);
    ui->centralwidget->layout()->addWidget(libraryWidget);


    this->show();
    QObject::connect(userWidget, &UserDataWidget::logOutClicked, this, &MainWindow::logOut);
    qDebug() << "main window created with id " << user->getId();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete user;
    qDebug() << "main window destroyed ";
}

void MainWindow::logUser(QString name)
{
    user = mDb.userDao.getUserData(name);
    userWidget->setUser(user);
    userWidget->update();
    this->repaint();
}

void MainWindow::logOut()
{
    this->close();
    this->deleteLater();
}





User *MainWindow::passUser()
{
    return user;
}



