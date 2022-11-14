#include "viewmessage.h"
#include "account.h"
#include "qsqlquery.h"
#include "replymessage.h"
#include "ui_viewmessage.h"
#include "adminpage.h"


viewmessage::viewmessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewmessage)
{
    ui->setupUi(this);
    setWindowTitle("Message");
    setMessage();
}

viewmessage::~viewmessage()
{
    delete ui;
}

// set previously selected message on screen
void viewmessage::setMessage()
{

    // setting the message on screen

    QSqlQuery q1;

    // search user messages

    q1.exec("SELECT * FROM messages");

    while(q1.next()){
        if(currentUser.isAdmin == 0){
            if(q1.value(0).toString() == currentMessageUser && q1.value(2).toString()== currentUser.email){
                ui->subjectText->setText(q1.value(0).toString());
                senderName = q1.value(4).toString();
                senderEmail = q1.value(4).toString();

                ui->fromText->setText(senderName);
                ui->messageText->setText(q1.value(1).toString());
            }

        }else{

            if(q1.value(0).toString() == currentMessageAdmin && q1.value(2).toString()== currentUser.email){
                ui->subjectText->setText(q1.value(0).toString());
                senderName = q1.value(4).toString();
                senderEmail = q1.value(4).toString();

                ui->fromText->setText(senderName);
                ui->messageText->setText(q1.value(1).toString());
            }
        }



    }
}




// reply to message
void viewmessage::on_replyButton_clicked()
{
    replymessage *newReplyMessageWindow = new class replymessage;
    newReplyMessageWindow->show();
    close();
}

//close button
void viewmessage::on_pushButton_clicked()
{
    close();
}




