
#ifndef USER_H
#define USER_H
#include <QString>
#include <QDate>


class User
{

public:
    enum Status
    {
        Administrator, RegularUser
    };
    User(int id = -1, QString name = "", QDate date = QDate(0,0,0), int status = -1);
    ~User();

    void setId(int num);
    void setName(QString text);
    void setJoined(QDate date);
    void setStatus(int s);

    int getId();
    QString getName();
    QDate getJoined();
    int getStatus();

private:
    int id;
    QString name;
    QDate joined;
    int status;

};

#endif // USER_H
