#ifndef ADDTASK_H
#define ADDTASK_H

#include <QWidget>

namespace Ui {
class addtask;
}

class addtask : public QWidget
{
    Q_OBJECT

public:
    explicit addtask(QWidget *parent = nullptr);
    ~addtask();

private:
    Ui::addtask *ui;

private slots:

    void saveTask();
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

};

#endif // ADDTASK_H
