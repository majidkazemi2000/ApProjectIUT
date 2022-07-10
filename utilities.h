#ifndef UTILITIES_H
#define UTILITIES_H
#include <QString>
class utilities
{
public:
    utilities();
    QString key;
    QString iv;
    static QByteArray encrypt(QString str);
    static QString decrypt(QByteArray str);
    static QString getDataAndTime();
    static bool sendMail();
};

#endif // UTILITIES_H
