#include "userloansdialog.h"
#include "ui_userloansdialog.h"
#include <QMessageBox>

UserLoansDialog::UserLoansDialog(DatabaseManager& database, QWidget *parent, User* user) :
    mDatabase(database), QDialog(parent),  mUser(user),
    ui(new Ui::UserLoansDialog)
{
    ui->setupUi(this);
    ui->titleLabel->setText("Books loaned to user : <b>" + mUser->getName() + "</b>");
    QObject::connect(ui->closeButton, &QPushButton::clicked, this, &UserLoansDialog::onCloseButton);
    mLoansList = nullptr;;
    initialiseBooks();
}

UserLoansDialog::~UserLoansDialog()
{
    delete ui;
}

void UserLoansDialog::initialiseBooks()
{
    if (mLoansList)
        delete mLoansList;
    buttonLoanMap.clear();
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());

    mLoansList = new QWidget(this);
    QVBoxLayout* listLayout = new QVBoxLayout(mLoansList);
    mLoansList->setLayout(listLayout);

    std::vector<std::shared_ptr<Loan>> loansVector = mDatabase.loanDao.getUsersLoans(mUser->getId());

    for (std::shared_ptr<Loan> &loan : loansVector)
    {
        LoanWidget* lo = new LoanWidget(mLoansList, loan);
        QHBoxLayout* lay = new QHBoxLayout(mLoansList);
        lay->addWidget(lo);

        QPushButton* returnButton = new QPushButton("Return book",mLoansList);
        buttonLoanMap.insert(returnButton, lo);
        QObject::connect(returnButton, &QPushButton::clicked, this, &UserLoansDialog::onReturnButton);
        lay->addWidget(returnButton);

        listLayout->addItem(lay);
    }

    layout->insertWidget(1, mLoansList);
}

void UserLoansDialog::onReturnButton()
{
    qDebug() << "Return clicked!";
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    QString message = "Are you sure to return book " + buttonLoanMap.value(button)->getLoan()->getBook()->getTitle() + "?";
    if (QMessageBox::warning(this, "Returning book", message, QMessageBox::Ok, QMessageBox::No) == QMessageBox::Ok)
    {
        mDatabase.loanDao.removeLoan(buttonLoanMap.value(button)->getLoan()->getID());
        initialiseBooks();
    }
}

void UserLoansDialog::onCloseButton()
{
    this->close();
}
