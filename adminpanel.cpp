#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "user.h"
#include "mainwindow.h"
#include <QSettings>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QColor>
#include <QPushButton>
#include <QBoxLayout>
#include "edituser.h"
#include "buy.h"
#include "pay.h"
#include "product.h"
#include "paypanel.h"

adminpanel::adminpanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminpanel)
{
    ui->setupUi(this);
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    ui->adminLabel->setText(settings.value("name").toString() + " عزیز ! خوش آمدید");
    ui->userTable->hide();
    ui->buyTable->hide();
    ui->buyTitle->hide();
    ui->payTable->hide();
    ui->payTitle->hide();
    ui->productTable->hide();
    ui->productStatisticInput->hide();
    ui->productStatisticLabel->hide();

    ui->userStatisticInput->hide();
    ui->userStatisticLabel->hide();

    ui->buyStatisticInput->hide();
    ui->buyStatisticLabel->hide();

    ui->payStatisticInput->hide();
    ui->payStatisticLabel->hide();

    ui->customerStatisticInput->hide();
    ui->customerStatisticLabel->hide();
}

adminpanel::~adminpanel()
{
    delete ui;
}


void adminpanel::on_logoutBtn_clicked()
{
    user::logout();
    this->close();
    MainWindow *m = new MainWindow();
    m->setWindowTitle(" ");
    m->setWindowIcon(QIcon(":/images/icon"));
    m->show();
}

void adminpanel::on_userBtn_clicked()
{
    ui->userBtn->setStyleSheet("background-color:white;");
    ui->transactionBtn->setStyleSheet("background-color:green;");
    ui->productBtn->setStyleSheet("background-color:green;");
    ui->statisticBtn->setStyleSheet("background-color:green;");

    ui->buyTable->hide();
    ui->buyTitle->hide();
    ui->payTable->hide();
    ui->payTitle->hide();
    ui->productTable->hide();
    ui->productStatisticInput->hide();
    ui->productStatisticLabel->hide();

    ui->userStatisticInput->hide();
    ui->userStatisticLabel->hide();

    ui->buyStatisticInput->hide();
    ui->buyStatisticLabel->hide();

    ui->payStatisticInput->hide();
    ui->payStatisticLabel->hide();

    ui->customerStatisticInput->hide();
    ui->customerStatisticLabel->hide();
    ui->userTable->show();
    ui->userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QJsonArray users = user::getAllUser();
    ui->userTable->setRowCount(users.size());
    ui->userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    for (int i = 0; i < users.size(); i++) {
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        QTableWidgetItem *item4 = new QTableWidgetItem();
        QTableWidgetItem *item5 = new QTableWidgetItem();
        QTableWidgetItem *item6 = new QTableWidgetItem();

        ui->userTable->setItem(i,0,item1);
        item1->setText(users.at(i)["name"].toString());
        item1->setTextAlignment(Qt::AlignCenter);
        ui->userTable->setItem(i,1,item2);
        item2->setText(users.at(i)["phone"].toString());
        item2->setTextAlignment(Qt::AlignCenter);
        ui->userTable->setItem(i,2,item3);
        item3->setText(users.at(i)["username"].toString());
        item3->setTextAlignment(Qt::AlignCenter);
        ui->userTable->setItem(i,3,item4);
        item4->setText(users.at(i)["address"].toString());
        item4->setTextAlignment(Qt::AlignCenter);

        ui->userTable->setItem(i,4,item6);
        if(users.at(i)["role"].toString() == "client"){
            item6->setText("مشتری");
        }else if (users.at(i)["role"].toString() == "customer") {
            item6->setText("فروشنده");
        }else {
            item6->setText("ادمین");
        }
        item6->setTextAlignment(Qt::AlignCenter);

        ui->userTable->setItem(i,5,item5);
        if (users.at(i)["status"].toBool()) {
            item5->setTextColor(QColor("green"));
            item5->setText("فعال");
        }else{
            item5->setTextColor(QColor("red"));
            item5->setText("غیر فعال");
        }
        item5->setTextAlignment(Qt::AlignCenter);

        QWidget* pWidget = new QWidget();
        QPushButton *btn = new QPushButton();
        btn->setText("ویرایش");
        btn->setToolTip(users.at(i)["username"].toString());
        btn->setStyleSheet("background-color:yellow;");
        btn->setFont(QFont("Yekan Bakh"));
        btn->setCursor(Qt::PointingHandCursor);
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        ui->userTable->setCellWidget(i, 6, pWidget);
        connect(btn, &QPushButton::clicked, this, &adminpanel::onClicked);


        if(users.at(i)["role"].toString() == "customer"){
            QWidget* pWidget1 = new QWidget();
            QPushButton *btn1 = new QPushButton();
            btn1->setText("تسویه");
            btn1->setToolTip(users.at(i)["username"].toString());
            btn1->setStyleSheet("background-color:green;");
            btn1->setFont(QFont("Yekan Bakh"));
            btn1->setCursor(Qt::PointingHandCursor);
            QHBoxLayout* pLayout1 = new QHBoxLayout(pWidget1);
            pLayout1->addWidget(btn1);
            pLayout1->setAlignment(Qt::AlignCenter);
            pLayout1->setContentsMargins(0, 0, 0, 0);
            pWidget1->setLayout(pLayout);
            ui->userTable->setCellWidget(i, 7, pWidget1);
            connect(btn1, &QPushButton::clicked, this, &adminpanel::checkout);
        }
    }
}
void adminpanel::checkout(){
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    settings.setValue("pay_user",b->toolTip());

    paypanel *pay = new paypanel();
    pay->setWindowTitle(" ");
    pay->setWindowIcon(QIcon(":/images/icon"));
    pay->setFixedSize(pay->width(),pay->height());
    //connect(pay,SIGNAL(update_user()),this,SLOT(update_user()));
    pay->show();

}
void adminpanel::onClicked(){
    QPushButton *b = qobject_cast<QPushButton *>(sender());

    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);

    settings.setValue("edit_user",b->toolTip());

    edituser *edit = new edituser();
    edit->setWindowTitle(" ");
    edit->setWindowIcon(QIcon(":/images/icon"));
    edit->setFixedSize(edit->width(),edit->height());
    connect(edit,SIGNAL(update_user()),this,SLOT(update_user()));
    edit->show();
}

void adminpanel::update_user()
{
    ui->userBtn->click();
}

void adminpanel::on_transactionBtn_clicked()
{
    ui->userBtn->setStyleSheet("background-color:green;");
    ui->transactionBtn->setStyleSheet("background-color:white;");
    ui->productBtn->setStyleSheet("background-color:green;");
    ui->statisticBtn->setStyleSheet("background-color:green;");

    ui->userTable->hide();
    ui->productTable->hide();
    ui->productStatisticInput->hide();
    ui->productStatisticLabel->hide();

    ui->userStatisticInput->hide();
    ui->userStatisticLabel->hide();

    ui->buyStatisticInput->hide();
    ui->buyStatisticLabel->hide();

    ui->payStatisticInput->hide();
    ui->payStatisticLabel->hide();

    ui->customerStatisticInput->hide();
    ui->customerStatisticLabel->hide();
    ui->buyTable->show();
    ui->buyTitle->show();
    ui->payTable->show();
    ui->payTitle->show();

    ui->buyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QJsonArray buy = buy::getAllBuy();
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
    QJsonArray pay = pay::getAllPay();
    ui->payTable->setRowCount(pay.size());
    ui->payTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i = 0; i < pay.size(); i++) {
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        QTableWidgetItem *item4 = new QTableWidgetItem();

        ui->payTable->setItem(i,0,item1);
        item1->setText(QString::number(pay.at(i)["id"].toInt()));
        item1->setTextAlignment(Qt::AlignCenter);

        ui->payTable->setItem(i,1,item2);
        item2->setText(pay.at(i)["date"].toString());
        item2->setTextAlignment(Qt::AlignCenter);

        ui->payTable->setItem(i,2,item3);
        item3->setText(pay.at(i)["customer"].toString());
        item3->setTextAlignment(Qt::AlignCenter);

        ui->payTable->setItem(i,3,item4);
        item4->setText(QString::number(pay.at(i)["amount"].toInt()));
        item4->setTextAlignment(Qt::AlignCenter);
        item4->setTextColor(QColor("green"));



    }


}

void adminpanel::on_productBtn_clicked()
{
    ui->userBtn->setStyleSheet("background-color:green;");
    ui->transactionBtn->setStyleSheet("background-color:green;");
    ui->statisticBtn->setStyleSheet("background-color:green;");

    ui->productBtn->setStyleSheet("background-color:white;");
    ui->userTable->hide();
    ui->buyTable->hide();
    ui->buyTitle->hide();
    ui->payTable->hide();
    ui->payTitle->hide();
    ui->productStatisticInput->hide();
    ui->productStatisticLabel->hide();

    ui->userStatisticInput->hide();
    ui->userStatisticLabel->hide();

    ui->buyStatisticInput->hide();
    ui->buyStatisticLabel->hide();

    ui->payStatisticInput->hide();
    ui->payStatisticLabel->hide();

    ui->customerStatisticInput->hide();
    ui->customerStatisticLabel->hide();
    ui->productTable->show();

    ui->productTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QJsonArray product = product::getAllProduct();
    ui->productTable->setRowCount(product.size());
    ui->productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i = 0; i < product.size(); i++) {
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        QTableWidgetItem *item4 = new QTableWidgetItem();
        QTableWidgetItem *item5 = new QTableWidgetItem();
        QTableWidgetItem *item6 = new QTableWidgetItem();
        QTableWidgetItem *item7 = new QTableWidgetItem();


        ui->productTable->setItem(i,0,item1);
        item1->setText(QString::number(product.at(i)["id"].toInt()));
        item1->setTextAlignment(Qt::AlignCenter);

        ui->productTable->setItem(i,1,item2);
        item2->setText(product.at(i)["name"].toString());
        item2->setTextAlignment(Qt::AlignCenter);


        ui->productTable->setItem(i,2,item3);
        item3->setText(product.at(i)["category"].toString());
        item3->setTextAlignment(Qt::AlignCenter);

        ui->productTable->setItem(i,3,item4);
        item4->setText(product.at(i)["customer"].toString());
        item4->setTextAlignment(Qt::AlignCenter);


        ui->productTable->setItem(i,4,item5);
        item5->setText(QString::number(product.at(i)["count"].toInt()) + "*");
        item5->setTextAlignment(Qt::AlignCenter);

        ui->productTable->setItem(i,5,item6);
        item6->setText(QString::number(product.at(i)["price"].toInt()) +" "+ " تومان");
        item6->setTextAlignment(Qt::AlignCenter);

        ui->productTable->setItem(i,6,item7);
        item7->setText(product.at(i)["brand"].toString());
        item7->setTextAlignment(Qt::AlignCenter);

    }

}

void adminpanel::on_statisticBtn_clicked()
{
    ui->userBtn->setStyleSheet("background-color:green;");
    ui->transactionBtn->setStyleSheet("background-color:green;");
    ui->productBtn->setStyleSheet("background-color:green;");
    ui->statisticBtn->setStyleSheet("background-color:white;");

    ui->userTable->hide();
    ui->buyTable->hide();
    ui->buyTitle->hide();
    ui->payTable->hide();
    ui->payTitle->hide();
    ui->productTable->hide();

    ui->productStatisticInput->show();
    ui->productStatisticLabel->show();

    ui->userStatisticInput->show();
    ui->userStatisticLabel->show();

    ui->buyStatisticInput->show();
    ui->buyStatisticLabel->show();

    ui->payStatisticInput->show();
    ui->payStatisticLabel->show();

    ui->customerStatisticInput->show();
    ui->customerStatisticLabel->show();


    ui->userStatisticInput->setText(QString::number(user::getUserCount()));
    ui->customerStatisticInput->setText(QString::number(user::getCustomerCount()));
    ui->productStatisticInput->setText(QString::number(product::getProductCount()));
    ui->buyStatisticInput->setText(QString::number(buy::getSumOfBuy()));
    ui->payStatisticInput->setText(QString::number(pay::getSumOfPay()));

}
