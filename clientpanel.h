#ifndef CLIENTPANEL_H
#define CLIENTPANEL_H

#include <QWidget>
#include <QJsonArray>

namespace Ui {
class clientpanel;
}

class clientpanel : public QWidget
{
    Q_OBJECT

public:
    explicit clientpanel(QWidget *parent = nullptr);
    ~clientpanel();
    void fillTable();
    QJsonArray searchItems;
    void fillBuy();
    void fillPay();

private slots:
    void on_logoutBtn_clicked();
    void detail();
    void buy();
    void updatePanel();
    void on_searchBtn_clicked();
    void search_product(QJsonArray searchResult);


    void on_backToAllProduct_clicked();

private:
    Ui::clientpanel *ui;
};

#endif // CLIENTPANEL_H
