#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <vector>

#include "databasemanager.h"
#include "bookwidget.h"

namespace Ui {
class SearchWidget;
}

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent, DatabaseManager& database);
    ~SearchWidget();

    void onSearchButton();
    void onTitleRadio();
    void onAuthorRadio();
    void setBookList();

private:
    Ui::SearchWidget *ui;
    DatabaseManager& mDatabase;
    QWidget* bookList;
};

#endif // SEARCHWIDGET_H
