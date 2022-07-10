#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include <QWidget>
#include <QJsonArray>
namespace Ui {
class searchpanel;
}

class searchpanel : public QWidget
{
    Q_OBJECT

public:
    explicit searchpanel(QWidget *parent = nullptr);
    ~searchpanel();

private slots:
    void on_backBtn_clicked();

    void on_searchBtn_clicked();

signals:
    void search_product(QJsonArray searchResult);

private:
    Ui::searchpanel *ui;
};

#endif // SEARCHPANEL_H
