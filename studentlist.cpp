#include "studentlist.h"
#include "qsqlquery.h"
#include "ui_studentlist.h"
#include "adminpage.h"


studentlist::studentlist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::studentlist)
{
    ui->setupUi(this);

    // set transparent backround for lists
    ui->fNameList->viewport()->setAutoFillBackground( false );
    ui->lNameList->viewport()->setAutoFillBackground( false );
    ui->ratingList->viewport()->setAutoFillBackground( false );

    // set student list
    setStudentList();

}

studentlist::~studentlist()
{
    delete ui;
}
// display students name and rating in lists
void studentlist::setStudentList(){

    QSqlQuery q1;
    q1.exec("SELECT * FROM login");
    while(q1.next()){

        ui->fNameList->addItem(q1.value(2).toString());
        ui->lNameList->addItem(q1.value(3).toString());
        ui->ratingList->addItem(q1.value(6).toString()+"/5");
    }
}


// return to adminpage
void studentlist::on_returnButton_clicked()
{
   adminpage *newAdminPageWindow = new class adminpage;
   newAdminPageWindow->show();
   close();

}

