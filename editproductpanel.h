#ifndef EDITPRODUCTPANEL_H
#define EDITPRODUCTPANEL_H

#include <QWidget>

namespace Ui {
class editproductpanel;
}

class editproductpanel : public QWidget
{
    Q_OBJECT

public:
    explicit editproductpanel(QWidget *parent = nullptr);
    ~editproductpanel();
    QString customer;
    QString productName;

private slots:
    void on_backBtn_clicked();

    void on_addBtn_clicked();

signals:
    void edit_product();
private:
    Ui::editproductpanel *ui;
};

#endif // EDITPRODUCTPANEL_H
