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
    explicit EditUserDialog(QWidget *parent, DatabaseManager& database, User* user);
    ~EditUserDialog();

private:
    Ui::EditUserDialog *ui;
    DatabaseManager& mDatabase;
    User* mUser;
};

#endif // EDITUSERDIALOG_H
