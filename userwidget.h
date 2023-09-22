#ifndef USERWIDGET_H
#define USERWIDGET_H
#include "user.h"

#include <QWidget>

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr, User* user = nullptr);
    ~UserWidget();
    User *getUser();

private:
    Ui::UserWidget *ui;
    User* mUser;
};

#endif // USERWIDGET_H
