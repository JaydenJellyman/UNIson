#include "homescreen.h"
#include "calenderview.h"
#include "events.h"
#include "ui_homescreen.h"
#include "addtask.h"
#include "viewtask.h"
#include "tasks.h"
#include "account.h"
#include "completedtasks.h"
#include "notes.h"
#include "addevent.h"
#include "viewevent.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCloseEvent>
#include <QAction>
#include <QMessageBox>
#include "eventreminder.h"
#include <QMediaPlayer>





homeScreen::homeScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::homeScreen)
{
    ui->setupUi(this);





    // set window title
    setWindowTitle("UNIson");


    // check current user name
    qDebug() << "current user is: " + currentUser.fName;

    // set button images
     ui->deleteTaskButton->setStyleSheet("QPushButton {background-image: url(':/img/delete.png')}");
     ui->completeButton->setStyleSheet("QPushButton {background-image: url(':/img/complete.png')}");
     ui->deleteEventButton->setStyleSheet("QPushButton {background-image: url(':/img/delete.png')}");


    // signals
    connect(ui->deleteTaskButton, &QPushButton::clicked, this, &homeScreen::deleteTask); // connect delete button to deleteTask slot
    connect(ui->deleteTaskButton, &QPushButton::clicked, this, &homeScreen::setRating);
    connect(ui->deleteTaskButton, &QPushButton::clicked, this, &homeScreen::setTasksProgressEvents);
    connect(ui->addTaskButton,&QPushButton::clicked, this, &homeScreen::addTasks); // connect add task button to addTasks slot (open new add task popup)
    connect(ui->viewTaskButton,&QPushButton::clicked, this, &homeScreen::viewTask);// connect view task button to viewTask slot (open new view task window)
    connect(ui->completeButton,&QPushButton::clicked, this, &homeScreen::markCompleteHomeSreen);
    connect(ui->completeButton, &QPushButton::clicked, this, &homeScreen::setRating);
    connect(ui->completeButton, &QPushButton::clicked, this, &homeScreen::setTasksProgressEvents);        
    connect(ui->addEventButton,&QPushButton::clicked, this, &homeScreen::addEvents);
    connect(ui->deleteEventButton, &QPushButton::clicked, this, &homeScreen::deleteEvents); // connect delete button to deleteEvent slot
    connect(ui->deleteEventButton, &QPushButton::clicked, this, &homeScreen::setRating);
    connect(ui->deleteEventButton, &QPushButton::clicked, this, &homeScreen::setTasksProgressEvents);
    connect(ui->viewEventButton,&QPushButton::clicked, this, &homeScreen::viewEvent);



    // get tasks/events/notes from database for current user
    getTasksEventsNotesFromDatabase();

    // set tasks/events/progress on home screen
    setTasksProgressEvents();

    checkMessages();
    connect(viewMessage, &QAction::triggered, this, &homeScreen::newAccountPage);
    // call event reminder function
    eventReminder();




}







homeScreen::~homeScreen()
{
    delete ui;
}


void homeScreen::getTasksEventsNotesFromDatabase(){

    // query for retrieving current users tasks from students.db

    QSqlQuery q1; // new query
    q1.exec("SELECT * FROM task"); // grab from task table in students.db
    while(q1.next()){ // loop through all records in task table
        if(q1.value(4).toString() == currentUser.email){ // if task identifier(users email) is the same as current user
            task newTask; // new task
            newTask.title = q1.value(0).toString(); // pass record into new task
            newTask.subject = q1.value(1).toString();
            newTask.due = q1.value(2).toString();
            newTask.priority = q1.value(3).toString();
            if(q1.value(5).toInt() == 1){ // mark task as complete or not complete
                newTask.complete = true;
                qDebug() << "completed tasks found";

            }else{
                newTask.complete = false;
                qDebug() << "tasks found";
            }


            savedTasks.push_back(newTask); // add new task to savedTasks vector

        }
    }
    // query for retrieving current users events from students.db

    QSqlQuery q2;
    q2.exec("SELECT * FROM events");
    while(q2.next()){
        if(q2.value(5).toString() == currentUser.email){
            struct event newEvent;
            newEvent.title = q2.value(0).toString();
            newEvent.subject = q2.value(1).toString();
            newEvent.due = q2.value(2).toString();
            newEvent.priority = q2.value(3).toString();
            newEvent.description = q2.value(4).toString();
            newEvent.complete = false;
            if(q2.value(6) == 1){
                newEvent.reminder = true;
            }else{
                newEvent.reminder = false;
            }
            if(q2.value(7) == 1){
                newEvent.repeat = true;
            }else{
                newEvent.repeat = false;
            }
            if(q2.value(8).toInt() == 1){
                newEvent.complete = true;
                qDebug() << "completed event found";

            }else{
                newEvent.complete = false;
                qDebug() << "event found";
            }
            savedEvents.push_back(newEvent);

        }
    }
    // query for retrieving current users notes from students.db
    QSqlQuery q3;
    q3.exec("SELECT * FROM notes");
    while(q3.next()){
        if(q3.value(3).toString() == currentUser.email){
            note newNote;
            newNote.title = q3.value(0).toString();
            newNote.subject = q3.value(1).toString();
            newNote.body = q3.value(2).toString();
            savedNotes.push_back(newNote);
            qDebug() << "notes found";
        }
    }
}



// slot definitions (declared in homescreen.h)
void homeScreen::setTasksProgressEvents(){ // show tasks/progress/events on home screen


        // clear task list
        ui->taskList->clear();
        // clear event list
        ui->eventsList->clear();

        // set tasks
        for(int i = 0; i<savedTasks.size();i++){
            if(savedTasks[i].complete == false){ // only show non complete tasks
            ui->taskList->addItem(savedTasks[i].title);
            }
        }

        // set progress
        ui->userRatingLabel->setText(QString::number(currentUser.rating)+"/5");
        ui->userCompletedEventsLabel->setText(QString::number(currentUser.completedEvents)
                                              + "/" + QString::number(currentUser.maxEvents));
        ui->userCompletedTasksLabel->setText(QString::number(currentUser.completedTasks)
                                              + "/" + QString::number(currentUser.maxTasks));



        // set events
        for(int i = 0; i<savedEvents.size();i++){
            if(savedEvents[i].complete == false){
            ui->eventsList->addItem(savedEvents[i].title);
            }
        }


    }

void homeScreen::deleteTask(){ // delete selected task from taskList and savedTasks vector

    QString temp;
    // check if task is selected
    if (ui->taskList->selectedItems().size() !=0){
        temp = ui->taskList->currentItem()->text(); // set selected task title to temp var
        for(int i = 0; i < savedTasks.size(); ){
            if(savedTasks[i].title == temp){
                if(savedTasks.size() > 1){
                    savedTasks.removeAt(i);
                    qDebug()<<"removed from vector";
                    // delete from database
                    QSqlQuery q1;
                    q1.prepare("DELETE FROM task WHERE title = '"+temp+"'");
                    q1.exec();
                    qDebug() << "deleted";
                    // message box

                    break;
                }else if(savedTasks.size() == 1){
                    savedTasks.clear();
                    qDebug() << "vector cleared";
                    // delete from database
                    QSqlQuery q1;
                    q1.prepare("DELETE FROM task WHERE title = '"+temp+"'");
                    q1.exec();
                    qDebug() << "deleted";
                    // message box
                    QMessageBox::information(this, "deleted", temp + " deleted!");
                    break;
                }
            }else{
                i++;
            }
        }
    }else{

        QMessageBox::information(this, "error","no task selected!");
    }
    currentUser.maxTasks--;
}
// open new add task popup
void homeScreen::addTasks(){


    addtask *addTaskWindow = new addtask;
    addTaskWindow->show();

}
// open new view task window and set selected task to currentTask
void homeScreen::viewTask(){

    // check if task is selected
    if(ui->taskList->selectedItems().size() != 0){
        for(int i = 0; i<savedTasks.size();i++){
            if(ui->taskList->currentItem()->text() == savedTasks[i].title){
                currentTask = savedTasks[i];
            }
        }
        viewtask *newViewTaskWindow = new viewtask;
        newViewTaskWindow->show();
    }else{
        QMessageBox::information(this, "Error", "No task selected");
    }

}
// mark task complete functon specific to home screen
void homeScreen::markCompleteHomeSreen(){

    QString temp;
    // check if task is selected
    if(ui->taskList->selectedItems().size() != 0){
        temp = ui->taskList->currentItem()->text();
        for(int i = 0; i<savedTasks.size();i++){
            if(savedTasks[i].title == temp && savedTasks[i].complete == false){
                savedTasks[i].complete = true;
                currentUser.completedTasks++;
            }
        }
        QMessageBox::information(this,temp,"task completed!");
    }else {
        QMessageBox::information(this,"error","no task selected");

    }

}
// open new add event popup
void homeScreen::addEvents(){
    addevent *newAddEventWindow = new class addevent;
    newAddEventWindow->show();
}
// delete selected task from taskList and savedTasks vector
void homeScreen::deleteEvents(){
    QString temp;
    // check if event is selected
    if(ui->eventsList->selectedItems().size() !=0){
        // set selected task title to temp var
        temp = ui->eventsList->currentItem()->text();
        for(int i = 0; i < savedEvents.size(); ){
            if(savedEvents[i].title == temp){
                if(savedEvents.size() > 1){
                    savedEvents.removeAt(i);
                    qDebug()<<"removed from vector";
                    // delete from database
                    QSqlQuery q1;
                    q1.prepare("DELETE FROM events WHERE title = '"+temp+"'");
                    q1.exec();
                    // message box
                    QMessageBox::information(this, temp, temp + " deleted!");
                    break;
                }else if(savedEvents.size() == 1){
                    savedEvents.clear();
                    qDebug() << "vector cleared";
                    // delete from database
                    QSqlQuery q1;
                    q1.prepare("DELETE FROM events WHERE title = '"+temp+"'");
                    q1.exec();
                    // message box
                    QMessageBox::information(this, temp, temp + " deleted!");
                        break;
                }
            }else{
                i++;
            }
        }
    }else{
        QMessageBox::information(this, "error", "No task selected!");
    }
    currentUser.maxEvents--;
}

// set selected event to currentEvent and open new view event window
void homeScreen::viewEvent(){

    // check if event is selected
    if(ui->eventsList->selectedItems().size() != 0){

        for(int i = 0; i<savedEvents.size();i++){
            if(ui->eventsList->currentItem()->text() == savedEvents[i].title){
                currentEvent = savedEvents[i];
            }
        }

        viewevent *newViewEventWindow = new class viewevent;
        newViewEventWindow->show();
    }else{

        QMessageBox::information(this, "Error", "No event selected");
    }

}

// set rating
void homeScreen::setRating(){

    float max = currentUser.maxTasks + currentUser.maxEvents;
    float complete = currentUser.completedTasks + currentUser.completedEvents;
    float percent = (complete / max)*100;
    if(percent < 20){
        currentUser.rating = 0;
    }else if(percent >= 20 && percent < 40){
        currentUser.rating = 1;
    }else if(percent >= 40 && percent < 60){
        currentUser.rating = 2;
    }else if(percent >= 60 && percent < 80){
        currentUser.rating = 3;
    }else if (percent >=80 && percent < 100){
        currentUser.rating = 4;
    }else{
        currentUser.rating = 5;
    }
}


// menu bar slots
void homeScreen::on_actionMy_Account_triggered()
{
    account *account = new class account;
    account->show();
    close();
}
void homeScreen::on_actionCompleted_Tasks_triggered()
{
    completedtasks *newCompletedTasksWindow = new class completedtasks;
    newCompletedTasksWindow->show();
}
void homeScreen::on_actionNotes_triggered()
{
    notes *newNoteWindow = new class notes;
    newNoteWindow->show();
    close();
}

// store date and modify to be read in calendar view class
void homeScreen::on_calendarWidget_clicked(const QDate &date)
{
    // get clicked date and set to variable
    calenderDate = date.toString();

    // set same to to new variable so we can keep the original one to display on calendarView page
    newCalenderDate = calenderDate;

    // remove the first 4 charcters (ie "Tue " or " Wed ") and be left with just the date (ie "Nov 1 2022")
    // we will use this variable to search through savedTasks and savedEvents
    newCalenderDate.remove(0,4);

    // debug check
    qDebug() << newCalenderDate;









    calenderView *calender = new class calenderView;
    calender->show();


}

// save eveything if user closes app without logging out
void homeScreen::closeEvent(QCloseEvent *event){

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



}

void homeScreen::checkMessages(){

    bool found = false;
    QSqlQuery q1;
    q1.exec("SELECT * FROM messages");
    while(q1.next() && found == false){

        if(q1.value(3).toInt() == 0 && q1.value(2).toString() == currentUser.email){
            found = true;
        }
    }
    if(found == true){
        newMessage = new QMenu("New Message!");
        newMessage->setStyleSheet("color:red");

        ui->menubar->addMenu(newMessage);
        viewMessage = new QAction("View Messages");
        newMessage->addAction(viewMessage);



    }

}

void homeScreen::newAccountPage(){
    account *account = new class account;
    account->show();
    close();
}


void homeScreen::eventReminder(){




    // set date to current date and convert to appropriate string format for event reminders
    date = QDate::currentDate();
    newDate = date.toString();
    newDate.remove(0,4);


    // check events for todays events and add to vector
    for(int i = 0; i<savedEvents.size(); i++){
        if(savedEvents[i].due == newDate && savedEvents[i].reminder == true){
            todaysEvents.push_back(savedEvents[i]);
        }
    }
    if(savedEvents.size() != 0){
        eventreminder *newEventReminderWindow = new class eventreminder;
        newEventReminderWindow->show();
    }



}
