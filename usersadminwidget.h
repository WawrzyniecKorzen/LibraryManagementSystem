#ifndef USERSADMINWIDGET_H
#define USERSADMINWIDGET_H

#include <QWidget>

#include "databasemanager.h"

namespace Ui {
class UsersAdminWidget;
}

class UsersAdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UsersAdminWidget(QWidget *parent, DatabaseManager& database);
    ~UsersAdminWidget();

public slots:
    void onSearchUser();

private:
    Ui::UsersAdminWidget *ui;
    DatabaseManager& mDatabase;
    QWidget* tabBar;
};

#endif // USERSADMINWIDGET_H
