#ifndef CHANGELOGINDIALOG_H
#define CHANGELOGINDIALOG_H

#include "user.h"
#include "databasemanager.h"

#include <QDialog>

namespace Ui {
class ChangeLoginDialog;
}

class ChangeLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeLoginDialog(QWidget *parent, DatabaseManager& database, User* user);
    ~ChangeLoginDialog();

public slots:

    void onChange();
    void onCancel();

private:
    Ui::ChangeLoginDialog *ui;
    DatabaseManager& mDatabase;
    User* mUser;
};

#endif // CHANGELOGINDIALOG_H
