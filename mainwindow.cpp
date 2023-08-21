
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent, DatabaseManager& database )
    :  QMainWindow(parent),
     ui(new Ui::MainWindow),
    mDb(DatabaseManager::instance()),
    user(new User)
{


    ui->setupUi(this);

    setLabels();

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
}

void MainWindow::setLabels()
{
    ui->idLabel->setText(QString("Id: %1").arg(user->getId()));
    ui->nameLabel->setText("Name: " + user->getName());
    ui->statusLabel->setText(QString("Status: %1").arg(user->getStatus()));
}


