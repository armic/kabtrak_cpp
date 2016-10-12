#include "kabtrak.h"
#include "ui_kabtrak.h"
#include <QMessageBox>
#include <QDebug>


Kabtrak::Kabtrak(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Kabtrak)
{
    ui->setupUi(this);
   // this->setStyleSheet("background-color: " + BACKGROUD_COLOR );
    timerId = startTimer(1000);
}

Kabtrak::~Kabtrak()
{
    killTimer(timerId);
    delete ui;
}


void  Kabtrak::timerEvent(QTimerEvent *event)
{
    int res;
    res = hid->RequestState();
    if (res == 0 ) qDebug() << "waiting" << hid->buf;
    if (res < 0) qDebug() << "Cant read";
    qDebug() << "Result" << hid->buf[1] << " " << hid->buf[2] ;

}

void Kabtrak::on_pushButton_clicked()
{
 close();
//
// QMessageBox msgBox;
// msgBox.setText(QString::number(iStatus));
// msgBox.exec();
}
