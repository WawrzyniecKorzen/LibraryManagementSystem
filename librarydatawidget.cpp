#include "librarydatawidget.h"
#include "ui_librarydatawidget.h"

libraryDataWidget::libraryDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::libraryDataWidget)
{
    ui->setupUi(this);
}

libraryDataWidget::~libraryDataWidget()
{
    delete ui;
}
