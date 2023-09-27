#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <vector>

#include "databasemanager.h"
#include "person.h"
#include "book.h"


namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent, DatabaseManager& database);
    ~AddBookDialog();

    void setAuthorList();
    bool isInputEmpty();

public slots:
    void onAddAuthor();
    void onAddBook();
    void onClear();
    void onCancel();

private:
    Ui::AddBookDialog *ui;
    DatabaseManager& mDatabase;
    std::vector<Person> authorList;
};

#endif // ADDBOOKDIALOG_H
