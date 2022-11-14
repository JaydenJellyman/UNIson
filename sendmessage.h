#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include <QWidget>

namespace Ui {
class sendmessage;
}

class sendmessage : public QWidget
{
    Q_OBJECT

public:
    explicit sendmessage(QWidget *parent = nullptr);
    ~sendmessage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::sendmessage *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // SENDMESSAGE_H
