#include "signup.h"
#include "ui_signup.h"
#include <QTimer>
#include "validator.h"
#include "user.h"

signup::signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
}

signup::~signup()
{
    delete ui;
}

void signup::on_backBtn_clicked()
{
    this->close();
}

void signup::on_signupBtn_clicked()
{

    QString name = ui->nameInput->text().trimmed();
    QString username = ui->usernameInput->text().trimmed();
    QString password = ui->passwordInput->text().trimmed();
    QString phone = ui->phoneInput->text().trimmed();
    QString address = ui->addressInput->text().trimmed();

    if(!validator::userValidator(name,username,password,phone,address)){
        ui->notification->show();
        ui->notification->setStyleSheet("color:red;");
        ui->notification->setText("اطلاعات وارد شده نادرست می باشد");
        QTimer::singleShot(5000, this, [this] () { ui->notification->hide();});
    }else{
        if(!user::existUsername(username)){
            if(!user::existPhone(phone)){

                //save in database
                if(user::save(name,username,password,phone,address)){

                    this->close();
                }else{
                    ui->notification->show();
                    ui->notification->setStyleSheet("color:red;");
                    ui->notification->setText("خطایی در ذخیره کردن داده ها رخ داده است");
                    QTimer::singleShot(5000, this, [this] () { ui->notification->hide();});
                }

            }else{
                ui->notification->show();
                ui->notification->setStyleSheet("color:red;");
                ui->notification->setText("شماره تلفن از قبل وجود دارد");
                QTimer::singleShot(5000, this, [this] () { ui->notification->hide();});
            }
        }else{
            ui->notification->show();
            ui->notification->setStyleSheet("color:red;");
            ui->notification->setText("نام کاربری از قبل وجود دارد");
            QTimer::singleShot(5000, this, [this] () { ui->notification->hide();});
        }
    }

}
