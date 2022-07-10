#include "product.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include "user.h"

product::product()
{

}

QJsonArray product::getAllProduct()
{
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    f.close();
    return json.array();
}

qint64 product::getProductCount()
{
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray product = json.array();

    f.close();
    return product.size();
}

QJsonArray product::getAvailableProduct()
{
    QJsonArray availableProduct;
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)["count"].toInt() > 0){
            availableProduct.append(products.at(i));
        }
    }

    f.close();
    return availableProduct;
}

QJsonObject product::getDetail(QString productName,QString customer)
{
    QJsonArray availableProduct;
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)["name"].toString() == productName && products.at(i)["customer"] == customer){
            return products.at(i)["options"].toObject();
        }
    }

    f.close();
    return {};
}

qint64 product::getPrice(QString productName)
{
    QJsonArray availableProduct;
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)["name"].toString() == productName){

            return products.at(i)["price"].toInt();
        }
    }

    f.close();
    return 0;
}

qint64 product::getAllAvailableProduct(QString productName)
{
    QJsonArray availableProduct;
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)["name"].toString() == productName){

            return products.at(i)["count"].toInt();
        }
    }

    f.close();
    return 0;
}

bool product::updateAfterBuy(QString productName, qint64 count)
{
    QString customer,brand,weight,size,category;
    QJsonObject options;
    int productId,oldCount;
    qint64 price;


    QJsonArray newProducts;
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)["name"] == productName){
            customer = products.at(i)["customer"].toString();
            price = products.at(i)["price"].toInt();
            brand = products.at(i)["brand"].toString();
            size = products.at(i)["size"].toString();
            weight = products.at(i)["weight"].toString();
            category = products.at(i)["category"].toString();
            productId = products.at(i)["id"].toInt();
            options = products.at(i)["options"].toObject();
            oldCount = products.at(i)["count"].toInt();
            QJsonObject newProduct = { {"id", productId},{"name", productName},{"customer", customer},{"count",(oldCount-count)},{"price",price} ,{"brand",brand}, {"weight",weight} ,{"size",size},{"category",category},{"options",options}};
            newProducts.append(newProduct);
        }else{
            newProducts.append(products.at(i));
        }
    }

    f.close();


    QJsonDocument doc(newProducts);
    QFile j("product.json");

    if( !j.open( QIODevice::ReadWrite | QIODevice::Truncate )  ){
        return false;
    }

    j.write(doc.toJson());
    j.close();

    return true;
}

QJsonArray product::search(QString accordingTo, QString searchText)
{

    QJsonArray newProducts;
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)[accordingTo].toString().contains(searchText)){
            newProducts.append(products.at(i));
        }
    }

    f.close();

    return newProducts;

}

QString product::getCustomer(QString productName)
{
    QJsonArray availableProduct;
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)["name"].toString() == productName){

            return products.at(i)["customer"].toString();
        }
    }

    f.close();
    return "";
}

QJsonArray product::getProductOfCustomer(QString username)
{
    QJsonArray availableProduct;
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)["customer"].toString() == username){
            availableProduct.append(products.at(i));
        }
    }

    f.close();
    return availableProduct;
}

bool product::deleteProduct(QString productName, QString owner)
{
    QJsonArray newProducts;
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)["name"] != productName && products.at(i)["customr"] != owner){
            newProducts.append(products.at(i));
        }
    }

    f.close();


    QJsonDocument doc(newProducts);
    QFile j("product.json");

    if( !j.open( QIODevice::ReadWrite | QIODevice::Truncate )  ){
        return false;
    }

    j.write(doc.toJson());
    j.close();
    return true;
}

bool product::checkProduct(QString productName,QString customer)
{
    if(productName.length() > 0){
        QFile f("product.json");
        f.open(QIODevice::ReadOnly);
        QByteArray data = f.readAll();
        QJsonDocument json = QJsonDocument::fromJson(data);
        QJsonArray products = json.array();
        for (int i = 0; i < products.size(); i++) {
            if(products.at(i)["name"] == productName && products.at(i)["customer"] == customer){
                f.close();
                return false;
            }
        }
        f.close();
    }

    return true;
}

bool product::save(QString username, QString name, QString brand, QString category, qint64 count, qint64 price, QString size, QString weight, QString options)
{

    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    f.close();

    QJsonDocument doc1 = QJsonDocument::fromJson(options.toUtf8());

    int productId = product::getLastId();
    QJsonObject newProduct = { {"id", productId},{"name", name},{"customer", username},{"count",count},{"price",price} ,{"brand",brand}, {"weight",weight} ,{"size",size},{"category",category}};
    newProduct.insert("options",doc1.object());
    products.append(newProduct);


    QJsonDocument doc(products);
    QFile j("product.json");

    if( !j.open( QIODevice::ReadWrite | QIODevice::Truncate )  ){
        return false;
    }

    j.write(doc.toJson());
    j.close();

    return true;
}

bool product::edit(QString username, QString name, QString brand, QString category, qint64 count, qint64 price, QString size, QString weight, QString options)
{

    QJsonArray newProducts;
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)["name"] == name && products.at(i)["customer"] == username){

            QJsonObject obj;
            QJsonDocument doc = QJsonDocument::fromJson(options.toUtf8());
            QJsonObject newProduct = { {"id", products.at(i)["id"].toInt()},{"name", name},{"customer", username},{"count",count},{"price",price} ,{"brand",brand}, {"weight",weight} ,{"size",size},{"category",category}};
            newProduct.insert("options",doc.object());
            newProducts.append(newProduct);
        }else{
            newProducts.append(products.at(i));
        }
    }

    f.close();


    QJsonDocument doc(newProducts);
    QFile j("product.json");

    if( !j.open( QIODevice::ReadWrite | QIODevice::Truncate )  ){
        return false;
    }

    j.write(doc.toJson());
    j.close();

    return true;
}

int product::getLastId()
{
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    if(products.size() > 0){
        return products.last()["id"].toInt() + 1;
    }
    return 1;
}

QJsonObject product::getProduct(QString productName, QString customer)
{
    QFile f("product.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray products = json.array();
    for (int i = 0; i < products.size(); i++) {
        if(products.at(i)["name"] == productName && products.at(i)["customer"] == customer){
            f.close();
            return products.at(i).toObject();
        }
    }
    f.close();

    return {};
}
