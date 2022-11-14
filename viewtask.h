#ifndef VIEWTASK_H
#define VIEWTASK_H

#include <QWidget>

namespace Ui {
class viewtask;
}

class viewtask : public QWidget
{
    Q_OBJECT

public:
    explicit viewtask(QWidget *parent = nullptr);
    ~viewtask();

private:
    Ui::viewtask *ui;

private slots:

    void setViewTask();
    void markCompleteViewTask();





    void on_closeButton_clicked();
};

#endif // VIEWTASK_H
