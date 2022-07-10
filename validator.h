#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <QString>
#include <QJsonObject>

class validator
{
public:
    validator();
    static bool userValidator(QString name,QString username,QString password,QString phone,QString address);
    static bool productValidator(QString username , QString name , QString brand , QString category , qint64 count , qint64 price , QString size , QString weight);
    static bool productValidatorForEdit(QString username , QString name , QString brand , QString category , qint64 count , qint64 price , QString size , QString weight);

};

#endif // VALIDATOR_H
