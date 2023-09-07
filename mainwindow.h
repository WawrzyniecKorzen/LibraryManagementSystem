
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include "user.h"
#include "databasemanager.h"
#include "userdatawidget.h"
#include "librarydatawidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow( QWidget *parent, DatabaseManager& database);
    ~MainWindow();

    void logUser(QString name);
    void logOut();

    User* passUser();


private:
    Ui::MainWindow *ui;
    DatabaseManager& mDb;
    User* user;
    UserDataWidget* userWidget;
    libraryDataWidget* libraryWidget;
    QScrollArea* scroll;
};

#endif // MAINWINDOW_H
