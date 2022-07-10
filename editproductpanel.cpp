#include "editproductpanel.h"
#include "ui_editproductpanel.h"
#include <QRect>
#include <QDesktopWidget>
#include <QPoint>
#include <QSettings>
#include <QJsonObject>
#include "product.h"
#include <QJsonDocument>
#include "validator.h"

editproductpanel::editproductpanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editproductpanel)
{
    ui->setupUi(this);
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x() - this->width() * 0.5, center.y() - this->height() * 0.52);

    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    QJsonObject product = product::getProduct(settings.value("edit_product").toString(),settings.value("username").toString());


    productName = product["name"].toString();
    customer = product["customer"].toString();

    ui->brandInput->setText(product["brand"].toString());
    ui->categoryInput->setText(product["category"].toString());
    ui->countInput->setText(QString::number(product["count"].toInt()));
    ui->priceInput->setText(QString::number(product["price"].toInt()));
    ui->sizeInput->setText(product["size"].toString());
    ui->weightInput->setText(product["weight"].toString());


    QJsonObject options = product["options"].toObject();
    QJsonDocument doc(options);
    QString jsonString = doc.toJson(QJsonDocument::Indented);
    ui->optionsInput->setText(jsonString);
}

editproductpanel::~editproductpanel()
{
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    settings.setValue("edit_product","");
    delete ui;
}

void editproductpanel::on_backBtn_clicked()
{
    this->hide();
}

void editproductpanel::on_addBtn_clicked()
{
    QString brand = ui->brandInput->text();
    QString category = ui->categoryInput->text();
    qint64 count = ui->countInput->text().toInt();
    qint64 price = ui->priceInput->text().toInt();
    QString size = ui->sizeInput->text();
    QString weight = ui->weightInput->text();
    QString options = ui->optionsInput->text();


    if (validator::productValidatorForEdit(customer,productName,brand,category,count,price,size,weight)) {
        if(product::edit(customer,productName,brand,category,count,price,size,weight,options)){
            emit edit_product();

            this->hide();
        }
    }
}
