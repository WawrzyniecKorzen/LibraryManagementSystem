#ifndef EDITBOOKDIALOG_H
#define EDITBOOKDIALOG_H

#include <QDialog>
#include <QHash>
#include <QListWidgetItem>


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

    void initializeAuthors();
    void setAuthors();

    QHash<QListWidgetItem*, Person> itemNameMap;

public slots:

    void onNewTitle();
    void onChangeAuthor();
    void onAddAuthor();
    void onRemoveAuthor();
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
    std::vector<Person>* mAuthors;
};

#endif // EDITBOOKDIALOG_H
