#include "edituser.h"
#include "ui_edituser.h"
#include <QDebug>
#include <QSettings>
#include "user.h"
edituser::edituser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edituser)
{
    ui->setupUi(this);
    QStringList list=(QStringList()<<"فعال"<<"غیر فعال");
    ui->statusUser->addItems(list);
    QStringList list2=(QStringList()<<"ادمین"<<"فروشنده"<<"مشتری");
    ui->roleUser->addItems(list2);

    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    if (user::isActive(settings.value("edit_user").toString())) {
        ui->statusUser->setCurrentIndex(0);
    }else{
        ui->statusUser->setCurrentIndex(1);
    }


    if(user::getRole(settings.value("edit_user").toString()) == "client"){
        ui->roleUser->setCurrentIndex(2);
    }else if (user::getRole(settings.value("edit_user").toString()) == "customer") {
        ui->roleUser->setCurrentIndex(1);
    }else {
        ui->roleUser->setCurrentIndex(0);
    }
}

edituser::~edituser()
{
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    settings.setValue("edit_user","");

    delete ui;
}

void edituser::on_cancelBtn_clicked()
{
    this->close();
}


void edituser::on_edtiBtn_clicked()
{
    QSettings settings("c:/windows/winf32.ini", QSettings::IniFormat);
    bool status = (ui->statusUser->currentIndex() == 0)?true:false;
    QString role = (ui->roleUser->currentIndex() == 0) ? "admin" : (ui->roleUser->currentIndex() == 1) ? "customer" : "client";
    if(user::editUser(settings.value("edit_user").toString(),role,status)){
        emit update_user();
        this->hide();
    }
}
