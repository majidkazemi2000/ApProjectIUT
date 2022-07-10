#include "buy.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QDateTime>
#include <QSettings>
#include "utilities.h"
#include "product.h"
#include <QJsonObject>

buy::buy()
{

}

QJsonArray buy::getAllBuy()
{
    QFile f("buy.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    f.close();
    return json.array();

}

qint64 buy::getSumOfBuy()
{
    QFile f("buy.json");
    qint64 sum = 0;
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray buy = json.array();
    for (int i = 0; i < buy.size(); i++) {
        sum += buy.at(i)["price"].toInt();
    }
    f.close();
    return sum;
}

int buy::getLastId()
{
    QFile f("buy.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray buy = json.array();
    if(buy.size() > 0){
        return buy.last()["id"].toInt() + 1;
    }
    return 1;
}


bool buy::checkout(qint64 productCount, qint64 productPrice)
{
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);

    QString username = settings.value("username").toString();
    QString productName = settings.value("buy_product").toString();

    if (productCount > product::getAllAvailableProduct(productName)) {
        return false;
    }



    QFile f("buy.json");
    if( !f.open( QIODevice::ReadOnly ) ){
        return false;
    }
    QJsonDocument jsonOrg = QJsonDocument::fromJson( f.readAll() );
    f.close();
    QString customer = product::getCustomer(productName);

    QJsonObject newBuy = { {"id", buy::getLastId()},{"date", utilities::getDataAndTime()},{"product_name", productName},{"count",productCount},{"price",(productCount * productPrice)} ,{"buyer",username},{"customer",customer}};
    QJsonArray allBuy = jsonOrg.array();
    allBuy.push_back(newBuy);
    QJsonDocument doc(allBuy);
    QFile j("buy.json");

    if( !j.open( QIODevice::ReadWrite | QIODevice::Truncate )  ){
        return false;
    }

    j.write(doc.toJson());
    j.close();

    return true;
}

QJsonArray buy::getBuyForCustomer(QString customer)
{
    QJsonArray newBuy;
    QFile f("buy.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray buy = json.array();
    for (int i = 0; i < buy.size(); i++) {
        if(buy.at(i)["customer"] == customer){
            newBuy.append(buy.at(i));
        }
    }

    f.close();

    return newBuy;
}

qint64 buy::getTotalBuyForCustomer(QString customer)
{
    qint64 sum = 0;
    QFile f("buy.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray buy = json.array();
    for (int i = 0; i < buy.size(); i++) {
        if(buy.at(i)["customer"] == customer){
            sum += buy.at(i)["price"].toInt();
        }
    }

    f.close();

    return sum;
}


