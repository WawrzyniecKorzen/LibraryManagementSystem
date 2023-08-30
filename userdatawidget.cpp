#include "userdatawidget.h"
#include "ui_userdatawidget.h"

#include "mainwindow.h"
#include <QDebug>

UserDataWidget::UserDataWidget(QWidget *parent, User* us) :
    QWidget(parent),
    ui(new Ui::UserDataWidget), user(us)
{
    ui->setupUi(this);


    qDebug() << "user widget created with id " << user->getId();
}

UserDataWidget::~UserDataWidget()
{
    delete ui;
}

void UserDataWidget::setUser(User *us)
{
    user = us;
}

void UserDataWidget::update()
{
    ui->nameLabel->setText(user->getName());

    this->repaint();
}
