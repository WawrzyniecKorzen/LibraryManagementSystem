#ifndef LIBRARYDATAWIDGET_H
#define LIBRARYDATAWIDGET_H

#include <QWidget>

namespace Ui {
class libraryDataWidget;
}

class libraryDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit libraryDataWidget(QWidget *parent = nullptr);
    ~libraryDataWidget();

private:
    Ui::libraryDataWidget *ui;
};

#endif // LIBRARYDATAWIDGET_H
