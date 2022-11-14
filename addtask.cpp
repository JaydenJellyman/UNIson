#include "addtask.h"
#include "login.h"
#include "ui_addtask.h"
#include "tasks.h"
#include "homescreen.h"
#include "users.h"
#include <QMessageBox>

addtask::addtask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addtask)
{
    ui->setupUi(this);

    // set dateEdit format to match what we will be searching for later on calendarView page
    ui->dateEdit->setDisplayFormat("MMM d yyyy");

    //set to QDateEdit current date
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);

    // signals
    connect(ui->saveButton, &QPushButton::clicked, this, &addtask::saveTask); // connect save button to saveTask()
    connect(ui->saveButton, &QPushButton::clicked, newHomeScreen ,&homeScreen::setRating);
    connect(ui->saveButton, &QPushButton::clicked, newHomeScreen ,&homeScreen::setTasksProgressEvents); // connect save button to setTasksProgress() ( refresh taskList and progress on home screen when save button clicked)



}

addtask::~addtask()
{
    delete ui;
}

// save task slot
void addtask::saveTask(){

    QString tempDue(ui->dateEdit->text());

    task task1;

    task1.title = ui->titleLine->text();
    task1.subject = ui->subjectLine->text();
    task1.due = tempDue;
    task1.priority = ui->priorityLine->text();
    task1.complete = false;
    savedTasks.push_back(task1);
    currentUser.maxTasks++;


    // add to database

    //new query
    QSqlQuery q1;
    // where and what we will be saving

    q1.prepare("INSERT INTO task (title, subject, due, priority, email, complete)"
                  "VALUES (:title, :subject, :due, :priority, :email, :complete)");

    // bind values to the where and whats
    q1.bindValue(":title", task1.title);
    q1.bindValue(":subject", task1.subject);
    q1.bindValue(":due", task1.due);
    q1.bindValue(":priority", task1.priority);
    q1.bindValue(":email",currentUser.email);
    q1.bindValue(":complete", 0);
    // execute
    q1.exec();




}
// additional save task slot, for dialog
void addtask::on_saveButton_clicked()
{
    QMessageBox::information(this, "saved", "task saved!");
    close();
}
// close when cancel button clicked
void addtask::on_cancelButton_clicked()
{
    close();
}

