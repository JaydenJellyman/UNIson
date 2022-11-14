#ifndef REPLYMESSAGE_H
#define REPLYMESSAGE_H

#include <QWidget>

namespace Ui {
class replymessage;
}

class replymessage : public QWidget
{
    Q_OBJECT

public:
    explicit replymessage(QWidget *parent = nullptr);
    ~replymessage();

private slots:
    void on_sendButton_clicked();

private:
    Ui::replymessage *ui;
};

#endif // REPLYMESSAGE_H
