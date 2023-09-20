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

public slots:
    void onAddUser();
    void onClear();
    void onCancel();
    void onGenerate();

private:
    Ui::AddUserDialog *ui;
    DatabaseManager& mDatabase;
};



#endif // ADDUSERDIALOG_H
