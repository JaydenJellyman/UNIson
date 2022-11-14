#include "adminpin.h"
#include "qmessagebox.h"
#include "ui_adminpin.h"
#include "login.h"


adminpin::adminpin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminpin)
{
    ui->setupUi(this);

    // signals
    connect(ui->pushButton, &QPushButton::clicked, newLoginWindow, &login::adminSignUp);

}

adminpin::~adminpin()
{
    delete ui;
}

// verify user entered admin pin with database
void adminpin::on_pushButton_clicked()
{
    QString pin = ui->pinEdit->text(); //user input into string varible
    QSqlQuery q1; // new query
    q1.exec("SELECT * FROM adminPins"); // select adminPins in database
    while(q1.next()){ // check each record in adminPins
        if(pin == q1.value(0).toString()){ //if user entered pin matches a record
            pinCorrect = true; // set pinCorrect to true (delcared in header so it is accesible to other classes)
            qDebug() << "pin found"; // debug checking
            close();

        }else{
            QMessageBox::information(this,"pin","pin incorrect"); // dialog to inform user pin not correct
        }
    }

}

