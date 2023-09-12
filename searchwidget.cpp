#include "searchwidget.h"
#include "ui_searchwidget.h"

SearchWidget::SearchWidget(QWidget *parent, DatabaseManager& database) :
    QWidget(parent),
    ui(new Ui::SearchWidget),
    mDatabase(database)
{
    ui->setupUi(this);
}

SearchWidget::~SearchWidget()
{
    delete ui;
}
