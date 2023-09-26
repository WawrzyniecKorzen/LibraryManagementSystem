#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>

#include "databasemanager.h"
#include "user.h"

namespace Ui {
class EditUserDialog;
}

class EditUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserDialog(QWidget *parent, DatabaseManager& database, User* user, User* admin);
    ~EditUserDialog();

public slots:
    void onChangeLogin();
    void onChangePassowrd();

private:
    Ui::EditUserDialog *ui;
    DatabaseManager& mDatabase;
    User* mUser;
    User* mAdmin;
};

#endif // EDITUSERDIALOG_H
