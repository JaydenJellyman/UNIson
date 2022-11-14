#include "notes.h"
#include "events.h"
#include "tasks.h"
#include "ui_notes.h"
#include "account.h"
#include "completedtasks.h"
#include "login.h"
#include "users.h"
#include <QMessageBox>


notes::notes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::notes)
{

    // set window title
    setWindowTitle("UNIson - Notes");

    ui->setupUi(this);
    setNotes();

    connect(ui->saveNoteButton, &QPushButton::clicked, this, &notes::setNotes);
}

notes::~notes()
{
    delete ui;
}
// menu bar action slots
void notes::on_actionMy_Account_triggered()
{
    account *account = new class account;
    account->show();
    close();
}

void notes::on_actionCompleted_Tasks_triggered()
{

    completedtasks *newCompletedTasksWindow = new class completedtasks;
    newCompletedTasksWindow->show();
}

void notes::on_actionHome_triggered()
{
    newHomeScreen->show();
    close();
}


// display notes in list
void notes::setNotes(){
    ui->notesList->clear();
    for(int i = 0; i<savedNotes.size(); i++){

        ui->notesList->addItem(savedNotes[i].title);

    }

}
//save note
void notes::on_saveNoteButton_clicked()
{
    QString title = ui->titleText->text();
    QString subject = ui->subjectText->text();
    QString body = ui->bodyText->toPlainText();
    note newNote{title, subject, body};
    savedNotes.push_back(newNote);
    ui->titleText->clear();
    ui->subjectText->clear();
    ui->bodyText->clear();
    QMessageBox::information(this,"Note Saved", "Your note has been saved!");

    // add to database

    QSqlQuery q1;
    q1.prepare("INSERT INTO notes (title, subject, description, email)"
               "VALUES (:title, :subject, :description, :email)");
    q1.bindValue(":title",newNote.title);
    q1.bindValue(":subject", newNote.subject);
    q1.bindValue(":description", newNote.body);
    q1.bindValue(":email", currentUser.email);
    q1.exec();

}
// view note on screen
void notes::on_viewNoteButton_clicked()
{
    QString text;
    // check if note is selected and view note
    if(ui->notesList->selectedItems().size() != 0){
        text = ui->notesList->currentItem()->text();
        for(int i =0; i<savedNotes.size();i++){
            if(savedNotes[i].title == text){
                ui->titleLabel_2->setText(savedNotes[i].title);
                ui->subjectLabel_2->setText(savedNotes[i].subject);
                ui->bodyLabel_2->setText(savedNotes[i].body);
            }
        }
    }else {
        QMessageBox::information(this, "Error", "No note selected");
    }


}
// delete note
void notes::on_deleteNoteButton_clicked()
{
    QString temp;
    QSqlQuery q1;
    // check if note is selected and delete note
    if(ui->notesList->selectedItems().size() != 0){
        temp = ui->notesList->currentItem()->text();
        for(int i = 0; i<savedNotes.size(); i++){
            if(savedNotes.size() > 1){
                savedNotes.removeAt(i);
                q1.exec("DELETE FROM notes WHERE title = '"+temp+"'");
                QMessageBox::information(this, temp, temp + " deleted!");

            }else if(savedNotes.size() == 1){
                savedNotes.clear();
                q1.exec("DELETE FROM notes WHERE title = '"+temp+"'");
                QMessageBox::information(this, temp, temp + " deleted!");
            }
        }

        ui->notesList->takeItem(ui->notesList->currentRow());
    }else{
        QMessageBox::information(this, "Error", "No note selected!");
    }
    // if deleted task is most recently viewed task, clear labels from viewTask
    if(temp == ui->titleLabel_2->text()){
        ui->titleLabel_2->clear();
        ui->subjectLabel_2->clear();
        ui->bodyLabel_2->clear();
    }

}
// save everything if user closes app without signing out
void notes::closeEvent(QCloseEvent *event){

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



}


