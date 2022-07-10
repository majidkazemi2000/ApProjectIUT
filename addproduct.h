#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QWidget>

namespace Ui {
class addProduct;
}

class addProduct : public QWidget
{
    Q_OBJECT

public:
    explicit addProduct(QWidget *parent = nullptr);
    ~addProduct();

private slots:
    void on_backBtn_clicked();

    void on_addBtn_clicked();

private:
    Ui::addProduct *ui;
};

#endif // ADDPRODUCT_H
