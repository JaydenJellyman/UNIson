#ifndef COMPLETEDTASKS_H
#define COMPLETEDTASKS_H

#include <QWidget>

namespace Ui {
class completedtasks;
}

class completedtasks : public QWidget
{
    Q_OBJECT

public:
    explicit completedtasks(QWidget *parent = nullptr);
    ~completedtasks();

private slots:
    void on_closeButton_clicked();
    void setCompletedTasks();

private:
    Ui::completedtasks *ui;
};

#endif // COMPLETEDTASKS_H
