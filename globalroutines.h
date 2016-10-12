#ifndef GLOBALROUTINES_H
#define GLOBALROUTINES_H
#include "globals.h"
#include <QDir>
#include <QLibrary>
#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QtMultimedia/QSound>


class GlobalRoutines
{
private:	

public:
   GlobalRoutines()
   {}
   ~GlobalRoutines()
   {}

   // Function to get sound directory path
   QString GetSoundPath()
   {
      QString SoundPath;
      SoundPath = QDir::currentPath() + "/sounds" ;
      qDebug() << SoundPath;
      return SoundPath;
   }


   // Function to get log directory path
   QString GetLogPath()
   {
      QString LogPath;
      LogPath = QDir::currentPath() + "/log" ;
      return LogPath;
   }

   // Play Alert sound
   void AlertSoundNotifaction()
   {
       QString alert_sound;
       alert_sound = GetSoundPath() + "/alert.wav";
       qDebug() << alert_sound;
       QSound::play("/sounds/alert.wav");

   }

   void IssuedSoundNotification()
   {
       QString issued_sound;
       issued_sound = GetSoundPath() + "/issue.wav";
       QSound::play(issued_sound);
   }


   void ReturnSoundNotification()
   {
       QString return_sound;
       return_sound = GetSoundPath() + "/return.wav";
       QSound::play(return_sound);
   }



   // Function to write log
   void WriteLog(QString Message )
   {

     QString dCurrentDate;
     QString tCurrentTime;
     QString LogFile;
     LogFile = GetLogPath() + "/kabTRAK.log";
     dCurrentDate = QDate::currentDate().toString();
     tCurrentTime = QTime::currentTime().toString();
     QFile file(LogFile);

     if(QFile::exists(LogFile)){
         if ( file.open(QIODevice::ReadWrite | QIODevice::Append) )
          {
            QTextStream stream( &file );
            stream << "[ " + dCurrentDate + " " + tCurrentTime + " ] " + Message + "\r\n" << endl;
          }
     }
     else
     {
        if ( file.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &file );
            stream << "[ " + dCurrentDate + " " + tCurrentTime + " ] " + "kabTRAK Log File" + "\r\n"<< endl;
        }

     }

   }



};

#endif // GLOBALROUTINES_H
