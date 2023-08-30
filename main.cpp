
#include "mainwindow.h"
#include "login.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/resources/book-icon.png"));

    Login dialog;
    dialog.show();


    return a.exec();

}
