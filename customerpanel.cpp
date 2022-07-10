#include "customerpanel.h"
#include "ui_customerpanel.h"
#include "user.h"
#include "mainwindow.h"
#include <QSettings>
#include "buy.h"
#include "pay.h"
#include "addproduct.h"
#include "showproductcustomer.h"
#include <QDesktopWidget>

customerPanel::customerPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customerPanel)
{
    ui->setupUi(this);
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);

    customerPanel::username = settings.value("username").toString();
    ui->customerLabel->setText(settings.value("name").toString() + " عزیز ! خوش آمدید");



    qint64 allBay = buy::getTotalBuyForCustomer(username);
    qint64 allPay = pay::getTotoalPayForCustomer(username);

    ui->buyLabel->setText(QString::number(allBay));
    ui->payLabel->setText(QString::number(allPay));

    fillTables();

}

customerPanel::~customerPanel()
{
    delete ui;
}

void customerPanel::fillTables(){


    ui->buyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QJsonArray buy = buy::getBuyForCustomer(username);
    ui->buyTable->setRowCount(buy.size());
    ui->buyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i = 0; i < buy.size(); i++) {
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        QTableWidgetItem *item4 = new QTableWidgetItem();
        QTableWidgetItem *item5 = new QTableWidgetItem();
        QTableWidgetItem *item6 = new QTableWidgetItem();


        ui->buyTable->setItem(i,0,item1);
        item1->setText(QString::number(buy.at(i)["id"].toInt()));
        item1->setTextAlignment(Qt::AlignCenter);

        ui->buyTable->setItem(i,1,item2);
        item2->setText(buy.at(i)["date"].toString());
        item2->setTextAlignment(Qt::AlignCenter);

        ui->buyTable->setItem(i,2,item3);
        item3->setText(buy.at(i)["product_name"].toString());
        item3->setTextAlignment(Qt::AlignCenter);

        ui->buyTable->setItem(i,3,item4);
        item4->setText(QString::number(buy.at(i)["count"].toInt()) + "*");
        item4->setTextAlignment(Qt::AlignCenter);

        ui->buyTable->setItem(i,4,item5);
        item5->setText(QString::number(buy.at(i)["price"].toInt()));
        item5->setTextAlignment(Qt::AlignCenter);

        ui->buyTable->setItem(i,5,item6);
        item6->setText(buy.at(i)["buyer"].toString());
        item6->setTextAlignment(Qt::AlignCenter);
    }





    ui->payTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QJsonArray pay = pay::getPayForCustomer(username);
    ui->payTable->setRowCount(pay.size());
    ui->payTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i = 0; i < pay.size(); i++) {
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();

        ui->payTable->setItem(i,0,item1);
        item1->setText(QString::number(pay.at(i)["id"].toInt()));
        item1->setTextAlignment(Qt::AlignCenter);

        ui->payTable->setItem(i,1,item2);
        item2->setText(pay.at(i)["date"].toString());
        item2->setTextAlignment(Qt::AlignCenter);


        ui->payTable->setItem(i,2,item3);
        item3->setText(QString::number(pay.at(i)["amount"].toInt()));
        item3->setTextAlignment(Qt::AlignCenter);
        item3->setTextColor(QColor("green"));



    }
}


void customerPanel::on_logoutBtn_clicked()
{
    user::logout();
    this->close();
    MainWindow *m = new MainWindow();
    m->setWindowTitle(" ");
    m->setWindowIcon(QIcon(":/images/icon"));
    m->show();
}

void customerPanel::on_showProductBtn_clicked()
{
    showproductcustomer *show = new showproductcustomer();

    show->setFixedSize(show->width(),show->height());
    show->showMaximized();

    show->setWindowTitle(" ");
    show->setWindowIcon(QIcon(":/images/icon"));
    show->show();
}

void customerPanel::on_addProductBtn_clicked()
{
    addProduct *add = new addProduct();
    add->setWindowTitle(" ");
    add->setWindowIcon(QIcon(":/images/icon"));

    add->setFixedSize(add->width(),add->height());

    add->show();
}
