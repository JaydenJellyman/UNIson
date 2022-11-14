#include "viewtask.h"
#include "ui_viewtask.h"
#include "tasks.h"
#include "login.h"
#include <QMessageBox>


viewtask::viewtask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewtask)
{
    ui->setupUi(this);

    // set window title
    this->setWindowTitle("Task - " + currentTask.title);

    // display task
    setViewTask();

    // signals
    connect(ui->completeButton, &QPushButton::clicked, this, &viewtask::markCompleteViewTask);
    connect(ui->completeButton, &QPushButton::clicked, newHomeScreen, &homeScreen::setTasksProgressEvents);
}

viewtask::~viewtask()
{
    delete ui;
}

// display task
void viewtask::setViewTask(){

    ui->titleText->setText( currentTask.title);
    ui->subjectText->setText( currentTask.subject);
    ui->dueText->setText( currentTask.due);
    ui->priorityText->setText( currentTask.priority);
}

// mark task complete from inside view task window
void viewtask::markCompleteViewTask(){

    for(int i = 0; i<savedTasks.size();i++){
        if(savedTasks[i].title == currentTask.title){
            savedTasks[i].complete = true;
            currentUser.completedTasks++;

        }

    }

    currentTask.complete = true;
    QMessageBox::information(this,"","task completed!");
    close();
}

// close window
void viewtask::on_closeButton_clicked()
{
    currentTask = {}; // clear currentTask
    close();
}

