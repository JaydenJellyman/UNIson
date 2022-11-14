#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QWidget>

namespace Ui {
class addevent;
}

class addevent : public QWidget
{
    Q_OBJECT

public:
    explicit addevent(QWidget *parent = nullptr);
    ~addevent();

private:
    Ui::addevent *ui;

private slots:
    void saveEvent();
    void on_cancelButton_clicked();
};

#endif // ADDEVENT_H
