#include "utilities.h"
#include <QString>
#include <QDateTime>
#include <QCryptographicHash>
#include "AESLibrary/qaesencryption.h"
#include <QDebug>
#include "emailLibrary/SmtpMime"

utilities::utilities()
{
}
QByteArray utilities::encrypt(QString str){
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC,QAESEncryption::ZERO);


    QString key = "RgUkXp2s5v8y/B?E(H+MbQeThVmYq3t6";
    QString iv = "9y$B&E)H@McQfTjWnZq4t7w!z%C*F-Ja";

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray encodeText = encryption.encode(str.toLocal8Bit(), hashKey, hashIV);

    return encodeText;


}
QString utilities::decrypt(QByteArray str){
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC,QAESEncryption::ZERO);


    QString key = "RgUkXp2s5v8y/B?E(H+MbQeThVmYq3t6";
    QString iv = "9y$B&E)H@McQfTjWnZq4t7w!z%C*F-Ja";

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray decodeText = encryption.decode(str, hashKey, hashIV);



    char fixed[2048];
    int index = 0;
    QByteArray::iterator iter = decodeText.begin();
    while(iter != decodeText.end())
    {
        QChar c = *iter;
        if (c != '\0') fixed[index++] = c.toLatin1();
        iter++;
    }
    fixed[index] = '\0';
    return decodeText;
}

QString utilities::getDataAndTime()
{
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("hh:mm:ss | yyyy.MM.dd");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
    return formattedTimeMsg;
}

bool utilities::sendMail()
{

    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

        // We need to set the username (your email address) and the password
        // for smtp authentification.

        smtp.setUser("alikazemi20126@gmail.com");
        smtp.setPassword("252517994005");

        // Now we create a MimeMessage object. This will be the email.

        MimeMessage message;

        message.setSender(new EmailAddress("alikazemi20126@gmail.com", "Ali Kazemi"));
        message.addRecipient(new EmailAddress("majidkazemi20126@gmail.com", "Majid Kazemi"));
        message.setSubject("SmtpClient for Qt - Demo");

        // Now add some text to the email.
        // First we create a MimeText object.

        MimeText text;

        text.setText("Hi,\nThis is a simple email message.\n");

        // Now add it to the mail

        message.addPart(&text);

        // Now we can send the mail

        smtp.connectToHost();
        smtp.login();
        smtp.sendMail(message);
        smtp.quit();


}


