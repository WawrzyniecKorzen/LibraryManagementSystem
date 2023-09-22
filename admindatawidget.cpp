#include "admindatawidget.h"
#include "ui_admindatawidget.h"
#include "adduserdialog.h"

#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

AdminDataWidget::AdminDataWidget(QWidget *parent, DatabaseManager& database) :
    QWidget(parent),
    ui(new Ui::AdminDataWidget), mDatabase(database)
{
    ui->setupUi(this);

    stackedPanel = new QStackedWidget(this);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    setTabBar();
    setToolBar();



    QVBoxLayout* lay = qobject_cast<QVBoxLayout*>(this->layout());
    QHBoxLayout* lowerLayout = new QHBoxLayout();
    lay->insertWidget(0, tabBar);
    lay->addLayout(lowerLayout);
    lowerLayout->addWidget(toolBar);


    usersWidget = new UsersAdminWidget(this, mDatabase);
    usersWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    bookSearch = new SearchWidget(this, mDatabase);
    bookSearch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    stackedPanel->addWidget(usersWidget);
    stackedPanel->addWidget(bookSearch);

    stackedPanel->setCurrentWidget(usersWidget);

    scrollArea->setWidget(stackedPanel);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lowerLayout->addWidget(scrollArea);
}

AdminDataWidget::~AdminDataWidget()
{
    delete ui;
}

void AdminDataWidget::setTabBar()
{
    tabBar = new QWidget(this);
    QHBoxLayout* tabLayout = new QHBoxLayout(tabBar);
    tabBar->setLayout(tabLayout);

    QPushButton* usersButton = new QPushButton(tabBar);
    usersButton->setText("Users");
    usersButton->setCheckable(true);
    usersButton->setChecked(true);
    usersButton->setAutoExclusive(true);
    tabBar->layout()->addWidget(usersButton);

    QPushButton* booksButton = new QPushButton(tabBar);
    booksButton->setText("Books");
    booksButton->setCheckable(true);
    booksButton->setAutoExclusive(true);
    tabBar->layout()->addWidget(booksButton);

    tabLayout->addStretch();

    mode = WidgetMode::Users;

    QObject::connect(usersButton,&QPushButton::clicked, this, &AdminDataWidget::onUsers);
    QObject::connect(booksButton, &QPushButton::clicked, this, &AdminDataWidget::onBooks);
}

void AdminDataWidget::setToolBar()
{
    toolBar = new QWidget(this);
    QVBoxLayout* toolLayout = new QVBoxLayout(toolBar);

    QPushButton* searchButton = new QPushButton(toolBar);
    searchButton->setText("Search");
    toolLayout->addWidget(searchButton);

    QPushButton* editButton = new QPushButton(toolBar);
    editButton->setText("Edit");
    toolLayout->addWidget(editButton);

    QPushButton* addButton = new QPushButton(toolBar);
    addButton->setText("Add");
    toolLayout->addWidget(addButton);

    QPushButton* removeButton = new QPushButton(toolBar);
    removeButton->setText("Remove");
    toolLayout->addWidget(removeButton);

    QSpacerItem* spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolLayout->addItem(spacer);
    toolBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    QObject::connect(addButton, &QPushButton::clicked, this, &AdminDataWidget::onAdd);
    QObject::connect(removeButton, &QPushButton::clicked, this, &AdminDataWidget::onRemove);

}

AdminDataWidget::WidgetMode AdminDataWidget::getMode()
{
    return mode;
}

void AdminDataWidget::onUsers()
{
    mode = WidgetMode::Users;
    stackedPanel->setCurrentWidget(usersWidget);
}

void AdminDataWidget::onBooks()
{
    mode = WidgetMode::Books;
    stackedPanel->setCurrentWidget(bookSearch);


}

void AdminDataWidget::onAdd()
{
    if (mode == WidgetMode::Users)
        onAddUser();
}

void AdminDataWidget::onAddUser()
{
    AddUserDialog* dialog = new AddUserDialog(this, mDatabase);
    dialog->show();
}

void AdminDataWidget::onRemove()
{
    if (mode == WidgetMode::Users)
        onRemoveUser();
}

void AdminDataWidget::onRemoveUser()
{


    User* user = usersWidget->findPickedUser();
    if (user->getName() != "admin")
        mDatabase.userDao.removeUser(user->getId());
    else
        QMessageBox::warning(this, "Cannot do that!", "You cannot remove admin account!", QMessageBox::Ok);
}
