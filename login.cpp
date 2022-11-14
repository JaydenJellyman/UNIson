#include "login.h"
#include "./ui_login.h"
#include "users.h"
#include "adminpin.h"
#include "adminpage.h"


login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    // hide password
    ui->loginPassword->setEchoMode(QLineEdit::Password);
    ui->signUpPassword->setEchoMode(QLineEdit::Password);

    // debug check
    if(QFile::exists("studentsDb.db")){
        qDebug() <<"db exists";
    }


    // establish and open database connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("studentsDb.db");
    db.open();

    // display connection status
    if(db.isOpen()){
        ui->connectionLabel->setText("<font color='green'>Connected</font>");
    }else{
        ui->connectionLabel->setText("<font color='red'>Not Connected</font>");
    }

    // button styling
    ui->loginButton->setStyleSheet("border-style: solid; background-color: #f25a3c; border-radius: 10px;");
    ui->signUpButton->setStyleSheet("border-style: solid; background-color: #f25a3c; border-radius: 10px;");
    ui->adminSignUpButton->setStyleSheet("border-style: solid; background-color: #f25a3c; border-radius: 10px;");


    // set tab order

    setTabOrder(ui->loginName, ui->loginPassword);
    setTabOrder(ui->loginPassword, ui->loginButton);
    setTabOrder(ui->loginButton, ui->signUpFName);
    setTabOrder(ui->signUpFName, ui->signUpLName);
    setTabOrder(ui->signUpLName, ui->signUpEmail);
    setTabOrder(ui->signUpEmail, ui->signUpPassword);
    setTabOrder(ui->signUpPassword, ui->signUpButton);
    setTabOrder(ui->signUpButton, ui->adminSignUpButton);

}

login::~login()
{
    delete ui;
}

// verify user in database and log in
void login::on_loginButton_clicked()
{


    // new query
    QSqlQuery q;
    // bool variable for if user is founf
    bool userFound = false;
    bool adminFound = false;

    // read from login table

    q.exec("SELECT * FROM login");
    while(q.next()){ // store users input in temp string variables and check database for matching user
        QString tempEmail= ui->loginName->text();
        QString tempPassword = ui->loginPassword->text();
        if(tempEmail == q.value(0).toString() &&tempPassword == q.value(1).toString() )
            {
                QString data;
                int dataNum;
                userFound = true;
                data = q.value(0).toString();
                currentUser.email = data;
                data = q.value(1).toString();
                currentUser.password = data;
                data = q.value(2).toString();
                currentUser.fName = data;
                data = q.value(3).toString();
                currentUser.lName = data;
                dataNum = q.value(4).toInt();
                currentUser.completedTasks = dataNum;
                dataNum = q.value(5).toInt();
                currentUser.maxTasks = dataNum;
                dataNum = q.value(7).toInt();
                currentUser.completedEvents = dataNum;
                dataNum = q.value(8).toInt();
                currentUser.maxEvents = dataNum;
                currentUser.isAdmin = 0;


                break;
                }
        else{
                userFound = false;
            }
    }


    // read from admin table

    q.exec("SELECT * FROM admin");
    while(q.next()){ // store users input in temp string variables and check database for matching user
        QString tempEmail= ui->loginName->text();
        QString tempPassword = ui->loginPassword->text();
        if(tempEmail == q.value(0).toString() &&tempPassword == q.value(1).toString() ){
            adminFound = true;
            QString data;
            data = q.value(0).toString();
            currentUser.email = data;
            data = q.value(1).toString();
            currentUser.password = data;
            data = q.value(2).toString();
            currentUser.fName = data;
            data = q.value(3).toString();
            currentUser.lName = data;
            currentUser.isAdmin = 1;
        }else{
            adminFound = false;
        }
    }


    // login appropriatly if user or admin found

    if(adminFound == true || userFound == true){
        // if user found then launch home screen
        if(userFound == true){
            newHomeScreen = new homeScreen; // define newHomeScreen (declared in header)
            newHomeScreen->show();
            close();
        }
        // if admin found then launch admin screen
        if(adminFound == true){
            adminpage *newAdminPageWindow = new class adminpage;
            newAdminPageWindow->show();
            close();
        }
    }else{
        QMessageBox::information(this,"access denied", "no user account found!");
    }


}

// create new user and save to database
void login::on_signUpButton_clicked()
{
    // store user input into QString variables

    QString email = ui->signUpEmail->text();
    QString fName = ui->signUpFName->text();
    QString lName = ui->signUpLName->text();
    QString password = ui->signUpPassword->text();

    // new query
    QSqlQuery q1;

    // bool variable to check if user account already exists
    bool userAlreadyFound = false;

    // search through login table in database
    q1.exec("SELECT * FROM login");

    // read each row of table and check if user exits already
    while(q1.next()){
        if(email == q1.value(0).toString()){
            userAlreadyFound = true;
            break;
        }else{
            userAlreadyFound = false;
        }
    }

    // if found - display dialog, if not found - create new user account from users input
    // and set all tasks etc to 0
    if(userAlreadyFound == true){
        QMessageBox::information(this, "user found", "user with this email already exists");
    }else{
        q1.prepare("INSERT INTO login (email, password, firstName, lastName, completedTasks, maxTasks, rating, "
                   "completedEvents, maxCompletedEvents)"
                    "VALUES (:email, :password, :firstName, :lastName, :completedTasks, :maxTasks, :rating,"
                   ":completedEvents, :maxCompletedEvents)");
        q1.bindValue(":email", email);
        q1.bindValue(":password", password);
        q1.bindValue(":firstName", fName);
        q1.bindValue(":lastName", lName);
        q1.bindValue(":completedTasks",0);
        q1.bindValue(":maxTasks",0);
        q1.bindValue(":rating",0);
        q1.bindValue(":completedEvents",0);
        q1.bindValue(":maxCompletedEvents",0);
        q1.exec();
        QMessageBox::information(this, "account created", "sign up succesful. you may now log in");
    }









}

// open new admin pin pop up
void login::on_adminSignUpButton_clicked()
{
        newAdminPinWindow = new class adminpin;
        newAdminPinWindow->show();



}

// create new admin (if pin was verified)
void login::adminSignUp(){

    if(pinCorrect == true){

        adminUser admin1;
        admin1.email = ui->signUpEmail->text();
        admin1.fName = ui->signUpFName->text();
        admin1.lName = ui->signUpLName->text();
        admin1.password = ui->signUpPassword->text();

        // save to database

        QSqlQuery q1;

        q1.prepare("INSERT INTO admin (email, password, firstName, lastName)"
                   "VALUES (:email, :password, :firstName, :lastName)");
        q1.bindValue(":email", admin1.email);
        q1.bindValue(":password", admin1.password);
        q1.bindValue(":firstName", admin1.fName);
        q1.bindValue(":lastName", admin1.lName);
        q1.exec();
        pinCorrect = false;
        qDebug() << "admin saved to database";

    }


}
