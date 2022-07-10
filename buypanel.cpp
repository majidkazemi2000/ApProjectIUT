#include "buypanel.h"
#include "ui_buypanel.h"
#include <QSettings>
#include "buy.h"
#include "product.h"
#include <QDebug>

buypanel::buypanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::buypanel)
{
    ui->setupUi(this);
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);

    buypanel::productName = settings.value("buy_product").toString();
    buypanel::productPrice = product::getPrice(settings.value("buy_product").toString());

    ui->productPrice->setText(QString::number(productPrice));
    ui->total->setText(QString::number(productPrice));

    qint64 availableProduct = product::getAllAvailableProduct(productName);
    if(availableProduct > 0){
        ui->productCount->setMaximum(availableProduct);
    }else{
        ui->buyBtn->hide();
    }

}

buypanel::~buypanel()
{
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    settings.setValue("buy_product","");

    delete ui;
}



void buypanel::on_productCount_valueChanged(int arg1)
{
    buypanel::productCount = arg1;
    ui->total->setText(QString::number(arg1 * buypanel::productPrice));
}

void buypanel::on_buyBtn_clicked()
{
    if(buy::checkout(ui->productCount->value(),buypanel::productPrice)){

        product::updateAfterBuy(buypanel::productName,buypanel::productCount);
        emit updatePanel();
        this->hide();
    }

}
