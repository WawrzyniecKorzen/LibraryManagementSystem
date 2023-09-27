#ifndef ADMINDATAWIDGET_H
#define ADMINDATAWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QScrollArea>
#include <vector>
#include <QRadioButton>
#include <QHash>

#include "databasemanager.h"
#include "usersadminwidget.h"
#include "searchwidget.h"
#include "userwidget.h"

namespace Ui {
class AdminDataWidget;
}



class AdminDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminDataWidget(QWidget *parent, DatabaseManager& database, User* user);
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
    void onAddBook();

    void onEdit();
    void onEditUser();

    void onRemove();
    void onRemoveUser();

private:
    Ui::AdminDataWidget *ui;
    DatabaseManager& mDatabase;
    User* mAdmin;
    QStackedWidget* stackedPanel;
    QWidget* tabBar;
    QWidget* toolBar;
    UsersAdminWidget* usersWidget;
    QScrollArea* scrollArea;
    SearchWidget* bookSearch;
    WidgetMode mode;
};

#endif // ADMINDATAWIDGET_H
