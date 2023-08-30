
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userdatawidget.h"

#include <QDebug>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent, DatabaseManager& database )
    :  QMainWindow(parent),
     ui(new Ui::MainWindow),
    mDb(DatabaseManager::instance()),
    user(new User)
{

    userWidget = new UserDataWidget(this, user);
    ui->setupUi(this);



    ui->centralwidget->layout()->addWidget(userWidget);
    qDebug() << "main window created with id " << user->getId();
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
    this->repaint();
}

User *MainWindow::passUser()
{
    return user;
}



