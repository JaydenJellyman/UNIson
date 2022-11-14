#include "eventreminder.h"
#include "events.h"
#include "ui_eventreminder.h"


eventreminder::eventreminder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::eventreminder)
{
    ui->setupUi(this);
    // set window title
    setWindowTitle("Todays Events");

    // set window to always on top
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);



    // set events in list
    setEvents();


}

eventreminder::~eventreminder()
{
    delete ui;
}

void eventreminder::on_closeButton_clicked()
{
    close();
}


void eventreminder::setEvents(){

    // set events
    for(int i = 0; i<todaysEvents.size();i++){

        ui->eventsList->addItem(todaysEvents[i].title);

    }


}
