#ifndef LOANWIDGET_H
#define LOANWIDGET_H

#include <QWidget>
#include <memory>
#include "loan.h"


namespace Ui {
class LoanWidget;
}

class LoanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoanWidget(QWidget *parent = nullptr, std::shared_ptr<Loan> loan = nullptr);
    ~LoanWidget();
    std::shared_ptr<Loan> getLoan();

private:
    Ui::LoanWidget *ui;
    std::shared_ptr<Loan> mLoan;
};

#endif // LOANWIDGET_H
