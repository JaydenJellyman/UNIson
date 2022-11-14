#include "viewevent.h"
#include "ui_viewevent.h"
#include "events.h"
#include "login.h"
#include <QMessageBox>

viewevent::viewevent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewevent)
{
    ui->setupUi(this);

    // set window title
    this->setWindowTitle("Event - " + currentEvent.title);

    //signals
    connect(ui->completeButton,&QPushButton::clicked,this,&viewevent::markCompleteViewEvent);
    connect(ui->completeButton, &QPushButton::clicked, newHomeScreen, &homeScreen::setRating);
    connect(ui->completeButton, &QPushButton::clicked, newHomeScreen, &homeScreen::setTasksProgressEvents);

    // display event
    setViewEvent();
}

viewevent::~viewevent()
{
    delete ui;
}
// display event from currentEvent
void viewevent::setViewEvent(){

    ui->titleText->setText(currentEvent.title);
    ui->subjectText->setText(currentEvent.subject);
    ui->dueText->setText(currentEvent.due);
    ui->priorityText->setText(currentEvent.priority);
    ui->descriptionText->setText(currentEvent.description);
    if(currentEvent.repeat == true){
        ui->repeatText->setText("Yes");

    }else{
        ui->repeatText->setText("No");
    }
    if(currentEvent.reminder == true){
        ui->reminderText->setText("Yes");
    }else{
        ui->reminderText->setText("No");
    }


}

// mark event complete from inside view event window
void viewevent::markCompleteViewEvent(){

    for(int i = 0; i<savedEvents.size();i++){
        if(savedEvents[i].title == currentEvent.title){
            savedEvents[i].complete = true;
            currentUser.completedEvents++;

        }

    }
    currentEvent.complete = true;
    QMessageBox::information(this,"","event completed!");
    close();
}
// close when close is clicked
void viewevent::on_pushButton_clicked()
{
    close();
}

