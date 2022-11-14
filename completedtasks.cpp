#include "completedtasks.h"
#include "ui_completedtasks.h"
#include "tasks.h"

completedtasks::completedtasks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::completedtasks)
{
    ui->setupUi(this);
    setCompletedTasks();
}

completedtasks::~completedtasks()
{
    delete ui;
}
// close
void completedtasks::on_closeButton_clicked()
{
    close();
}

// display completed tasks
void completedtasks::setCompletedTasks(){

    for(int i = 0; i<savedTasks.size(); i++){
        if(savedTasks[i].complete == true){
            ui->completedList->addItem(savedTasks[i].title);

        }
    }
}
