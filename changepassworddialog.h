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
    explicit ChangePasswordDialog(QWidget *parent = nullptr, User* us = nullptr);
    ~ChangePasswordDialog();


    void onChangeButton();
    void onClearButton();
    void onCancelButton();

private:
    Ui::ChangePasswordDialog *ui;
    DatabaseManager& mDb;
    User* user;
};

#endif // CHANGEPASSWORDDIALOG_H
