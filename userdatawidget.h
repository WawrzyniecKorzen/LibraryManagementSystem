#ifndef USERDATAWIDGET_H
#define USERDATAWIDGET_H

#include <QWidget>
#include "user.h"


namespace Ui {
class UserDataWidget;
}

class UserDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserDataWidget(QWidget *parent = nullptr, User* us = nullptr);
    ~UserDataWidget();

    void setUser(User* us);
    void update();
    void logOut();

signals:
    void logOutClicked();

private slots:
    void on_changePassButton_clicked();

private:
    Ui::UserDataWidget *ui;

    User* user;

};

#endif // USERDATAWIDGET_H
