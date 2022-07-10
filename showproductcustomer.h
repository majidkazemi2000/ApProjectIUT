#ifndef SHOWPRODUCTCUSTOMER_H
#define SHOWPRODUCTCUSTOMER_H

#include <QWidget>

namespace Ui {
class showproductcustomer;
}

class showproductcustomer : public QWidget
{
    Q_OBJECT

public:
    explicit showproductcustomer(QWidget *parent = nullptr);
    ~showproductcustomer();
    void fillTable();
    QString username;

private slots:
    void detail();
    void deleteProduct();
    void edit();
    void edit_product();

private:
    Ui::showproductcustomer *ui;
};

#endif // SHOWPRODUCTCUSTOMER_H
