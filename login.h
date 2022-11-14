#ifndef LOGIN_H
#define LOGIN_H

#include "adminpin.h"
#include "homescreen.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>


QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
    QSqlDatabase db;


public slots:

    void adminSignUp();
private slots:
    void on_loginButton_clicked();



    void on_signUpButton_clicked();


    void on_adminSignUpButton_clicked();

private:
    Ui::login *ui;
};
struct usersAtLogin{
    QString email;
    QString password;
    QString fName;
    QString lName;
    int completedTasks;
    int maxTasks;
    int rating;
    int completedEvents;
    int maxEvents;
    int isAdmin = 0;

};
struct adminUser{
    QString email;
    QString password;
    QString fName;
    QString lName;

};
struct infoForMessaging{
    QString fName;
    QString lName;
    QString email;
};

inline homeScreen *newHomeScreen; // declare newHome screen
inline adminpin *newAdminPinWindow;
inline QVector <usersAtLogin> userList;
inline bool pinCorrect;
inline login *newLoginWindow;
inline usersAtLogin currentUser;
inline QVector <infoForMessaging> listOfStudents;
inline QVector <infoForMessaging> listOfAdmin;

#endif // LOGIN_H
