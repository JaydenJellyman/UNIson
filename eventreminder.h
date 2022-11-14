#ifndef EVENTREMINDER_H
#define EVENTREMINDER_H

#include "qmediaplayer.h"
#include <QWidget>

namespace Ui {
class eventreminder;
}

class eventreminder : public QWidget
{
    Q_OBJECT

public:
    explicit eventreminder(QWidget *parent = nullptr);
    ~eventreminder();

private slots:
    void on_closeButton_clicked();

private:
    Ui::eventreminder *ui;
    void setEvents();
    QMediaPlayer *ding;
};

#endif // EVENTREMINDER_H
