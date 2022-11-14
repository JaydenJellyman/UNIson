#ifndef VIEWEVENT_H
#define VIEWEVENT_H

#include <QWidget>

namespace Ui {
class viewevent;
}

class viewevent : public QWidget
{
    Q_OBJECT

public:
    explicit viewevent(QWidget *parent = nullptr);
    ~viewevent();

private slots:
    void setViewEvent();
    void on_pushButton_clicked();

    void markCompleteViewEvent();
private:
    Ui::viewevent *ui;
};

#endif // VIEWEVENT_H
