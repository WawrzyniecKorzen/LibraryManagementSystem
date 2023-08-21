#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
class DatabaseManager;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:


    void on_clearButton_clicked();

    void on_singInButton_clicked();



private:
    Ui::Login *ui;
    DatabaseManager& mDb;
};

#endif // LOGIN_H
