#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QJsonArray>

class product
{
public:
    product();
    static QJsonArray getAllProduct();
    static qint64 getProductCount();
    static QJsonArray getAvailableProduct();
    static QJsonObject getDetail(QString productName,QString customer);
    static qint64 getPrice(QString productName);
    static qint64 getAllAvailableProduct(QString productName);
    static bool updateAfterBuy(QString productName , qint64 count);
    static QJsonArray search(QString accordingTo,QString searchText);
    static QString getCustomer(QString productName);
    static QJsonArray getProductOfCustomer(QString username);
    static bool deleteProduct(QString productName , QString owner);
    static bool checkProduct(QString productName,QString customer);
    static bool save(QString username,QString name,QString brand,QString category,qint64 count,qint64 price,QString size,QString weight,QString options);
    static bool edit(QString username,QString name,QString brand,QString category,qint64 count,qint64 price,QString size,QString weight,QString options);

    static int getLastId();
    static QJsonObject getProduct(QString productName,QString customer);
};

#endif // PRODUCT_H
