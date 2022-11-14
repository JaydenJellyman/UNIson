#include "adminpage.h"
#include "sendmessage.h"
#include "ui_adminpage.h"
#include "studentlist.h"
#include "viewmessage.h"

adminpage::adminpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminpage)
{
    ui->setupUi(this);

    // set window title
    setWindowTitle("UNIson - Admin");

    // display admin name
    ui->adminFName->setText(currentUser.fName);
    ui->adminLName->setText(currentUser.lName);
    ui->adminEmail->setText(currentUser.email);

    // set new message button image
    ui->newMessageButton->setStyleSheet("QPushButton {background-image: url(':/img/newmessage.png')}");  

    // set messages
    setMessages();

}

adminpage::~adminpage()
{
    delete ui;
}

// set messages (read and unread)
void adminpage::setMessages(){

    QSqlQuery q1;
    q1.exec("SELECT * FROM messages");
    while(q1.next()){
        if(q1.value(2).toString()==currentUser.email && q1.value(3).toInt() == 0){
            ui->unreadList->addItem(q1.value(0).toString());
        }
        if(q1.value(2).toString()==currentUser.email && q1.value(3).toInt() == 1){
            ui->readList->addItem(q1.value(0).toString());
        }

    }
};

// open student list window
void adminpage::on_pushButton_clicked()
{
    studentlist *newStudentListWindow = new class studentlist;
    newStudentListWindow->show();
    close();
}

// sign out
void adminpage::on_signOutButton_clicked()
{
//    listOfStudents = {};
//    listOfAdmin = {};
    currentUser = {};
    newLoginWindow->show();
    close();
}

// new message
void adminpage::on_newMessageButton_clicked()
{
    QSqlQuery q1;
    q1.exec("SELECT * FROM login");
    while(q1.next()){
        infoForMessaging newStudent;
        newStudent.email = q1.value(0).toString();
        newStudent.fName = q1.value(2).toString();
        listOfStudents.push_back(newStudent);
    }
    sendmessage *newSendMessageWindow = new class sendmessage;
    newSendMessageWindow->show();


}

// unread messages (double click to open)
void adminpage::on_unreadList_itemDoubleClicked(QListWidgetItem *item)
{
    QString subject = item->text();
    QSqlQuery q1;
    q1.exec("SELECT *  FROM messages");
    while(q1.next()){
        if(q1.value(0).toString() == subject && q1.value(2).toString() == currentUser.email){
           currentMessageAdmin = q1.value(0).toString();
        }
    }
    q1.prepare("UPDATE messages SET read=:read WHERE subject=:subject AND email=:email");
    q1.bindValue(":read", 1);
    q1.bindValue(":subject", subject);
    q1.bindValue(":email", currentUser.email);
    q1.exec();
    viewmessage *newViewMessageWindow = new class viewmessage;
    newViewMessageWindow->show();
    ui->readList->clear();
    ui->unreadList->clear();
    setMessages();

}

