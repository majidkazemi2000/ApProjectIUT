#include "user.h"
#include <string.h>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>

user::user()
{

}
bool user::loginUser(QString username ,QString password){
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["username"] == username){
            if (users.at(i)["password"] == password) {
                f.close();
                return true;
            }
        }
    }
    f.close();
    return false;
}
QString user::rememberMe(QString username, QString phone){
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["username"] == username){
            if (users.at(i)["phone"] == phone) {
                f.close();
                return users.at(i)["password"].toString();
            }
        }
    }
    f.close();
    return "";
}
bool user::existPhone(QString phone){
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["phone"] == phone){
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}
bool user::existUsername(QString username){
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["username"] == username){
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}


bool user::save(QString name, QString username, QString password, QString phone, QString address){

    QFile f("data.json");
    if( !f.open( QIODevice::ReadOnly ) ){
        return false;
    }
    QJsonDocument jsonOrg = QJsonDocument::fromJson( f.readAll() );
    f.close();


    QJsonObject newUser = { {"name", name},{"username", username},{"password", password},{"phone",phone},{"address",address} ,{"role","client"}, {"status",true} , {"acount",0} };
    QJsonArray users = jsonOrg.array();
    users.push_back(newUser);
    QJsonDocument doc(users);
    QFile j("data.json");

    if( !j.open( QIODevice::ReadWrite | QIODevice::Truncate )  ){
        return false;
    }

    j.write(doc.toJson());
    j.close();

    return true;

}

QString user::getRole(QString username)
{
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["username"] == username){
            f.close();
            return users.at(i)["role"].toString();
        }
    }
    f.close();
    return "";
}
QString user::getName(QString username)
{
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["username"] == username){
            f.close();
            return users.at(i)["name"].toString();
        }
    }
    f.close();
    return "";

}

bool user::isActive(QString username){
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["username"] == username && users.at(i)["status"] == true){
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}

QJsonArray user::getAllUser()
{
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    f.close();
    return json.array();
}

bool user::editUser(QString username, QString role, bool status)
{

    QString name,phone,address,password;
    qint64 acount;
    QJsonArray newUsers;
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["username"] == username){
            name = users.at(i)["name"].toString();
            phone = users.at(i)["phone"].toString();
            address = users.at(i)["address"].toString();
            password = users.at(i)["password"].toString();
            acount = users.at(i)["acount"].toInt();
            QJsonObject newUser = { {"name", name},{"username", username},{"password", password},{"phone",phone},{"address",address} ,{"role",role}, {"status",status} ,{"acount",acount}};
            newUsers.append(newUser);
        }else{
            newUsers.append(users.at(i));
        }
    }

    f.close();


    QJsonDocument doc(newUsers);
    QFile j("data.json");

    if( !j.open( QIODevice::ReadWrite | QIODevice::Truncate )  ){
        return false;
    }

    j.write(doc.toJson());
    j.close();

    return true;


}

bool user::logout()
{
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    settings.setValue("login",false);
    settings.setValue("username","");
    settings.setValue("role","");
    settings.setValue("name","");
}

qint64 user::getUserCount()
{
    QFile f("data.json");
    qint64 count = 0;
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["role"] == "client"){
            count++;
        }
    }
    f.close();
    return count;
}

qint64 user::getCustomerCount()
{
    QFile f("data.json");
    qint64 count = 0;
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["role"] == "customer"){
            count++;
        }
    }
    f.close();
    return count;
}

bool user::updateAcount(QString username, qint64 amount)
{
    QString name,phone,address,password,role;
    qint64 acount;
    bool status;
    QJsonArray newUsers;
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["username"] == username){
            status = users.at(i)["status"].toBool();
            role = users.at(i)["role"].toString();
            name = users.at(i)["name"].toString();
            phone = users.at(i)["phone"].toString();
            address = users.at(i)["address"].toString();
            password = users.at(i)["password"].toString();
            acount = users.at(i)["acount"].toInt();
            QJsonObject newUser = { {"name", name},{"username", username},{"password", password},{"phone",phone},{"address",address} ,{"role",role}, {"status",status} ,{"acount",(acount+amount)}};
            newUsers.append(newUser);
        }else{
            newUsers.append(users.at(i));
        }
    }

    f.close();


    QJsonDocument doc(newUsers);
    QFile j("data.json");

    if( !j.open( QIODevice::ReadWrite | QIODevice::Truncate )  ){
        return false;
    }

    j.write(doc.toJson());
    j.close();

    return true;
}

bool user::checkCustomer(QString username)
{
    QFile f("data.json");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray users = json.array();
    for (int i = 0; i < users.size(); i++) {
        if(users.at(i)["username"] == username && users.at(i)["status"] == true && users.at(i)["role"] == "customer"){
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}
