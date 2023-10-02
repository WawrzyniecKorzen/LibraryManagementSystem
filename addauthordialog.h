#ifndef ADDAUTHORDIALOG_H
#define ADDAUTHORDIALOG_H

#include <QDialog>
#include <vector>
#include "person.h"
#include "databasemanager.h"


namespace Ui {
class AddAuthorDialog;
}

class AddAuthorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAuthorDialog(QWidget *parent, DatabaseManager& database, std::vector<Person>* authors);
    ~AddAuthorDialog();

public slots:
    void onAdd();
    void onClear();
    void onCancel();


private:
    Ui::AddAuthorDialog *ui;
    DatabaseManager& mDatabase;
    std::vector<Person>* mAuthors;
    Person* mAuthor;
};

#endif // ADDAUTHORDIALOG_H
