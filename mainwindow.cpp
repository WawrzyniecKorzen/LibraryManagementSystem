
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userdatawidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent, DatabaseManager& database )
    :  QMainWindow(parent),
     ui(new Ui::MainWindow),
    mDb(DatabaseManager::instance()),
    user(new User)
{

    userWidget = new UserDataWidget(this, user);
    ui->setupUi(this);



    ui->centralwidget->layout()->addWidget(userWidget);

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
}





User *MainWindow::passUser()
{
    return user;
}



