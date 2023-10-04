#ifndef CHANGEAUTHORDIALOG_H
#define CHANGEAUTHORDIALOG_H

#include <QDialog>

#include "person.h"

namespace Ui {
class ChangeAuthorDialog;
}

class ChangeAuthorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeAuthorDialog(QWidget *parent, Person author);
    ~ChangeAuthorDialog();

public slots:
    void onSaveChanges();
    void onClear();
    void onCancel();

private:
    Ui::ChangeAuthorDialog *ui;
    Person mAuthor;
};

#endif // CHANGEAUTHORDIALOG_H
