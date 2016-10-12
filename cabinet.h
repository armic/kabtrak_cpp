#ifndef CabinetH
#define CabinetH
#include "globals.h"
#include "hidControl.h"
#include "ToolDraw.h"
#include <QThread>

#define MAX_DRAW_COUNT  10

 // Define the messages coming from the Cabinet Hardware which we need to handle.

const int USB_MSG_REQUESTED_DRAW_UPDATE = 0x4;
const int USB_MSG_ALL_DRAWS_OPEN_STATUS = 0x7;
const int USB_MSG_INTERRUPT_DRAW_UPDATE = 0x10;
const int USB_MSG_FIRMWARE_VERSION = 0x11;
const int USB_MSG_I2C_ERROR_MESSAGE = 0xAA;


class Cabinet {
  private:
    TToolDraw MyToolDraws [ MAX_DRAW_COUNT ];
    int ActiveDrawNumber;
    int fw_major_version;
    int fw_minor_version;
  public:
    // Called when creating an instance (object) from this class
  TCabinet( )
  {
     ActiveDrawNumber = 0;
     fw_major_version = 0;
     fw_minor_version = 0;
  }

  ~TCabinet()
  {}

      hidControl *hid;


    // Talks to the Physical Cabinet to find out what is actually attached.
  void  InitaliseCabinet( )
  {
    int I = 0;

    hid->ReadFirmwareVersion();
    QThread::sleep(50);
  //  for ( int stop = MAX_DRAW_COUNT, I = 1; I <= stop; I++)
 //   {
  //    if ( isDrawerExistRecord( I ) )
  //    {
  //     // frmSplash.SplashScrn_AddLine( "Initalising Draw " + IntToStr( I ) );
  //      MyToolDraws[I - 1].InitaliseToolDraw( I );
  //    }
  //    else
  //    {
  //      MyToolDraws[I - 1].SetToolDrawActive( false );
  //    }
    //}
  }


  void HandleUSBMsg( char* Buffer )
  {
    int ToolDrawNum = 0, MsgID = 0;

    // Work out what kind of message we're dealing with.

    MsgID = ((int) (( char ) ( Buffer )[1] ));

    // We know what size ALL USB packets are (64bytes) so we can safely read the second byte of the message
    // even before we know if we needed.

    ToolDrawNum = ( char ) ( Buffer )[2] ;
    switch ( MsgID )
    {
      case USB_MSG_REQUESTED_DRAW_UPDATE:
      {
          // ensure we're getting information on a valid draw ID.
        if ( ( ToolDrawNum < 1 ) || ( ToolDrawNum > MAX_DRAW_COUNT ) )
        {
          //WriteLog( "[ Error ] Invalid Draw ID " + IntToStr( ToolDrawNum ) );
          return;
        }
        MyToolDraws[ToolDrawNum - 1].HandleReqDrawUpdateMsg( Buffer );
      }
      break;
      // ############################################################################################

      case USB_MSG_ALL_DRAWS_OPEN_STATUS:
      {
        for ( int stop = MAX_DRAW_COUNT, ToolDrawNum = 1; ToolDrawNum <= stop; ToolDrawNum++)
        {
          if ( ((int) ( (( char ) ( Buffer )[ToolDrawNum + 1] ) ) == 1 ))
            MyToolDraws[ToolDrawNum - 1].SetToolDrawActive( true );
          else
            MyToolDraws[ToolDrawNum - 1].SetToolDrawActive( false );
        }
      }
      break;
      // ############################################################################################

      case USB_MSG_INTERRUPT_DRAW_UPDATE:
      {
          // ensure we're getting information on a valid draw ID.
        if ( ( ToolDrawNum < 1 ) || ( ToolDrawNum > MAX_DRAW_COUNT ) )
        {
          //WriteLog( "[ Error ] Invalid Draw ID " + IntToStr( ToolDrawNum ) );
          return;
        }
        MyToolDraws[ToolDrawNum - 1].HandleIntDrawUpdateMsg( Buffer );
      }
      break;
      // ############################################################################################

      case USB_MSG_FIRMWARE_VERSION:
      {
        fw_major_version = ((int) (( char ) ( Buffer )[2] ));
        fw_minor_version = ((int) (( char ) ( Buffer )[3] ));
       // frmSplash.SplashScrn_AddLine( "Cabinet Firmware Version " + IntToStr( fw_major_version ) + "." + IntToStr( fw_minor_version ) + " detected" );
       // WriteLog( "Cabinet Firmware " + IntToStr( fw_major_version ) + "." + IntToStr( fw_minor_version ) + " detected." );
      //  DM.LogCabinetFirmware( fw_major_version, fw_minor_version );
      }
      break;
      // ############################################################################################

      case USB_MSG_I2C_ERROR_MESSAGE:
      {
        switch ( ((int) ( char ) ( Buffer )[2] ) )
        {
          case 0xFF:
          {
           // WriteLog( "[ Error ] i2C Bus collision error detected...." );
          }
          break;
          case 0xFE:
          {
           // WriteLog( "[ Error ] i2C Not Ack error detected...." );
          }
          break;
          case 0xFD:
          {
           // WriteLog( "[ Error ] i2C write collision error detected...." );
          }
          break;
          case 0xFC:
          {
           // WriteLog( "[ Error ] undefined error detected...." );
          }
          break;
          case 0xFB:
          {
           // WriteLog( "[ Error ] Checksum error detected...." );
          }
          break;
        default:
        {
         // WriteLog( "[ Error ] Unknown Error: " + IntToStr( ((unsigned char) (( PAnsiChar ) ( Buffer ))[2] ) ) );
        }
        }
      }
      break;
    }
  }


  int GetActiveToolDraw( )
  {
    int result = 0;
    int ToolDrawNum = 0;
    // Search through our list of draws and find the first one which is open.
    for ( int stop = MAX_DRAW_COUNT, ToolDrawNum = 1; ToolDrawNum <= stop; ToolDrawNum++)
    {
      if ( MyToolDraws[ToolDrawNum - 1].IsOpen( ) )
      {
        result = ToolDrawNum;
        return result;
      }
    }
    result = 0;
    return result;
  }


  bool IsToolDrawOpen( int DrawNumber )
  {
    bool result = false;
    if ( ( DrawNumber < 1 ) || ( DrawNumber > MAX_DRAW_COUNT ) )
      result = false;
    else
    {
      if ( MyToolDraws[DrawNumber - 1].IsOpen( ) )
        result = true;
      else
        result = false;
    }
    return result;
  }


 };


#endif //  CabinetH

