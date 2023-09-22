#include "usersadminwidget.h"
#include "ui_usersadminwidget.h"


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
    userList->setLayout(new QVBoxLayout(userList));
    ui->verticalLayout->insertWidget(1,userList);
}

void UsersAdminWidget::addUserWidget(User *user)
{
    QHBoxLayout* layout = new QHBoxLayout(userList);
    QRadioButton* radio = new QRadioButton(userList);
    UserWidget* userWidget = new UserWidget(userList, user);
    layout->addWidget(radio);
    layout->addWidget(userWidget);
    QVBoxLayout* listLayout = qobject_cast<QVBoxLayout*>(userList->layout());
    listLayout->addLayout(layout);

    widgetList.push_back(radio);
    userListMap.insert(radio, userWidget);
}

User *UsersAdminWidget::findPickedUser()
{
    QRadioButton* radio;
    for (QRadioButton* button : widgetList)
    {
        if (button->isChecked())
        {
            radio = button;
            break;
        }
    }

    return userListMap.value(radio)->getUser();
}

void UsersAdminWidget::removePickedUser()
{
    QRadioButton* radio;
    int i;
    for (i = 0; i < widgetList.size(); i++)
    {
        if (widgetList[i]->isChecked())
        {
            radio = widgetList[i];

            break;
        }
    }
    widgetList.erase(widgetList.begin()+i);
    UserWidget* userWidget = userListMap.value(radio);
    userListMap.remove(radio);
    radio->hide();
    userWidget->hide();

    radio->deleteLater();
    userWidget->deleteLater();
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

    widgetList.clear();
    userListMap.clear();

    setUserList();

    for (QString& userName : users)
    {
        qDebug() << "found user: " << userName;
        User* user = mDatabase.userDao.getUserData(userName);
        addUserWidget(user);

    }
}
