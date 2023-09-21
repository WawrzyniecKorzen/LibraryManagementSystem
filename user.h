
#ifndef USER_H
#define USER_H
#include <QString>
#include <QDate>

enum class AccountType {
    Admin, Member
};

class User
{

public:
    enum Status
    {
        Administrator, RegularUser
    };
    User(int id = -1, QString name = "", QDate date = QDate(0,0,0), AccountType status = AccountType(-1));
    ~User();

    void setId(int num);
    void setName(QString text);
    void setJoined(QDate date);
    void setStatus(int s);
    void setStatus(AccountType type);

    int getId();
    QString getName();
    QDate getJoined();
    AccountType getStatus();

private:
    int id;
    QString name;
    QDate joined;
    AccountType status;

};

#endif // USER_H
