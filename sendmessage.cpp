#include "sendmessage.h"
#include "login.h"
#include "qsqlquery.h"
#include "ui_sendmessage.h"
#include "qmessagebox.h"

sendmessage::sendmessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sendmessage)
{
    ui->setupUi(this);

    // display names of recipients depending on admin or user account
    if(currentUser.isAdmin == 1){
        for(int i = 0; i<listOfStudents.size(); i++){
            ui->recipientBox->addItem(listOfStudents[i].fName);
        }
    }else{
        for(int i = 0; i<listOfAdmin.size(); i++){


            ui->recipientBox->addItem(listOfAdmin[i].fName);
        }
    }


}

sendmessage::~sendmessage()
{
    delete ui;
}

// send message
void sendmessage::on_pushButton_clicked()
{

    QString subject = ui->subjectText->text();
    QString message = ui->messageText->toPlainText();

    QSqlQuery q1;
    q1.prepare("INSERT INTO messages (subject, message, email, read, sender)" "VALUES(:subject, :message, :email, :read, :sender)");
    q1.bindValue(":subject",subject);
    q1.bindValue(":message",message);
    q1.bindValue(":read",0);
    q1.bindValue(":sender", currentUser.fName);
    QString recipient = ui->recipientBox->currentText();
    if(currentUser.isAdmin == 1){
        for(int i = 0; i < listOfStudents.size(); i++){
            if (listOfStudents[i].fName == recipient){
                q1.bindValue(":email",listOfStudents[i].email);
                qDebug() << "email";
            }
        }

    }else{
        for(int i = 0; i < listOfAdmin.size(); i++){
            if (listOfAdmin[i].fName == recipient){
                q1.bindValue(":email",listOfAdmin[i].email);
                qDebug() << "email";
            }
        }

    }

    q1.exec();
    QMessageBox::information(this, "sent", "message sent!");
    close();


}

// close event (clear lists so we dont end up with multiples)
void sendmessage::closeEvent(QCloseEvent *event){

    listOfAdmin = {};
    listOfStudents = {};
}
