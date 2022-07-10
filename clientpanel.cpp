#include "clientpanel.h"
#include "ui_clientpanel.h"
#include <QSettings>
#include <QJsonArray>
#include "product.h"
#include <QHBoxLayout>
#include "user.h"
#include "mainwindow.h"
#include <QDebug>
#include "buypanel.h"
#include "detailproduct.h"
#include "searchpanel.h"
#include <QJsonArray>

//void clientpanel::fillTable();

clientpanel::clientpanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientpanel)
{
    ui->setupUi(this);
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    ui->clientLabel->setText(settings.value("name").toString() + " عزیز ! خوش آمدید");

    ui->backToAllProduct->hide();
    fillTable();


}

clientpanel::~clientpanel()
{
    delete ui;
}

void clientpanel::fillTable()
{
    QJsonArray product;
    ui->productTable->clear();
    if(clientpanel::searchItems.size() <= 0){
        product= product::getAvailableProduct();
    }else{

        product = clientpanel::searchItems;
    }
    ui->productTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
    item4->setText("فروشنده");
    item4->setTextAlignment(Qt::AlignCenter);


    ui->productTable->setItem(0,4,item5);
    item5->setText("موجودی");
    item5->setTextAlignment(Qt::AlignCenter);

    ui->productTable->setItem(0,5,item6);
    item6->setText("قیمت");
    item6->setTextAlignment(Qt::AlignCenter);

    ui->productTable->setItem(0,6,item7);
    item7->setText("برند");
    item7->setTextAlignment(Qt::AlignCenter);

    ui->productTable->setItem(0,7,item8);
    item8->setText("جزئیات");
    item8->setTextAlignment(Qt::AlignCenter);

    ui->productTable->setItem(0,8,item9);
    item9->setText("خرید");
    item9->setTextAlignment(Qt::AlignCenter);

    for (int i = 1; i <= product.size(); i++) {
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        QTableWidgetItem *item4 = new QTableWidgetItem();
        QTableWidgetItem *item5 = new QTableWidgetItem();
        QTableWidgetItem *item6 = new QTableWidgetItem();
        QTableWidgetItem *item7 = new QTableWidgetItem();


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
        item4->setText(product.at(i-1)["customer"].toString());
        item4->setTextAlignment(Qt::AlignCenter);


        ui->productTable->setItem(i,4,item5);
        item5->setText(QString::number(product.at(i-1)["count"].toInt()) + "*");
        item5->setTextAlignment(Qt::AlignCenter);

        ui->productTable->setItem(i,5,item6);
        item6->setText(QString::number(product.at(i-1)["price"].toInt()) +" "+ " تومان");
        item6->setTextAlignment(Qt::AlignCenter);

        ui->productTable->setItem(i,6,item7);
        item7->setText(product.at(i-1)["brand"].toString());
        item7->setTextAlignment(Qt::AlignCenter);


        QWidget* pWidget = new QWidget();
        QPushButton *btn = new QPushButton();
        btn->setText("جزئیات");
        btn->setToolTip(product.at(i-1)["name"].toString() + "-" + product.at(i-1)["customer"].toString());

        btn->setStyleSheet("background-color:gray;color:white;");
        btn->setFont(QFont("Yekan Bakh"));
        btn->setCursor(Qt::PointingHandCursor);
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        ui->productTable->setCellWidget(i, 7, pWidget);
        connect(btn, &QPushButton::clicked, this, &clientpanel::detail);


        QWidget* pWidget1 = new QWidget();
        QPushButton *btn1 = new QPushButton();
        if(product.at(i-1)["count"].toInt() <= 0){
            btn1->setEnabled(false);
        }
        btn1->setText("خرید");
        btn1->setToolTip(product.at(i-1)["name"].toString());
        btn1->setStyleSheet("background-color:green;color:white;");
        btn1->setFont(QFont("Yekan Bakh"));
        btn1->setCursor(Qt::PointingHandCursor);
        QHBoxLayout* pLayout1 = new QHBoxLayout(pWidget1);
        pLayout1->addWidget(btn1);
        pLayout1->setAlignment(Qt::AlignCenter);
        pLayout1->setContentsMargins(0, 0, 0, 0);
        pWidget1->setLayout(pLayout1);
        ui->productTable->setCellWidget(i, 8, pWidget1);
        connect(btn1, &QPushButton::clicked, this, &clientpanel::buy);

    }
}

void clientpanel::on_logoutBtn_clicked()
{
    user::logout();
    this->close();
    MainWindow *m = new MainWindow();
    m->setWindowTitle(" ");
    m->setWindowIcon(QIcon(":/images/icon"));
    m->show();
}

void clientpanel::detail()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);

    QRegExp rx("(\\-)");
    QStringList query = b->toolTip().split(rx);


    settings.setValue("detail_product",query[0]);
    settings.setValue("detail_product_username",query[1]);
    detailProduct *detail = new detailProduct();
    detail->setWindowTitle(" ");
    detail->setWindowIcon(QIcon(":/images/icon"));
    detail->show();
}

void clientpanel::buy()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    settings.setValue("buy_product",b->toolTip());

    buypanel *buy = new buypanel();
    buy->setWindowTitle(" ");
    buy->setWindowIcon(QIcon(":/images/icon"));
    connect(buy,SIGNAL(updatePanel()),this,SLOT(updatePanel()));

    buy->show();
}
void clientpanel::updatePanel(){

    fillTable();
}


void clientpanel::on_searchBtn_clicked()
{
    searchpanel *search = new searchpanel();
    search->setWindowTitle(" ");
    search->setWindowIcon(QIcon(":/images/icon"));
    connect(search,SIGNAL(search_product(QJsonArray)),this,SLOT(search_product(QJsonArray)));

    search->show();
}
void clientpanel::search_product(QJsonArray searchResult)
{
    clientpanel::searchItems = searchResult;
    ui->backToAllProduct->show();
    fillTable();
}


void clientpanel::on_backToAllProduct_clicked()
{
    clientpanel::searchItems = {};
    ui->backToAllProduct->hide();
    fillTable();
}
