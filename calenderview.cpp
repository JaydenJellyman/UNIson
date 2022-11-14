#include "calenderview.h"
#include "events.h"
#include "tasks.h"
#include "ui_calenderview.h"
#include "homescreen.h"

calenderView::calenderView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calenderView)
{
    ui->setupUi(this);

    // display date in full format at top of page
    this->setWindowTitle(calenderDate);

    // grab tasks and events with corrosponding date
    ui->label->setText(calenderDate);
    for(int i = 0; i < savedTasks.size(); i++){
        if(newCalenderDate == savedTasks[i].due){
            if(savedTasks[i].complete == false){
                ui->taskList->addItem(savedTasks[i].title);
            }

        }
    }
    for(int i = 0; i < savedEvents.size(); i++){
        if(newCalenderDate == savedEvents[i].due){
            if(savedEvents[i].complete == false){
                ui->eventList->addItem(savedEvents[i].title);

            }
        }
    }

}
calenderView::~calenderView()
{
    delete ui;
}


