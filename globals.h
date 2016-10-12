#ifndef GLOBALS_H
#define GLOBALS_H
#include <QString>
#include <QDateTime>


struct TkabTRAK {
       int CustomerID;
       QString CustomerName;
       QString CabinetID;
       int VendorID;
       int ProductID;
       bool isLogged;
       bool isAdmin;
       bool isUser;
       bool isSupervisor;
       QString UserID;
       bool isPCB;
       bool isSMARTCARD;
       bool UserIsAdmin;
       QString strUserFullname;
       QString strJbLabel;
       QString strUserPIN;
       QString Email;
       bool isDBOnline;
       bool isLocalDBOnline;
       bool isOnlineDBOnline;
       int TrailID;
       QString version;
       int isAllDrawersLocked;
       bool isCabinetLocked;
       QString packetRecieved;
       QString wallpaper;
       int intIssued;
       int intReturned;
       int intLeftUnattendedCounter;
       int PinRequired;
       int LineCount;
       QString LicenseID;
       QString RegistrationCode;
       QString UpdateURL;
       bool isBarcodeReader;
       int DefaultCalibrationAccount;
       int DefaultTransferAccount;
       int DefaultServiceAccount;
       int DefaultTestAccount;
       QString ModelNumber;
       int fw_major_version;
       int fw_minor_version;
       int BlockSize;
       int ToolThatChanged;
       int UseWorkOrder;
       int UserBatch;
       int AllowReturnByOthers;
       QString JobLabel;
       int UseAlertSound;
       bool UserMode;
       QDateTime LastLogged;
       QString LastLoggedUser;

   };


   struct TDrawer {
     QString kabID;
     int CustID;
     QString DrawerID;
     int DrawerNumber;
     int IsOpen;
     //DynamicArray< TTools > Tools;
     int LightStatus;
     bool WithDiagram;
     bool WithRecords;
     //TCustomDiagramBlock ABlock;
     QString ToolNumbers;
     int CountTotal;
     int CountMissing;
     int CountIssuedToOther;
     int CountIsuedToUser;
     int CountToolsAvailable;
     int CountToolsOut;
     int LDR_Bytes [21];
     bool Draw_Valid;
   };


extern TkabTRAK thisCabinet;
extern QString SavePressedKey;
extern bool SummaryFormActive;
extern bool ToolReturnActive;
extern bool MessageBoxActive;
extern int tools_available;
extern int tools_issued_current_user;
extern int tools_issued_other_user;
extern bool close_timer_fired;
extern QString UserID;
extern QString qryOutToolsSQL;
extern QString qryOutCribToolSQL;
extern QString ToolsOutSort;
extern bool UserConfrimedTransactions;
extern QString SQLFileName;
extern int ActiveDrawerNum;
extern bool ActiveDrawerState;
extern bool ActiveOpenState;
extern bool ActiveToolChanged;
extern bool DiagramIsLoaded;
extern int BeforeCalibrationDays;
extern bool AllowDrawerClose;
extern int Calibration;
extern int CalibrationNotification;
extern int CloseDrawerToLogOff;
extern int OpenDrawerToAlarm;
extern int AdminToLogOff;
extern int CloseDrawerCounter;
extern int OpenDrawerCounter;
extern int AdminCounter;
extern bool Online;
extern bool TailNumberActive;
extern bool BarcodeTestActive;
extern bool isBarcodeConnected;
extern bool CloseGuiActive;
extern bool WarningActive;
extern int TailCounter;
extern int TailToLogOff;
extern bool AdminTransactionActive;
extern int kabtrakTransferID;
extern bool Transferring;
extern int CurrentTransactionID;
extern int transfer_drawernum;
extern int transfer_toolnum;
extern bool PostToTransaction;
extern bool DrawersUnlock;
extern QString workorder_no;
extern QString batch_no;
extern int current_drawernum;
extern bool ReloadDiagram;
extern int TrailID;
extern bool isCardReaderConnected;
extern bool UpdateAvailable;
extern bool NoLayout;
extern int totaltools_na;
extern bool DrawerOpenDelayisOn;
extern bool maintenanceactive;
extern QString ldr_bit_toolchange;
extern QString ldr_bit_open;
extern int TestActiveDrawer;
extern bool AdminSettingsActive;
extern bool PostIt;
extern bool IssuedToOther;
extern bool ScannedOut;
extern bool DisconnectionScreenActive;
extern bool vKBVisible;
extern bool ReadToolOnly;
extern bool SelectJobActive;
//extern TRzButton SpeedDial[ 10/*# range 1..10*/ ];
extern bool EmailSent;
extern QString logSQL;
extern bool DrawToolMaintActive;
extern bool CabinetSetupActive;
extern bool TerminalActive;
extern bool ToolDrawActive;
extern bool mainActive;
extern bool ToolPropertyActive;
extern unsigned char CurrentAttempt;
extern bool DisplayToolNumberActive;



const int Open = 1;
const int Close = 0;
const int TOOL_IN = 1;
const int TOOL_OUT = 0;
const int RETURN = 1;
const int ISSUEANCE = 0;
const int ADMIN_SETTINGS = 100;
const int ADMIN_USERMODE = 101;
const int NOT_RESPONDING = 255;
   //const char BLOCK_NORMAL[] = "00";
   //const char BLOCK_FLIPPED[] = "10";
   //const char BLOCK_REVERSED[] = "01";
  //const char BLOCK_BOTH[] = "11";
   const int ADMIN = 1;
   const int USER = 0;
   const int NO_TRANSACTION = - 1;
   const int RETURN_BY_CURRENT_USER = 1;
   const int RETURN_BY_OTHER_USER = 2;
   const int NOT_EXIST = - 1;
   const int CALIBRATION_IS_REQUIRED = 1;
   const int SERVICABLE = 1;
   const int NON_SERVICEABLE = 0;
   const int IS_KIT = 1;
   const int BUTTON_PRESSED = 1;
   const int BUTTON_RELEASED = 0;
   const int DRAWERS_LOCKED = 1;
   const int DRAWERS_UNLOCKED = 0;
   const int Missing = 1;
   const int NOT_MISSING = 0;
   const int serviceable = 1;
   const int UNSERVICEABLE = 0;
   const int TRANSFERRED = 1;
   const int NOT_TRANSFERRED = 0;

     // Interface Section Standard colors

   const int BACKGROUD_COLOR = 0x00252525;
   const int COLOR_BLUE = 0x00EFAE00;
   const int COLOR_GRAY = 0x00ACACAC;
   const int COLOR_GREEN = 0x00f600;
   const int COLOR_RED = 0xee2e24;
   const int SYSTEM_MAX_DRAW_COUNT = 10;
   const int LDR_STATUS_BYTE = 3;
     // define the byte masks when dealing with the LDR Status byte

//   const int LDR_STATUS_DRAW_OPEN = 0x01;
//   const int LDR_STATUS_DRAW_LIGHT = 0x10;
//   const int LDR_STATUS_DRAW_HAS_SLAVE = 0x20;
//   const int LDR_STATUS_DRAW_SLAVE_COMMS = 0x40;

   // Device Constanst

 const int VENDOR_ID = 0x04D8;  // PCB Vendor ID
 const int PRODUCT_ID = 0x003F; // Product
 const int SMARTCARD_VENDOR_ID = 0x6352;  // PCB Vendor ID
 const int SMARTCARD_PRODUCT_ID = 0x213A; // Product
 const int LOCK_DRAWERS = 0x01;   // Lock Drawers
 const int UNLOCK_DRAWERS = 0x02; // Unlock Drawers
 const int GET_DRAWER_LOCK_STATE = 0x03;
 const int GET_DRAWER_OPEN_STATE = 0x07;
 const int GET_DRAWER_TOOL_STATE = 0x04; // $04,DrawerNumber,$FF
 const int GET_DRAWER_TOOL_STATUS = 0x10;   // Device Report 10
 const int FIRMWARE_VERSION = 0x11;
 const int LOGO_ON = 0x12;
 const int LOGO_OFF = 0x13;
 const int SET_DRAWER_LIGHT = 0x14; // $14, DrawerNumber, Light Status (00 or 01)
 const int BUTTON_ONE = 0x15; // Device report on Button 1  $15 State State = 01 OFF to ON, 00 ON to OFF
 const int BUTTON_TWO = 0x16; // Device report on Button 2  $16 State State = 01 OFF to ON, 00 ON to OFF
 const int CHECK_BUTTONS = 0x17; // Device command
 const int DEVICE_ERROR = 0xAA; // Device Report

#endif

