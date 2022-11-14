#include "account.h"
#include "events.h"
#include "sendmessage.h"
#include "ui_account.h"
#include "login.h"
#include "tasks.h"
#include "notes.h"
#include "viewmessage.h"

account::account(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::account)
{
    ui->setupUi(this);


    // set message button image

    ui->newMessageButton->setStyleSheet("QPushButton {background-image: url(':/img/newmessage.png')}");


    ui->userName->setText(currentUser.fName + " " + currentUser.lName);
    ui->userEmail->setText(currentUser.email);
    ui->userRating->setText(QString::number(currentUser.rating)+"/5");

    setMessages();
}

account::~account()
{
    delete ui;
}
// sign out
void account::on_signOutButton_clicked(){



    QSqlQuery q1;
    QString temp = currentUser.fName;

    // delete current user from database and replace with currentUser and new user info(completed tasks ect)
    q1.prepare("DELETE FROM login WHERE firstName = '"+temp+"'");
    q1.exec();
    q1.prepare("INSERT INTO login (email, password, firstName, lastName, completedTasks, maxTasks, rating, "
               "completedEvents, maxCompletedEvents)"
                "VALUES (:email, :password, :firstName, :lastName, :completedTasks, :maxTasks, :rating,"
               ":completedEvents, :maxCompletedEvents)");
    q1.bindValue(":email", currentUser.email);
    q1.bindValue(":password", currentUser.password);
    q1.bindValue(":firstName", currentUser.fName);
    q1.bindValue(":lastName", currentUser.lName);
    q1.bindValue(":completedTasks",currentUser.completedTasks);
    q1.bindValue(":maxTasks",currentUser.maxTasks);
    q1.bindValue(":rating",currentUser.rating);
    q1.bindValue(":completedEvents",currentUser.completedEvents);
    q1.bindValue(":maxCompletedEvents",currentUser.maxEvents);
    q1.exec();

    // find all tasks in database for current user and delete them

    QString tempEmail = currentUser.email;
    for(int i=0; i < savedTasks.size(); i++){
        q1.prepare("DELETE FROM task WHERE email = '"+tempEmail+"'");
        q1.exec();
    }

    // add savedTasks to database

    for(int i = 0; i < savedTasks.size(); i++){
        q1.prepare("INSERT INTO task (title, subject, due, priority, email, complete)"
                      "VALUES (:title, :subject, :due, :priority, :email, :complete)");
        q1.bindValue(":title", savedTasks[i].title);
        q1.bindValue(":subject", savedTasks[i].subject);
        q1.bindValue(":due", savedTasks[i].due);
        q1.bindValue(":priority", savedTasks[i].priority);
        q1.bindValue(":email",currentUser.email);
        if(savedTasks[i].complete == true){
            q1.bindValue(":complete", 1);
        }else{
            q1.bindValue(":complete", 0);
        }
        q1.exec();
    }

    // find all tasks in database for current user and delete them

    for(int i=0; i < savedTasks.size(); i++){
        q1.prepare("DELETE FROM events WHERE email = '"+tempEmail+"'");
        q1.exec();
    }

    // add currentUser events to database

    for(int i = 0; i < savedEvents.size(); i++){

        q1.prepare("INSERT INTO events (title, subject, due, priority, description, email, repeat, reminder, complete)"
                      "VALUES (:title, :subject, :due, :priority, :description, :email, :repeat, :reminder, :complete)");
        q1.bindValue(":title", savedEvents[i].title);
        q1.bindValue(":subject", savedEvents[i].subject);
        q1.bindValue(":due", savedEvents[i].due);
        q1.bindValue(":priority", savedEvents[i].priority);
        q1.bindValue(":description", savedEvents[i].description);
        if(savedEvents[i].repeat == true){
            q1.bindValue(":repeat", 1);
        }else{
            q1.bindValue(":repeat", 0);
        }
        if(savedEvents[i].reminder == true){
            q1.bindValue(":reminder", 1);
        }else{
            q1.bindValue(":reminder", 0);
        }
        if(savedEvents[i].complete == true){
            q1.bindValue(":complete", 1);
        }else{
            q1.bindValue(":complete", 0);
        }
        q1.bindValue(":email",currentUser.email);
        q1.exec();
    }

//    listOfStudents = {};
//    listOfAdmin = {};

    login *newLoginWindow = new class login;
    newLoginWindow->show();
    close();

}
// save everything when app closed
void account::closeEvent(QCloseEvent *event){

    QSqlQuery q1;
    QString temp = currentUser.fName;

    // delete current user from database and replace with currentUser and new user info(completed tasks ect)
    q1.prepare("DELETE FROM login WHERE firstName = '"+temp+"'");
    q1.exec();

    q1.prepare("INSERT INTO login (email, password, firstName, lastName, completedTasks, maxTasks, rating, "
               "completedEvents, maxCompletedEvents)"
                "VALUES (:email, :password, :firstName, :lastName, :completedTasks, :maxTasks, :rating,"
               ":completedEvents, :maxCompletedEvents)");
    q1.bindValue(":email", currentUser.email);
    q1.bindValue(":password", currentUser.password);
    q1.bindValue(":firstName", currentUser.fName);
    q1.bindValue(":lastName", currentUser.lName);
    q1.bindValue(":completedTasks",currentUser.completedTasks);
    q1.bindValue(":maxTasks",currentUser.maxTasks);
    q1.bindValue(":rating",currentUser.rating);
    q1.bindValue(":completedEvents",currentUser.completedEvents);
    q1.bindValue(":maxCompletedEvents",currentUser.maxEvents);
    q1.exec();

    // find all tasks in database for current user and delete them

    QString tempEmail = currentUser.email;
    for(int i=0; i < savedTasks.size(); i++){
        q1.prepare("DELETE FROM task WHERE email = '"+tempEmail+"'");
        q1.exec();
    }

    // add savedTasks to database

    for(int i = 0; i < savedTasks.size(); i++){
        q1.prepare("INSERT INTO task (title, subject, due, priority, email, complete)"
                      "VALUES (:title, :subject, :due, :priority, :email, :complete)");
        q1.bindValue(":title", savedTasks[i].title);
        q1.bindValue(":subject", savedTasks[i].subject);
        q1.bindValue(":due", savedTasks[i].due);
        q1.bindValue(":priority", savedTasks[i].priority);
        q1.bindValue(":email",currentUser.email);
        if(savedTasks[i].complete == true){
            q1.bindValue(":complete", 1);
        }else{
            q1.bindValue(":complete", 0);
        }
        q1.exec();
    }

    // find all events in database for current user and delete them

    for(int i=0; i < savedTasks.size(); i++){
        q1.prepare("DELETE FROM events WHERE email = '"+tempEmail+"'");
        q1.exec();
    }

    // add currentUser events to database

    for(int i = 0; i < savedEvents.size(); i++){

        q1.prepare("INSERT INTO events (title, subject, due, priority, description, email, repeat, reminder, complete)"
                      "VALUES (:title, :subject, :due, :priority, :description, :email, :repeat, :reminder, :complete)");
        q1.bindValue(":title", savedEvents[i].title);
        q1.bindValue(":subject", savedEvents[i].subject);
        q1.bindValue(":due", savedEvents[i].due);
        q1.bindValue(":priority", savedEvents[i].priority);
        q1.bindValue(":description", savedEvents[i].description);
        if(savedEvents[i].repeat == true){
            q1.bindValue(":repeat", 1);
        }else{
            q1.bindValue(":repeat", 0);
        }
        if(savedEvents[i].reminder == true){
            q1.bindValue(":reminder", 1);
        }else{
            q1.bindValue(":reminder", 0);
        }
        if(savedEvents[i].complete == true){
            q1.bindValue(":complete", 1);
        }else{
            q1.bindValue(":complete", 0);
        }
        q1.bindValue(":email",currentUser.email);
        q1.exec();
    }
    // clear student and admin lists at logout
    listOfStudents = {};
    listOfAdmin = {};



}
// set messages (read and unread)
void account::setMessages(){

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
}


// menu bar actions
void account::on_actionHome_triggered()
{
    newHomeScreen->show();
    close();
}
void account::on_actionView_Notes_triggered()
{
    notes *newNoteWindow = new class notes;
    newNoteWindow->show();
    close();
}


// unread messages (double click to open)
void account::on_unreadList_itemDoubleClicked(QListWidgetItem *item)
{
    QString subject = item->text();
    QSqlQuery q1;
    q1.exec("SELECT *  FROM messages");
    while(q1.next()){
        if(q1.value(0).toString() == subject && q1.value(2).toString() == currentUser.email){
           currentMessageUser = q1.value(0).toString();
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

// send new message
void account::on_newMessageButton_clicked()
{
    QSqlQuery q1;
    q1.exec("SELECT * FROM admin");
    while(q1.next()){
        infoForMessaging newAdmin;
        newAdmin.email = q1.value(0).toString();
        newAdmin.fName = q1.value(2).toString();
        listOfAdmin.push_back(newAdmin);
    }
    sendmessage *newSendMessageWindow = new class sendmessage;
    newSendMessageWindow->show();
}

