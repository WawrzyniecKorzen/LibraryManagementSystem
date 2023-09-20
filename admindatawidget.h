#ifndef ADMINDATAWIDGET_H
#define ADMINDATAWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QScrollArea>

#include "databasemanager.h"
#include "usersadminwidget.h"
#include "searchwidget.h"

namespace Ui {
class AdminDataWidget;
}



class AdminDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminDataWidget(QWidget *parent, DatabaseManager& database);
    ~AdminDataWidget();

    void setTabBar();
    void setToolBar();

    enum class WidgetMode {
        Users, Books
    };

    WidgetMode getMode();

public slots:
    void onUsers();
    void onBooks();

    void onAdd();
    void onAddUser();

private:
    Ui::AdminDataWidget *ui;
    DatabaseManager& mDatabase;
    QStackedWidget* stackedPanel;
    QWidget* tabBar;
    QWidget* toolBar;
    UsersAdminWidget* usersWidget;
    QScrollArea* scrollArea;
    SearchWidget* bookSearch;
    WidgetMode mode;
};

#endif // ADMINDATAWIDGET_H
