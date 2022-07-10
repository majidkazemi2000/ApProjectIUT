#ifndef USER_H
#define USER_H
#include <QString>
#include <QJsonArray>
class user
{
public:
    user();
    static bool loginUser(QString username , QString password);
    static QString rememberMe(QString username , QString phone);
    static bool existUsername(QString username);
    static bool existPhone(QString phone);
    static bool save(QString name,QString username,QString password,QString phone,QString address);
    static QString getRole(QString username);
    static QString getName(QString username);
    static bool isActive(QString username);
    static QJsonArray getAllUser();
    static bool editUser(QString username , QString role , bool status);
    static bool logout();
    static qint64 getUserCount();
    static qint64 getCustomerCount();
    static bool updateAcount(QString username , qint64 amount);
    static bool checkCustomer(QString username);

};

#endif // USER_H
