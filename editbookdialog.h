#ifndef EDITBOOKDIALOG_H
#define EDITBOOKDIALOG_H

#include <QDialog>

#include "databasemanager.h"

namespace Ui {
class EditBookDialog;
}

class EditBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditBookDialog(QWidget *parent, DatabaseManager& database, Book* book, User* admin);
    ~EditBookDialog();

public slots:

    void onNewTitle();
    void onNewPublicationYear();
    void onNumberOfCopies();

    void onSave();
    void onClearChanges();
    void onCancel();


private:
    Ui::EditBookDialog *ui;
    DatabaseManager& mDatabase;
    Book* mBook;
    User* mAdmin;
};

#endif // EDITBOOKDIALOG_H
