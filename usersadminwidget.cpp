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
    userList->setLayout(new QVBoxLayout());
    ui->verticalLayout->insertWidget(1,userList);

    widgetList.clear();
    userListMap.clear();
    manageBooksButtons.clear();
    manageBooksButtonsMap.clear();
}

void UsersAdminWidget::addUserWidget(User *user)
{
    std::vector<QString> titles = mDatabase.loanDao.getUsersBookTitles(user->getId());
    QHBoxLayout* layout = new QHBoxLayout(userList);
    QRadioButton* radio = new QRadioButton(userList);
    UserWidget* userWidget = new UserWidget(userList, user, titles);
    layout->addWidget(radio);
    layout->addWidget(userWidget);
    QVBoxLayout* listLayout = qobject_cast<QVBoxLayout*>(userList->layout());
    listLayout->addLayout(layout);

    widgetList.push_back(radio);
    userListMap.insert(radio, userWidget);

    QPushButton* manage = new QPushButton("Manage Users Books", userList);
    manageBooksButtons.push_back(manage);
    manageBooksButtonsMap.insert(manage, user);
    QHBoxLayout* buttonLayout = new QHBoxLayout(userList);
    buttonLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    buttonLayout->addWidget(manage);
    listLayout->addLayout(buttonLayout);
    QObject::connect(manage, &QPushButton::clicked, this, &UsersAdminWidget::onManageBooks);

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    listLayout->addWidget(line);

}

User *UsersAdminWidget::findPickedUser()
{

    if (widgetList.size() == 0)
    {
        qDebug() << "null pointer passed";
        return nullptr;
    }
    QRadioButton* radio = nullptr;
    for (QRadioButton* button : widgetList)
    {
        if (button->isChecked())
        {
            radio = button;
            break;
        }
    }

    if (radio == nullptr)
        return nullptr;
    return userListMap.value(radio)->getUser();
}

void UsersAdminWidget::removePickedUser()
{
    QRadioButton* radio = nullptr;
    int i;
    for (i = 0; i < widgetList.size(); i++)
    {
        if (widgetList[i]->isChecked())
        {
            radio = widgetList[i];

            break;
        }
    }

    if (radio == nullptr)
        return;
    widgetList.erase(widgetList.begin()+i);
    UserWidget* userWidget = userListMap.value(radio);
    userListMap.remove(radio);
    radio->hide();
    userWidget->hide();

    radio->deleteLater();
    userWidget->deleteLater();
}

void UsersAdminWidget::onManageBooks()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    User* user = manageBooksButtonsMap.value(button);
    UserLoansDialog* dialog = new UserLoansDialog(mDatabase, this, user);
    dialog->show();
}

void UsersAdminWidget::onSearchUser()
{
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
