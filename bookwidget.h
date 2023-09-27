#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include "book.h"
#include <QWidget>

namespace Ui {
class BookWidget;
}

class BookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookWidget(QWidget *parent = nullptr, Book* book = nullptr);
    ~BookWidget();

    Book* getBook();

private:
    Ui::BookWidget *ui;
    Book* mBook;
};

#endif // BOOKWIDGET_H
