#include "userwidget.h"
#include "ui_userwidget.h"

UserWidget::UserWidget(QWidget *parent, User* user) :
    QWidget(parent),
    ui(new Ui::UserWidget), mUser(user)
{
    ui->setupUi(this);
    ui->userName->setText(mUser->getName());
    ui->joinedDate->setText(mUser->getJoined().toString(("dd.MM.yyyy")));
}

UserWidget::~UserWidget()
{
    delete ui;
}
