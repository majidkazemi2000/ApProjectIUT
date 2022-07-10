#include "addproduct.h"
#include "ui_addproduct.h"
#include <QRect>
#include <QPoint>
#include <QDesktopWidget>
#include <QSettings>
#include <QJsonObject>
#include "validator.h"
#include "product.h"

addProduct::addProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addProduct)
{
    ui->setupUi(this);

    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();

    move(center.x() - this->width() * 0.5, center.y() - this->height() * 0.52);
}

addProduct::~addProduct()
{
    delete ui;
}

void addProduct::on_backBtn_clicked()
{
    this->hide();
}

void addProduct::on_addBtn_clicked()
{
    QString name = ui->nameInput->text();
    QString brand = ui->brandInput->text();
    QString category = ui->categoryInput->text();
    qint64 count = ui->countInput->text().toInt();
    qint64 price = ui->priceInput->text().toInt();
    QString size = ui->sizeInput->text();
    QString weight = ui->weightInput->text();
    QString options = ui->optionsInput->text();


    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    QString username = settings.value("username").toString();

    if (validator::productValidator(username,name,brand,category,count,price,size,weight)) {
        if(product::save(username,name,brand,category,count,price,size,weight,options)){
            this->hide();
        }
    }


}
