#ifndef LIBRARYDATAWIDGET_H
#define LIBRARYDATAWIDGET_H

#include <QWidget>
#include <memory>
#include <vector>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "book.h"
#include "databasemanager.h"

namespace Ui {
class libraryDataWidget;
}

class libraryDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit libraryDataWidget(QWidget *parent, DatabaseManager& database);
    ~libraryDataWidget();

    void demo();

    void onMyBooks();
    void onMySearch();

private:
    Ui::libraryDataWidget *ui;
    DatabaseManager& mDatabase;
    std::vector<Book*> books;
    QStackedWidget* stackedPanel;
    QWidget* tabBar;
    QWidget* mWidget;
    QWidget* searchWidget;
};

#endif // LIBRARYDATAWIDGET_H
