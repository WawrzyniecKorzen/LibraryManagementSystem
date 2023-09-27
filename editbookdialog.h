#ifndef EDITBOOKDIALOG_H
#define EDITBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class EditBookDialog;
}

class EditBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditBookDialog(QWidget *parent = nullptr);
    ~EditBookDialog();

private:
    Ui::EditBookDialog *ui;
};

#endif // EDITBOOKDIALOG_H
