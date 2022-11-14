#ifndef TASKS_H
#define TASKS_H

#include "qdatetime.h"
#include <QVector>

struct task{ // struct to hold tasks
    QString title;
    QString subject;
    QString due;
    QString priority;
    bool complete;
};

inline QVector <task> savedTasks; // vector to store users tasks


inline task currentTask;





#endif // TASKS_H
