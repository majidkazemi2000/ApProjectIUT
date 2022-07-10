#include "showproductcustomer.h"
#include "ui_showproductcustomer.h"
#include "product.h"
#include <QSettings>
#include <QBoxLayout>
#include <QPushButton>
#include "detailproduct.h"
#include <QDebug>
#include "editproductpanel.h"

showproductcustomer::showproductcustomer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showproductcustomer)
{
    ui->setupUi(this);
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    username = settings.value("username").toString();


    fillTable();


}

showproductcustomer::~showproductcustomer()
{
    delete ui;
}

void showproductcustomer::fillTable()
{


    ui->productTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QJsonArray product = product::getProductOfCustomer(username);
    ui->productTable->setRowCount(product.size()+1);
    ui->productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();
    QTableWidgetItem *item4 = new QTableWidgetItem();
    QTableWidgetItem *item5 = new QTableWidgetItem();
    QTableWidgetItem *item6 = new QTableWidgetItem();
    QTableWidgetItem *item7 = new QTableWidgetItem();
    QTableWidgetItem *item8 = new QTableWidgetItem();
    QTableWidgetItem *item9 = new QTableWidgetItem();

    ui->productTable->setItem(0,0,item1);
    item1->setText("شناسه کالا");
    item1->setTextAlignment(Qt::AlignCenter);

    ui->productTable->setItem(0,1,item2);
    item2->setText("نام کالا");
    item2->setTextAlignment(Qt::AlignCenter);


    ui->productTable->setItem(0,2,item3);
    item3->setText("دسته بندی");
    item3->setTextAlignment(Qt::AlignCenter);

    ui->productTable->setItem(0,3,item4);
    item4->setText("برند");
    item4->setTextAlignment(Qt::AlignCenter);


    ui->productTable->setItem(0,4,item5);
    item5->setText("موجودی");
    item5->setTextAlignment(Qt::AlignCenter);

    ui->productTable->setItem(0,5,item6);
    item6->setText("قیمت");
    item6->setTextAlignment(Qt::AlignCenter);

    ui->productTable->setItem(0,6,item7);
    item7->setText("ویرایش");
    item7->setTextAlignment(Qt::AlignCenter);

    ui->productTable->setItem(0,7,item8);
    item8->setText("جزئیات");
    item8->setTextAlignment(Qt::AlignCenter);

    ui->productTable->setItem(0,8,item9);
    item9->setText("حذف");
    item9->setTextAlignment(Qt::AlignCenter);


    for (int i = 1; i <= product.size(); i++) {
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        QTableWidgetItem *item4 = new QTableWidgetItem();
        QTableWidgetItem *item5 = new QTableWidgetItem();
        QTableWidgetItem *item6 = new QTableWidgetItem();


        ui->productTable->setItem(i,0,item1);
        item1->setText(QString::number(product.at(i-1)["id"].toInt()));
        item1->setTextAlignment(Qt::AlignCenter);

        ui->productTable->setItem(i,1,item2);
        item2->setText(product.at(i-1)["name"].toString());
        item2->setTextAlignment(Qt::AlignCenter);


        ui->productTable->setItem(i,2,item3);
        item3->setText(product.at(i-1)["category"].toString());
        item3->setTextAlignment(Qt::AlignCenter);

        ui->productTable->setItem(i,3,item4);
        item4->setText(product.at(i-1)["brand"].toString());
        item4->setTextAlignment(Qt::AlignCenter);


        ui->productTable->setItem(i,4,item5);
        item5->setText(QString::number(product.at(i-1)["count"].toInt()) + "*");
        item5->setTextAlignment(Qt::AlignCenter);

        ui->productTable->setItem(i,5,item6);
        item6->setText(QString::number(product.at(i-1)["price"].toInt()) +" "+ " تومان");
        item6->setTextAlignment(Qt::AlignCenter);



        QWidget* pWidget0 = new QWidget();
        QPushButton *btn0 = new QPushButton();
        btn0->setText("ویرایش");
        btn0->setToolTip(product.at(i-1)["name"].toString());
        btn0->setStyleSheet("background-color:green;color:white;");
        btn0->setFont(QFont("Yekan Bakh"));
        btn0->setCursor(Qt::PointingHandCursor);
        QHBoxLayout* pLayout0 = new QHBoxLayout(pWidget0);
        pLayout0->addWidget(btn0);
        pLayout0->setAlignment(Qt::AlignCenter);
        pLayout0->setContentsMargins(0, 0, 0, 0);
        pWidget0->setLayout(pLayout0);
        ui->productTable->setCellWidget(i, 6, pWidget0);
        connect(btn0, &QPushButton::clicked, this, &showproductcustomer::edit);




        QWidget* pWidget = new QWidget();
        QPushButton *btn = new QPushButton();
        btn->setText("جزئیات");
        btn->setToolTip(product.at(i-1)["name"].toString());
        btn->setStyleSheet("background-color:gray;color:white;");
        btn->setFont(QFont("Yekan Bakh"));
        btn->setCursor(Qt::PointingHandCursor);
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        ui->productTable->setCellWidget(i, 7, pWidget);
        connect(btn, &QPushButton::clicked, this, &showproductcustomer::detail);



        QWidget* pWidget1 = new QWidget();
        QPushButton *btn1 = new QPushButton();
        btn1->setText("حذف");
        btn1->setToolTip(product.at(i-1)["name"].toString());
        btn1->setStyleSheet("background-color:red;color:white;");
        btn1->setFont(QFont("Yekan Bakh"));
        btn1->setCursor(Qt::PointingHandCursor);
        QHBoxLayout* pLayout1 = new QHBoxLayout(pWidget1);
        pLayout1->addWidget(btn1);
        pLayout1->setAlignment(Qt::AlignCenter);
        pLayout1->setContentsMargins(0, 0, 0, 0);
        pWidget1->setLayout(pLayout1);
        ui->productTable->setCellWidget(i, 8, pWidget1);
        connect(btn1, &QPushButton::clicked, this, &showproductcustomer::deleteProduct);


    }
}

void showproductcustomer::detail()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    settings.setValue("detail_product",b->toolTip());
    settings.value("detail_product_username",username);
    detailProduct *detail = new detailProduct();
    detail->setWindowTitle(" ");
    detail->setWindowIcon(QIcon(":/images/icon"));
    detail->show();
}

void showproductcustomer::edit()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    settings.setValue("edit_product",b->toolTip());
    editproductpanel *edit = new editproductpanel();
    edit->setWindowTitle(" ");
    edit->setWindowIcon(QIcon(":/images/icon"));
    connect(edit,SIGNAL(edit_product()),this,SLOT(edit_product()));

    edit->show();
}

void showproductcustomer::edit_product()
{
    fillTable();
}

void showproductcustomer::deleteProduct()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    if (product::deleteProduct(b->toolTip(),username)) {
        fillTable();
    }
}
