
#ifndef USER_H
#define USER_H
#include <QString>



class User
{

public:
    enum Status
    {
        Administrator, RegularUser
    };
    User(int id = -1, QString name = "", int status = -1);
    ~User();

    void setId(int num);
    void setName(QString text);
    void setStatus(int s);

    int getId();
    QString getName();
    int getStatus();

private:
    int id;
    QString name;
    int status;

};

#endif // USER_H
