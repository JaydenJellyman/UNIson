#ifndef ADMINPAGE_H
#define ADMINPAGE_H
#include "login.h"

#include <QMainWindow>

namespace Ui {
class adminpage;
}

class adminpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminpage(QWidget *parent = nullptr);
    ~adminpage();

private slots:
    void on_pushButton_clicked();

    void on_signOutButton_clicked();

    void on_newMessageButton_clicked();

    void on_unreadList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::adminpage *ui;
    void setMessages();
};

inline QString currentMessageAdmin;




#endif // ADMINPAGE_H
