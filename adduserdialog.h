#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include "databasemanager.h"

#include <QDialog>

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent, DatabaseManager& database);
    ~AddUserDialog();

private:
    Ui::AddUserDialog *ui;
    DatabaseManager& mDatabase;
};

#endif // ADDUSERDIALOG_H
