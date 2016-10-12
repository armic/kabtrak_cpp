#include "kabtrak.h"
#include <QApplication>
#include "hidControl.h"
#include "globalroutines.h"
#include "globals.h"
#include <QDebug>

 hidControl *hid;
 GlobalRoutines *gr;

int main(int argc, char *argv[])
{
    // Create new instance of HidControl Class and connect to cabinet
    int res;
    hid = new hidControl();
    gr = new GlobalRoutines;


    // Initialise hid
    if (hid->init(0x4d8, 0x3f) < 0)
        return -2;
     res = hid->ReadFirmwareVersion();
     if (res < 0) qDebug() << "Cant read firmware version";
     if (res ==  0) qDebug() << "Nothing firmware version";

//    res = hid->RequestState();
//    if (res == 0 ) qDebug() << "waiting" << hid->buf;
//    if (res < 0) qDebug() << "Cant read";
//    qDebug() << "Result" << hid->buf[1] << " " << hid->buf[2] ;

    gr->WriteLog("This is a test");

    QApplication a(argc, argv);
    Kabtrak w;



    //QRect rec = QApplication::desktop()->screenGeometry();
   // w.setWindowState(w.windowState() ^ Qt::WindowFullScreen); // Show in full screen
    w.show();
    return a.exec();
}


