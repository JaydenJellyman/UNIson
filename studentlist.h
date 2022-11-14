#ifndef STUDENTLIST_H
#define STUDENTLIST_H
#include "login.h"

#include <QMainWindow>

namespace Ui {
class studentlist;
}

class studentlist : public QMainWindow
{
    Q_OBJECT

public:
    explicit studentlist(QWidget *parent = nullptr);
    ~studentlist();

private slots:


    void on_returnButton_clicked();

private:
    Ui::studentlist *ui;
    QVector <usersAtLogin> studentList;
    void setStudentList();
};

#endif // STUDENTLIST_H
