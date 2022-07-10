#ifndef BUYPANEL_H
#define BUYPANEL_H

#include <QWidget>


namespace Ui {
class buypanel;
}

class buypanel : public QWidget
{
    Q_OBJECT

public:
    explicit buypanel(QWidget *parent = nullptr);
    ~buypanel();
    qint64 productPrice = 0;
    QString productName;
    qint64 productCount = 1;

private slots:

    void on_productCount_valueChanged(int arg1);

    void on_buyBtn_clicked();
signals:
    void updatePanel();

private:
    Ui::buypanel *ui;
};

#endif // BUYPANEL_H
