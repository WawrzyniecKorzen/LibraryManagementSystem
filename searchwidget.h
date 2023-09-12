#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>

#include "databasemanager.h"
namespace Ui {
class SearchWidget;
}

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent, DatabaseManager& database);
    ~SearchWidget();

private:
    Ui::SearchWidget *ui;
    DatabaseManager& mDatabase;
};

#endif // SEARCHWIDGET_H
