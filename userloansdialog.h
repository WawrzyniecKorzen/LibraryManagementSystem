#ifndef USERLOANSDIALOG_H
#define USERLOANSDIALOG_H

#include <QDialog>
#include "databasemanager.h"
#include "loanwidget.h"

namespace Ui {
class UserLoansDialog;
}

class UserLoansDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserLoansDialog(DatabaseManager& database, QWidget *parent = nullptr, User* user = nullptr);
    ~UserLoansDialog();

    void initialiseBooks();
    void onReturnButton();
    void onCloseButton();
    QHash<QPushButton*, LoanWidget*> buttonLoanMap;

private:
    Ui::UserLoansDialog *ui;
    DatabaseManager& mDatabase;
    std::shared_ptr<User> mUser;
    QWidget* mLoansList;
};

#endif // USERLOANSDIALOG_H
