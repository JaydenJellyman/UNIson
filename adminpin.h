#ifndef ADMINPIN_H
#define ADMINPIN_H

#include <QWidget>

namespace Ui {
class adminpin;
}

class adminpin : public QWidget
{
    Q_OBJECT

public:
    explicit adminpin(QWidget *parent = nullptr);
    ~adminpin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::adminpin *ui;
};

#endif // ADMINPIN_H
