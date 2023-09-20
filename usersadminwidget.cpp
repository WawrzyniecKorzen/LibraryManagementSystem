#include "usersadminwidget.h"
#include "ui_usersadminwidget.h"
#include "userwidget.h"

#include <QPushButton>
#include <vector>
#include <QDebug>
#include <QVBoxLayout>

UsersAdminWidget::UsersAdminWidget(QWidget *parent, DatabaseManager& database) :
    QWidget(parent),
    ui(new Ui::UsersAdminWidget), mDatabase(database)
{
    ui->setupUi(this);
    setUserList();

    QObject::connect(ui->searchUserButton, &QPushButton::clicked, this, &UsersAdminWidget::onSearchUser);

}

UsersAdminWidget::~UsersAdminWidget()
{
    delete ui;
}

void UsersAdminWidget::setUserList()
{
    userList = new QWidget(this);
    userList->setLayout(new QVBoxLayout());
    ui->verticalLayout->insertWidget(1,userList);
}

void UsersAdminWidget::onSearchUser()
{
    qDebug() << "search button clicked with username: " << ui->userNameEdit->text();
    if (ui->userNameEdit->text().isEmpty())
        return;
    std::vector<QString> users;
    users = mDatabase.userDao.getUserNames(ui->userNameEdit->text());
    ui->userNameEdit->clear();
    delete userList;

    setUserList();

    for (QString& userName : users)
    {
        qDebug() << "found user: " << userName;
        User* user = mDatabase.userDao.getUserData(userName);
        UserWidget* userWidget = new UserWidget(userList, user);
        userList->layout()->addWidget(userWidget);
    }
}
