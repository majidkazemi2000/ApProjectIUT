#ifndef REMEMBERME_H
#define REMEMBERME_H

#include <QWidget>

namespace Ui {
class rememberMe;
}

class rememberMe : public QWidget
{
    Q_OBJECT

public:
    explicit rememberMe(QWidget *parent = nullptr);
    ~rememberMe();

private slots:
    void on_backBtn_clicked();
    void on_getLinkBtn_clicked();

signals:
    void remember_me(QString username,QString password);

private:
    Ui::rememberMe *ui;
};

#endif // REMEMBERME_H
