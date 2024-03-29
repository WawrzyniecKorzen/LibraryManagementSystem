#ifndef LIBRARYDATAWIDGET_H
#define LIBRARYDATAWIDGET_H

#include <QWidget>
#include <memory>
#include <vector>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "user.h"
#include "book.h"
#include "databasemanager.h"
#include "searchwidget.h"


namespace Ui {
class libraryDataWidget;
}

class libraryDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit libraryDataWidget(QWidget *parent, DatabaseManager& database, User* user);
    ~libraryDataWidget();

    void setLoans();

    void onMyBooks();
    void onMySearch();

private:
    Ui::libraryDataWidget *ui;
    DatabaseManager& mDatabase;
    std::vector<std::shared_ptr<Loan>> loansVector;
    QStackedWidget* stackedPanel;
    QWidget* tabBar;
    QWidget* mLoans;
    SearchWidget* searchWidget;
    User* mUser;
};

#endif // LIBRARYDATAWIDGET_H
