#ifndef USERLOANSDIALOG_H
#define USERLOANSDIALOG_H

#include <QDialog>

namespace Ui {
class UserLoansDialog;
}

class UserLoansDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserLoansDialog(QWidget *parent = nullptr);
    ~UserLoansDialog();

    void onCloseButton();

private:
    Ui::UserLoansDialog *ui;
};

#endif // USERLOANSDIALOG_H
