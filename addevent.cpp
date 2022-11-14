#include "addevent.h"
#include "ui_addevent.h"
#include "events.h"
#include "qmessagebox.h"
#include "login.h"


addevent::addevent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addevent)
{
    ui->setupUi(this);

    // set dateEdit format to match what we will be searching for later on calendarView page
    ui->dateEdit->setDisplayFormat("MMM d yyyy");

    //set to QDateEdit current date
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);

    //signals
    connect(ui->saveButton,&QPushButton::clicked, this, &addevent::saveEvent);
    connect(ui->saveButton,&QPushButton::clicked, newHomeScreen,&homeScreen::setRating);
    connect(ui->saveButton,&QPushButton::clicked, newHomeScreen,&homeScreen::setTasksProgressEvents);
}

addevent::~addevent()
{
    delete ui;
}

// save event
void addevent::saveEvent(){

    QString tempDue(ui->dateEdit->text());


    struct event event1;
    event1.title = ui->titleLine->text();
    event1.subject = ui->subjectLine->text();
    event1.due = tempDue;
    event1.priority = ui->priorityLine->text();
    event1.description = ui->descriptionLine->toPlainText();
    event1.complete = false;
    if(ui->reminderCheckBox->isChecked()){
        event1.reminder = true;
    }
    if(ui->repeatCheckBox->isChecked()){
        event1.repeat = true;
    }
    savedEvents.push_back(event1);
    currentUser.maxEvents++;

    // add to database
    QSqlQuery q1;
    q1.prepare("INSERT INTO events (title, subject, due, priority, description, email, repeat, reminder, complete)"
                  "VALUES (:title, :subject, :due, :priority, :description, :email, :repeat, :reminder, :complete)");
    q1.bindValue(":title", event1.title);
    q1.bindValue(":subject", event1.subject);
    q1.bindValue(":due", event1.due);
    q1.bindValue(":priority", event1.priority);
    q1.bindValue(":description", event1.description);
    if(event1.repeat == true){
        q1.bindValue(":repeat", 1);
    }else{
        q1.bindValue(":repeat", 0);
    }
    if(event1.reminder == true){
        q1.bindValue(":reminder", 1);
    }else{
        q1.bindValue(":reminder", 0);
    }
    q1.bindValue(":email",currentUser.email);
    q1.bindValue(":complete", 0);
    q1.exec();


    qDebug() << "event saved!";
    QMessageBox::information(this,"","event saved!");
    close();
}
// close when cancel button clicked
void addevent::on_cancelButton_clicked()
{
    close();
}


