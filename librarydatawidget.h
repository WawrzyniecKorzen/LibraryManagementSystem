#ifndef LIBRARYDATAWIDGET_H
#define LIBRARYDATAWIDGET_H

#include <QWidget>
#include <memory>
#include <vector>
#include <QVBoxLayout>

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

private:
    Ui::libraryDataWidget *ui;
    DatabaseManager& mDatabase;
    std::vector<Book*> books;
    //QVBoxLayout* layout;
    QWidget* mWidget;
};

#endif // LIBRARYDATAWIDGET_H
