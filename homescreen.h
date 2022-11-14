#ifndef HOMESCREEN_H
#define HOMESCREEN_H
#include <QSqlDatabase>




#include "qmediaplayer.h"
#include "ui_homescreen.h"
#include <QMainWindow>

namespace Ui {
class homeScreen;
}

class homeScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit homeScreen(QWidget *parent = nullptr);
    ~homeScreen();
    QSqlDatabase dbTask;



private:

    QPushButton *deleteTaskButton;


private slots:
    void deleteTask();
    void addTasks();
    void viewTask();
    void markCompleteHomeSreen();
    void viewEvent();
    void addEvents();
    void deleteEvents();
    void getTasksEventsNotesFromDatabase();
    void on_actionMy_Account_triggered();

    void on_actionCompleted_Tasks_triggered();

    void on_actionNotes_triggered();

    void on_calendarWidget_clicked(const QDate &date);


public slots:
    void setTasksProgressEvents();

    void setRating();
    void newAccountPage();
private:
    Ui::homeScreen *ui;


    void closeEvent(QCloseEvent *event);
    void checkMessages();
    void on_actionviewMessages_triggered();
    void eventReminder();

};

inline QString calenderDate;
inline QString newCalenderDate;
inline QAction* viewMessage;
inline QMenu* newMessage;
inline QDate date;
inline QString newDate;

#endif // HOMESCREEN_H
