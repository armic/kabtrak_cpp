#ifndef HIDCONTROL_H
#define HIDCONTROL_H
#define REPORT_LENGTH   65
#include "hidapi.h"
#include <QDir>
#include <QLibrary>
#include <QThread>
#include <QDebug>



typedef struct hid_device_info* (*HID_ENUMERATE)(unsigned short, unsigned short);
typedef void (*HID_FREE_ENUMARATION)(struct hid_device_info*);
typedef hid_device* (*HID_OPEN)(unsigned short, unsigned short, wchar_t*);
typedef int (*HID_GET_MANUFACTURER_STRING)(hid_device *, wchar_t *, size_t);
typedef int (*HID_GET_PRODUCT_STRING)(hid_device*, wchar_t*, size_t);
typedef int (*HID_GET_SERIAL_NUMBER_STRING)(hid_device*, wchar_t*, size_t);
typedef int (*HID_SET_NONBLOCKING)(hid_device*, int);
typedef int (*HID_SEND_FEATURE_REPORT)(hid_device*, const unsigned char*, size_t);
typedef int (*HID_GET_FEATURE_REPORT)(hid_device*, unsigned char*, size_t);


class hidControl
{
private:
    HID_OPEN hid_open;
    HID_SET_NONBLOCKING hid_set_nonblocking;
    HID_SEND_FEATURE_REPORT hid_send_feature_report;
    HID_GET_FEATURE_REPORT hid_get_feature_report;
public:
    hidControl()
    {}

    ~hidControl()
    {}

    unsigned char buf[REPORT_LENGTH];
    bool deviceFound;
    hid_device *handle;

    int init(unsigned int VID, unsigned int PID)
    {

       QDir curdir;
       QLibrary lib(curdir.absolutePath() + "/hidapi");

       lib.load();

        if (!lib.isLoaded())
            return -1;

        hid_open = (HID_OPEN)lib.resolve("hid_open");
        hid_set_nonblocking = (HID_SET_NONBLOCKING)lib.resolve("hid_set_nonblocking");
        hid_send_feature_report = (HID_SEND_FEATURE_REPORT)lib.resolve("hid_send_feature_report");
        hid_get_feature_report = (HID_GET_FEATURE_REPORT)lib.resolve("hid_get_feature_report");

        deviceFound = false;

        handle = hid_open(VID, PID, NULL);

        if (handle)
        {
            qDebug() << "HID Device found.";
            deviceFound = true;
            hid_set_nonblocking(handle, 1);
        }
        else
            return -1;

        return 0;
    }

    // Read hid report

    int RequestState()
    {
        buf[0] = 0x1;
        buf[1] = 0x81;

      hid_write(handle, buf, REPORT_LENGTH);
     // QThread::sleep(1000);
       return hid_read(handle, buf, REPORT_LENGTH);
    }

    // Command - Get Firmaware version
    int ReadFirmwareVersion()
    {
       buf[0] = 0x00;
       buf[1] = 0x11;

       return hid_write(handle,buf,REPORT_LENGTH);
    }

    // Command - Turn logo light ON
    int LogoLightOn()
    {
       buf[0] = 0x00;
       buf[1] = 0x12;

       return hid_write(handle,buf,REPORT_LENGTH);
    }

    //Command - Turn logo light OFF

    int LogoLightOff()
    {
       buf[0] = 0x00;
       buf[1] = 0x13;

       return hid_write(handle,buf,REPORT_LENGTH);
    }
    // Command - Read drawer lock state
    int ReadDrawLockState()
    {
       buf[0] = 0x00;
       buf[1] = 0x03;

       return hid_write(handle,buf,REPORT_LENGTH);
    }



    // Comand to lock all Drawers
    int LockAllDrawers()
    {
       buf[0] = 0x00;
       buf[1] = 0x01;

       return hid_write(handle,buf,REPORT_LENGTH);
    }

    // Command - unlock all drawers
    int UnlockAllDrawers()
    {
       buf[0] = 0x00;
       buf[1] = 0x02;

       return hid_write(handle,buf,REPORT_LENGTH);
    }
    // Command - Set drawer light ON
    int SetLightOn(int DrawNum)
    {
       buf[0] = 0x00;
       buf[1] = 0x14;
       buf[2] = DrawNum;
       buf[3] = 0x01;

       return hid_write(handle,buf,REPORT_LENGTH);
    }

    // Command - Set Drawer Light OFF
    int SetLightOff(int DrawNum)
    {
       buf[0] = 0x00;
       buf[1] = 0x14;
       buf[2] = DrawNum;
       buf[3] = 0x00;

       return hid_write(handle,buf,REPORT_LENGTH);
    }

    // Command - Read Tool Draw status
    int ReadToolDrawStatus(int DrawNum)
    {
       buf[0] = 0x00;
       buf[1] = 0x04;
       buf[2] = DrawNum;
       buf[3] = 0xFF;

       return hid_write(handle,buf,REPORT_LENGTH);
    }

    // Command - Read Drawer open state

    int ReadDrawerOpenState()
    {
       buf[0] = 0x00;
       buf[1] = 0x07;

       return hid_write(handle,buf,REPORT_LENGTH);
    }

};

#endif // HIDCONTROL_H
