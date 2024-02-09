#include "userwidget.h"
#include "ui_userwidget.h"

UserWidget::UserWidget(QWidget *parent, User* user, std::vector<QString> titlesList) :
    QWidget(parent),
    ui(new Ui::UserWidget), mUser(user), mTitlesList(titlesList)
{
    ui->setupUi(this);
    ui->userName->setText(mUser->getName());
    ui->joinedDate->setText(mUser->getJoined().toString(("dd.MM.yyyy")));
    QString titles;
    for (QString title : mTitlesList)
    {
        titles += title;
        titles += "\n";
    }
    ui->booksListLabel->setText(titles);
}

UserWidget::~UserWidget()
{
    delete ui;
}

User *UserWidget::getUser()
{
    return mUser;
}

void UserWidget::setTitlesList(std::vector<QString> titles)
{
    mTitlesList = titles;
}
