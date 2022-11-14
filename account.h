#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "login.h"
#include "qlistwidget.h"
#include <QMainWindow>

namespace Ui {
class account;
}

class account : public QMainWindow
{
    Q_OBJECT

public:
    explicit account(QWidget *parent = nullptr);
    ~account();

private slots:
    void on_signOutButton_clicked();

    void on_actionHome_triggered();

    void on_actionView_Notes_triggered();

    void on_unreadList_itemDoubleClicked(QListWidgetItem *item);

    void on_newMessageButton_clicked();

private:
    Ui::account *ui;
    void closeEvent(QCloseEvent *event);
    void setMessages();

};

inline QString currentMessageUser;

#endif // ACCOUNT_H
