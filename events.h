#ifndef EVENTS_H
#define EVENTS_H
#include <QString>
#include <QVector>

struct event { // struct to store new event
    QString title;
    QString subject;
    QString due;
    QString priority;
    QString description;
    bool repeat;
    bool reminder;
    bool complete;
};
inline QVector <event> savedEvents; // vector to store saved events
inline QVector <event> todaysEvents; // vector to store todays events
inline event currentEvent;



#endif // EVENTS_H
