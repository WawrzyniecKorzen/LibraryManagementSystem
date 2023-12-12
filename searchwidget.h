#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QHash>
#include <vector>

#include "databasemanager.h"
#include "user.h"
#include "bookwidget.h"

namespace Ui {
class SearchWidget;
}

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent, DatabaseManager& database, User* user);
    ~SearchWidget();

    std::vector<QRadioButton*> widgetList;
    QHash<QRadioButton*, BookWidget*> bookListMap;

    void onSearchButton();
    void onTitleRadio();
    void onAuthorRadio();
    void onReserveButton();
    void setBookList();

    void addBookWidget(Book* book);

    Book* findPickedBook();
    void removePickedBook();
    void reserveBook(Book* book);

private:
    Ui::SearchWidget *ui;
    DatabaseManager& mDatabase;
    User* mUser;
    QWidget* bookList;
    QPushButton* reserveButton;
};

#endif // SEARCHWIDGET_H
