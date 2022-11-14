#ifndef NOTES_H
#define NOTES_H

#include <QMainWindow>

namespace Ui {
class notes;
}

class notes : public QMainWindow
{
    Q_OBJECT

public:
    explicit notes(QWidget *parent = nullptr);
    ~notes();

private slots:

    void on_actionMy_Account_triggered();

    void on_actionCompleted_Tasks_triggered();

    void on_actionHome_triggered();

    void setNotes();

    void on_saveNoteButton_clicked();

    void on_viewNoteButton_clicked();

    void on_deleteNoteButton_clicked();

private:
    Ui::notes *ui;
    void closeEvent(QCloseEvent *event);
};

struct note{
    QString title, subject, body;
};
inline QVector<note> savedNotes;

#endif // NOTES_H
