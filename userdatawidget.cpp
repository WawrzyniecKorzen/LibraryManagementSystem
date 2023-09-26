#include "userdatawidget.h"
#include "ui_userdatawidget.h"

#include "changepassworddialog.h"
#include "login.h"
#include <QDebug>
#include <QPixmap>

UserDataWidget::UserDataWidget(QWidget *parent, User* us) :
    QWidget(parent),
    ui(new Ui::UserDataWidget),
    user(us)
{
    ui->setupUi(this);
    QPixmap pictureLogo(":/resources/resources/book-icon.png");
    ui->logo->setPixmap(pictureLogo);
    ui->logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    connect(ui->logOutButton, &QPushButton::clicked, this, &UserDataWidget::logOut);
    qDebug() << "user widget created with id " << user->getId();
}

UserDataWidget::~UserDataWidget()
{
    delete ui;
}

void UserDataWidget::setUser(User *us)
{
    user = us;
}

void UserDataWidget::update()
{
    ui->nameLabel->setText(user->getName());
    ui->dateLabel->setText(user->getJoined().toString("dd.MM.yyyy"));

    this->repaint();
}

void UserDataWidget::logOut()
{
    Login* dialog = new Login();
    dialog->show();
    emit logOutClicked();
}

void UserDataWidget::on_changePassButton_clicked()
{
    ChangePasswordDialog* dialog = new ChangePasswordDialog(nullptr, user, user);
    dialog->show();
}

