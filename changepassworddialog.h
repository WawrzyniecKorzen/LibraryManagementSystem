#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>
#include "databasemanager.h"
#include "user.h"

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(QWidget *parent, User* user, User* logged);
    ~ChangePasswordDialog();


    void onChangeButton();
    void onClearButton();
    void onCancelButton();
    void setAdminMode();

private:
    Ui::ChangePasswordDialog *ui;
    DatabaseManager& mDatabase;
    User* mUser;
    User *mLoggedUser;
};

#endif // CHANGEPASSWORDDIALOG_H
