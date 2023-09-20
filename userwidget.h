#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>

namespace Ui {
class userWidget;
}

class userWidget : public QWidget
{
    Q_OBJECT

public:
    explicit userWidget(QWidget *parent = nullptr);
    ~userWidget();

private:
    Ui::userWidget *ui;
};

#endif // USERWIDGET_H
