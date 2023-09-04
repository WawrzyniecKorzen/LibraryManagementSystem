
#include "mainwindow.h"
#include "login.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/resources/book-icon.png"));

    Login *dialog = new Login();
    dialog->show();


    return a.exec();

}
