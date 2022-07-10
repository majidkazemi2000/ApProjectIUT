#include "pay.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QDateTime>
#include <QSettings>
#include "utilities.h"
#include <QJsonObject>
pay::pay()
{

}

QJsonArray pay::getAllPay()
{
    QFile f("pay.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    f.close();
    return json.array();

}

qint64 pay::getSumOfPay()
{
    QFile f("pay.json");
    qint64 sum = 0;
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray pay = json.array();
    for (int i = 0; i < pay.size(); i++) {
        sum += pay.at(i)["amount"].toInt();
    }
    f.close();
    return sum;

}

QJsonArray pay::getPayForCustomer(QString customer)
{
    QJsonArray newPay;
    QFile f("pay.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray pay = json.array();
    for (int i = 0; i < pay.size(); i++) {
        if(pay.at(i)["customer"] == customer){
            newPay.append(pay.at(i));
        }
    }
    f.close();
    return newPay;
}

qint64 pay::getTotoalPayForCustomer(QString customer)
{
    qint64 sum = 0;
    QFile f("pay.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray pay = json.array();
    for (int i = 0; i < pay.size(); i++) {
        if(pay.at(i)["customer"] == customer){
            sum += pay.at(i)["amount"].toInt();
        }
    }
    f.close();
    return sum;
}

int pay::getLastId()
{
    QFile f("pay.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray pay = json.array();
    if(pay.size() > 0){
        return pay.last()["id"].toInt() + 1;
    }
    return 1;
}

bool pay::checkout(QString username, qint64 amount)
{

    QFile f("pay.json");
    if( !f.open( QIODevice::ReadOnly ) ){
        return false;
    }
    QJsonDocument jsonOrg = QJsonDocument::fromJson( f.readAll() );
    f.close();

    QJsonObject newPay = { {"id", pay::getLastId()},{"date", utilities::getDataAndTime()},{"customer", username},{"amount",amount}};
    QJsonArray allPay = jsonOrg.array();
    allPay.push_back(newPay);
    QJsonDocument doc(allPay);
    QFile j("pay.json");

    if( !j.open( QIODevice::ReadWrite | QIODevice::Truncate )  ){
        return false;
    }

    j.write(doc.toJson());
    j.close();

    return true;
}


