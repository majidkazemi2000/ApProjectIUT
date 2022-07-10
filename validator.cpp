#include "validator.h"
#include "user.h"
#include "product.h"

validator::validator()
{

}
bool validator::userValidator(QString name, QString username, QString password, QString phone, QString address){
    if (name.length() >= 3) {
        if (username.length() >= 4) {
            if (password.length() >= 4) {
                if (phone.length() == 11) {
                    if (address.length() >= 4) {

                       return true;
                    }
                }
            }
        }
    }
    return false;
}

bool validator::productValidator(QString username, QString name, QString brand, QString category, qint64 count, qint64 price, QString size, QString weight)
{
    if(user::checkCustomer(username) && product::checkProduct(name,username) && brand.length() > 0 && category.length() > 0 && count > 0 && price > 0 && size.length() > 0 && weight.length() > 0){
        return true;
    }
    return false;
}

bool validator::productValidatorForEdit(QString username, QString name, QString brand, QString category, qint64 count, qint64 price, QString size, QString weight)
{
    if(user::checkCustomer(username) && name.length() > 0 && brand.length() > 0 && category.length() > 0 && count > 0 && price > 0 && size.length() > 0 && weight.length() > 0){
        return true;
    }
    return false;
}
