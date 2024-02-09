#include "loanwidget.h"
#include "ui_loanwidget.h"

LoanWidget::LoanWidget(QWidget *parent,  std::shared_ptr<Loan> loan) :
    QWidget(parent),
    ui(new Ui::LoanWidget),
    mLoan(loan)
{
    ui->setupUi(this);
    ui->userNameLabel->setText(mLoan->getUser()->getName());
    ui->loanStartDateTextLabel->setText(mLoan->getStartDate().toString("dd.MM.yyyy"));
    ui->titleTextLabel->setText(mLoan->getBook()->getTitle());
    ui->authorNamesLabel->setText(mLoan->getBook()->printAuthor());
}


LoanWidget::~LoanWidget()
{
    delete ui;
}

std::shared_ptr<Loan> LoanWidget::getLoan()
{
    return mLoan;
}
