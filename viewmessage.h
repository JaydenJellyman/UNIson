#ifndef VIEWMESSAGE_H
#define VIEWMESSAGE_H

#include <QWidget>

namespace Ui {
class viewmessage;
}

class viewmessage : public QWidget
{
    Q_OBJECT

public:
    explicit viewmessage(QWidget *parent = nullptr);
    ~viewmessage();

private slots:


    void on_replyButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::viewmessage *ui;
    void setMessage();

};
inline QString senderName;
inline QString senderEmail;

#endif // VIEWMESSAGE_H
