#ifndef EDITUSER_H
#define EDITUSER_H

#include <QWidget>

namespace Ui {
class edituser;
}

class edituser : public QWidget
{
    Q_OBJECT

public:
    explicit edituser(QWidget *parent = nullptr);
    ~edituser();

private slots:
    void on_cancelBtn_clicked();

    void on_edtiBtn_clicked();
signals:
    void update_user();
private:
    Ui::edituser *ui;
};

#endif // EDITUSER_H
