#include "userwidget.h"
#include "ui_userwidget.h"

userWidget::userWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userWidget)
{
    ui->setupUi(this);
}

userWidget::~userWidget()
{
    delete ui;
}
