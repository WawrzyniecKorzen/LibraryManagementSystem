
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "databasemanager.h"


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
    void setLabels();

private:
    Ui::MainWindow *ui;
    DatabaseManager& mDb;
    User* user;
};

#endif // MAINWINDOW_H
