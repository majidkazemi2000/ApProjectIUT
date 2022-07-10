#ifndef PAYPANEL_H
#define PAYPANEL_H

#include <QWidget>

namespace Ui {
class paypanel;
}

class paypanel : public QWidget
{
    Q_OBJECT

public:
    explicit paypanel(QWidget *parent = nullptr);
    ~paypanel();
    qint64 allPay = 0;
    qint64 allBuy = 0;
private slots:
    void on_payBtn_clicked();

private:
    Ui::paypanel *ui;
};

#endif // PAYPANEL_H
