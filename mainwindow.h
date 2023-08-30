
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "databasemanager.h"
#include "userdatawidget.h"

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
    User* passUser();


private:
    Ui::MainWindow *ui;
    DatabaseManager& mDb;
    User* user;
    UserDataWidget* userWidget;
};

#endif // MAINWINDOW_H
