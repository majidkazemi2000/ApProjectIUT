#ifndef BUY_H
#define BUY_H
#include <QString>
#include <QJsonArray>
class buy
{
public:
    buy();
    static QJsonArray getAllBuy();
    static qint64 getSumOfBuy();
    static bool checkout(qint64 productCount , qint64 productPrice);
    static QJsonArray getBuyForCustomer(QString customer);
    static qint64 getTotalBuyForCustomer(QString customer);

private:
    static int getLastId();
};

#endif // BUY_H
