#ifndef CALENDERVIEW_H
#define CALENDERVIEW_H

#include <QWidget>

namespace Ui {
class calenderView;
}

class calenderView : public QWidget
{
    Q_OBJECT

public:
    explicit calenderView(QWidget *parent = nullptr);
    ~calenderView();

private:
    Ui::calenderView *ui;
};

#endif // CALENDERVIEW_H
