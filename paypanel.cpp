#include "paypanel.h"
#include "ui_paypanel.h"
#include <QSettings>
#include "buy.h"
#include "pay.h"
#include "user.h"

paypanel::paypanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paypanel)
{
    ui->setupUi(this);
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    allBuy = buy::getTotalBuyForCustomer(settings.value("pay_user").toString());
    allPay = pay::getTotoalPayForCustomer(settings.value("pay_user").toString());
    ui->buyTotal->setText(QString::number(allBuy));
    ui->payTotal->setText(QString::number(allPay));
    ui->remainTotal->setText(QString::number(allBuy - allPay));
    if((allBuy - allPay) <= 0){
        ui->payBtn->setEnabled(false);
        ui->payBtn->setText("تسویه شده است");
    }

}

paypanel::~paypanel()
{
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    settings.setValue("pay_user","");

    delete ui;
}

void paypanel::on_payBtn_clicked()
{
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);

    if(pay::checkout(settings.value("pay_user").toString(),allBuy-allPay)){

        if(user::updateAcount(settings.value("pay_user").toString(),allBuy-allPay)){
            this->hide();
        }
    }


}
