#ifndef DETAILPRODUCT_H
#define DETAILPRODUCT_H

#include <QWidget>

namespace Ui {
class detailProduct;
}

class detailProduct : public QWidget
{
    Q_OBJECT

public:
    explicit detailProduct(QWidget *parent = nullptr);
    ~detailProduct();

private:
    Ui::detailProduct *ui;
};

#endif // DETAILPRODUCT_H
