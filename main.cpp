
#include "mainwindow.h"
#include "login.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login dialog;
    MainWindow w;
    if(dialog.exec() == QDialog::Accepted){

            //w.setUser(dialog.GetUser());
            w.show();

        }
    return a.exec();
        //else return 0;
}
