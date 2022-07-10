#include "searchpanel.h"
#include "ui_searchpanel.h"
#include "product.h"
#include "clientpanel.h"
#include <QtDebug>
#include <QJsonArray>


searchpanel::searchpanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchpanel)
{
    ui->setupUi(this);
}

searchpanel::~searchpanel()
{
    delete ui;
}

void searchpanel::on_backBtn_clicked()
{
    this->close();
}

void searchpanel::on_searchBtn_clicked()
{

    if(ui->searchText->text().length() > 0){
        QString accordingTo;
        switch (ui->accordingTo->currentIndex()) {
            case 0:
                accordingTo = "name";
            break;
            case 1:
                accordingTo = "category";
            break;
            case 2:
                accordingTo = "customer";
            break;
            case 3:
                accordingTo = "brand";
            break;
            default:
                accordingTo = "name";

        }

        QJsonArray searchResult = product::search(accordingTo,ui->searchText->text());
        emit search_product(searchResult);
        this->hide();

    }

}
