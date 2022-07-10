#ifndef PAY_H
#define PAY_H
#include <QString>
#include <QJsonArray>

class pay
{
public:
    pay();
    static QJsonArray getAllPay();
    static qint64 getSumOfPay();
    static QJsonArray getPayForCustomer(QString customer);
    static qint64 getTotoalPayForCustomer(QString customer);
    static int getLastId();
    static bool checkout(QString username , qint64 amount);
};

#endif // PAY_H
