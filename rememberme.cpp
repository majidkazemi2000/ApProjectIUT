#include "rememberme.h"
#include "ui_rememberme.h"
#include "user.h"
#include <QTimer>
rememberMe::rememberMe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rememberMe)
{
    ui->setupUi(this);
    ui->notification->hide();
}

rememberMe::~rememberMe()
{
    delete ui;
}

void rememberMe::on_backBtn_clicked()
{
    this->close();
}

void rememberMe::on_getLinkBtn_clicked()
{
    QString username = ui->usernameInput->text().trimmed();
    QString phone = ui->phoneInput->text().trimmed();
    QString returnPassword = user::rememberMe(username,phone);
    ui->notification->show();
    if (returnPassword == "") {
        ui->notification->show();
        ui->notification->setStyleSheet("color:red;");
        ui->notification->setText("نام کاربری یا شماره تلفن اشتباه است");
    }else{
        if(user::isActive(username)){
            emit remember_me(username,returnPassword);
            this->close();
        }else{
            ui->notification->show();
            ui->notification->setStyleSheet("color:red;");
            ui->notification->setText("این کاربر غیر فعال می باشد");
        }

    }
    QTimer::singleShot(5000, this, [this] () { ui->notification->hide();});
}
