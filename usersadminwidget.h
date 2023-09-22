#ifndef USERSADMINWIDGET_H
#define USERSADMINWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QHash>

#include "databasemanager.h"
#include "userwidget.h"

namespace Ui {
class UsersAdminWidget;
}

class UsersAdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UsersAdminWidget(QWidget *parent, DatabaseManager& database);
    ~UsersAdminWidget();

    void setUserList();
    void addUserWidget(User *user);

    std::vector<QRadioButton*> widgetList;
    QHash<QRadioButton*, UserWidget*> userListMap;

public slots:
    void onSearchUser();

private:
    Ui::UsersAdminWidget *ui;
    DatabaseManager& mDatabase;
    QWidget* userList;

};

#endif // USERSADMINWIDGET_H
