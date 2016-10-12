#ifndef KABTRAK_H
#define KABTRAK_H
#include <QMainWindow>
#include "hidControl.h"

namespace Ui {
class Kabtrak;
}

class Kabtrak : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kabtrak(QWidget *parent = 0);
    ~Kabtrak();
    hidControl *hid;



private slots:
    void on_pushButton_clicked();

private:
    Ui::Kabtrak *ui;
    int timerId;


protected:
   void timerEvent(QTimerEvent *event);


};

#endif // KABTRAK_H
