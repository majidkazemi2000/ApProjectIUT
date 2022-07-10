#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QWidget>

namespace Ui {
class customerPanel;
}

class customerPanel : public QWidget
{
    Q_OBJECT

public:
    explicit customerPanel(QWidget *parent = nullptr);
    ~customerPanel();
    void fillTables();
    QString username;


private slots:
    void on_logoutBtn_clicked();

    void on_showProductBtn_clicked();

    void on_addProductBtn_clicked();

private:
    Ui::customerPanel *ui;
};

#endif // CUSTOMERPANEL_H
