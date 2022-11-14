#include "replymessage.h"
#include "login.h"
#include "ui_replymessage.h"
#include "viewmessage.h"
#include "qmessagebox.h"
replymessage::replymessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::replymessage)
{
    ui->setupUi(this);
    // show who you are replying to
    ui->recipientLabel->setText(senderName);
}

replymessage::~replymessage()
{
    delete ui;
}

// send message (save toc dB to be read later)
void replymessage::on_sendButton_clicked()
{


    QSqlQuery q1;
    q1.prepare("INSERT INTO messages (subject, message, email, sender, read) VALUES (:subject, :message, :email, :sender, :read)");
    q1.bindValue(":subject", ui->subjectText->text());
    q1.bindValue(":message", ui->messageText->toPlainText());
    q1.bindValue(":email", senderEmail);
    q1.bindValue(":sender", currentUser.email);
    q1.bindValue(":read", 0);
    q1.exec();
    QMessageBox::information(this, "sent", "message sent!");
    close();







}

