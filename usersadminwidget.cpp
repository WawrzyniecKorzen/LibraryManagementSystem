#include "usersadminwidget.h"
#include "ui_usersadminwidget.h"

#include <QPushButton>
#include <vector>
#include <QDebug>

UsersAdminWidget::UsersAdminWidget(QWidget *parent, DatabaseManager& database) :
    QWidget(parent),
    ui(new Ui::UsersAdminWidget), mDatabase(database)
{
    ui->setupUi(this);

    QObject::connect(ui->searchUserButton, &QPushButton::clicked, this, &UsersAdminWidget::onSearchUser);

}

UsersAdminWidget::~UsersAdminWidget()
{
    delete ui;
}

void UsersAdminWidget::onSearchUser()
{
    qDebug() << "search button clicked with username: " << ui->userNameEdit->text();
    if (ui->userNameEdit->text().isEmpty())
        return;
    std::vector<QString> users;
    users = mDatabase.findUserName(ui->userNameEdit->text());
    ui->userNameEdit->clear();
}
