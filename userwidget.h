#ifndef USERWIDGET_H
#define USERWIDGET_H
#include "user.h"

#include <QWidget>
#include <vector>


namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr, User* user = nullptr, std::vector<QString> titlesList = std::vector<QString>());
    ~UserWidget();
    User *getUser();
    void setTitlesList(std::vector<QString> titles);

private:
    Ui::UserWidget *ui;
    User* mUser;
    std::vector<QString> mTitlesList;
};

#endif // USERWIDGET_H
