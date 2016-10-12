#include "tooldraw.h"
#include <QThread>


TToolDraw::TToolDraw( ):DrawNumber(0),DrawObjectStatus(0), DrawInitCount(0)
{
  LDR_Bytes[0] = 0;
}


bool TToolDraw::IsOpen( )
{
  bool result = false;
  if ( ( ( LDR_STATUS_DRAW_OPEN & LDR_STATUS_DRAW_OPEN ) ) == LDR_STATUS_DRAW_OPEN )
    result = true;
  else
    result = false;
  return result;
}


void TToolDraw::InitaliseToolDraw( int mDrawNumber )
{
  int TimeOut = 0;
  if ( ( ( DrawObjectStatus & TD_STATUS_INITALISED ) ) != 0 )
  {
    // This means we're already initalised, so just re-request the details from the main processor
    // so we know everything is up-to-date.
   // ReadDrawerToolState( DrawNumber, DM.nrhdkabTRAK );
    QThread::sleep(20);; // Delay for 20ms so we don't flood the USB
    return;
  }

  DrawNumber = mDrawNumber;
  TimeOut = 200; // Use a time out of 2 seconds.
  DrawInitCount = 15;

  // Turn the Light on for the given draw so we can scan which tools are in.
 // SetLightOn( DrawNumber, DM.nrhdkabTRAK );

  // On the off chance the draw already has its light on, request a tool state aswell, since we'll just ignore any extra messages.
  QThread::sleep(10);
 // ReadDrawerToolState( DrawNumber, DM.nrhdkabTRAK );

  // Now wait for a period for the draw to respond.
  while ( ( TimeOut > 0 ) && ( ( ( DrawObjectStatus & TD_STATUS_INITALISED ) ) != TD_STATUS_INITALISED ) )
  {
    // Wait 10ms, decrement our timeout, then try again.
    QThread::sleep(10);
    TimeOut--;
  }

  // At this point we're either initalised, or we've timed out.
  if ( ( ( DrawObjectStatus & TD_STATUS_INITALISED ) ) != TD_STATUS_INITALISED )
  {
   // SetLightOff( DrawNumber, DM.nrhdkabTRAK );
   // WriteLog( "[ Error ] Draw timed out: " + IntToStr( DrawNumber ) );
    SetToolDrawActive( false );
    return;
  }
 // WriteLog( "Success: Draw found: " + IntToStr( DrawNumber ) + " Delay: " + IntToStr( TimeOut ) );
  // We have the data needed for initalising the draw, so turn off the tool lights again.
 // SetLightOff( DrawNumber, DM.nrhdkabTRAK );
}


void TToolDraw::SetToolDrawActive( bool mIsActive )
{
  if ( mIsActive )
  {
    DrawObjectStatus = DrawObjectStatus | TD_STATUS_ACTIVE;
  }
  else
    DrawObjectStatus = DrawObjectStatus & ~ TD_STATUS_ACTIVE;
}


void TToolDraw::HandleInitialDrawUpdateMsg( char* Buffer )
{
  int k = 0, ArrayOffset = 0, BitOffset = 0;

  // Always update our status
  LDR_Bytes[LDR_STATUS_LOC] = ((int) (( char ) ( Buffer )[UPDATE_MSG_STATUS_LOC] ));

  // If the light isn't on yet or we have a slave draw and the period for waiting for the draw to light up hasn't passed,
  // request another update from the draw.
  if ( ( ( LDR_Bytes[LDR_STATUS_LOC] & LDR_STATUS_DRAW_LIGHT ) ) == 0 )
  {
    if ( DrawInitCount > 0 )
    {
     DrawInitCount--;
     QThread::sleep(50);
    //  SetLightOn( DrawNumber, DM.nrhdkabTRAK );
    }
  //  WriteLog( "Light not active yet, ignoring packet. " );
    return;
  }
  if ( ( ( ( LDR_Bytes[LDR_STATUS_LOC] & LDR_STATUS_DRAW_HAS_SLAVE ) ) != 0 ) && ( ( ( LDR_Bytes[LDR_STATUS_LOC] & LDR_STATUS_DRAW_SLAVE_LIGHT ) ) == 0 ) )
  {
    if ( DrawInitCount > 0 )
    {
      DrawInitCount--;
    //  WriteLog( "Slave Draw Light not on, re-requesting Draws details." );
    QThread::sleep(10);
   //   ReadDrawerToolState( DrawNumber, DM.nrhdkabTRAK );
    }
    return;
  }
  // Now if the Light is on, update the LDR bytes and do any missing tool checks.
  for ( int stop = 23, k = 4; k <= stop; k++)
  {
    LDR_Bytes[k - 3] = ((int) (( char ) ( Buffer )[k] ));
  }

  // Regular Diagram Tools
  /*# with DM.qryLoadDrawerTools do */
  {
    //Connection = DM.conHenchman;
   // Close;
   // ParamByName( "CustID" ).Value = thisCabinet.CustomerID;
   // ParamByName( "kabID" ).Value = thisCabinet.CabinetID;
  //  ParamByName( "DrawerNum" ).Value = DrawNumber;
  //  try
  //  {
//     Open;
//      if ( ! isEmpty )
//      {
//        WriteLog( "Syncing tool state ..." );
//        First;
//        while ( ! EOF )
//        {
//          k = FieldByName( "ToolNumber" ).asInteger;
//          if ( k <= 160 )
//          {
//            // need to turn this into a bit patern to compare against the LDR Bits.
//            ArrayOffset = ( ( k - 1 ) / 8 ) + 1;
//            // This is a little weird, since when k is divisable by 8 we want the bitoffset to be 0.
//            BitOffset = ( 7 - ( ( k - 1 ) % 8 ) );
//            if ( ( ( LDR_Bytes[ArrayOffset] & ( 1 << BitOffset ) ) ) != 0 )
//              PostToolStatus( DrawNumber, k, 1, FieldByName( "status" ).asInteger );
//            else
//              PostToolStatus( DrawNumber, k, 0, FieldByName( "status" ).asInteger );
//          }
//          else
//          {
//            WriteLog( "Drawer no. " + IntToStr( DrawNumber ) + " Tool Index " + IntToStr( k ) + " > 160 and is Out of Bounds" );
//          }
//          Next;
//        }
//      }
//    }
//    catch( EMyError & E )
//    {
//    {
//      WriteLog( "[ SQL ERROR ] Exception class name = " + E.ClassName );
//      WriteLog( "[ SQL ERROR ] Exception message = " + E.Message );
//      return;
//    }
//    }
  }
  // Denote the fact we've initalised.
  DrawObjectStatus = ( DrawObjectStatus | TD_STATUS_INITALISED );

  // IF the draw isn't open, turn the light off.
  if ( ( ( LDR_Bytes[LDR_STATUS_LOC] & LDR_STATUS_DRAW_OPEN ) ) == 0 )
  {
   // SetLightOff( DrawNumber, DM.nrhdkabTRAK );
  }
}


void TToolDraw::HandleReqDrawUpdateMsg( char* Buffer )
{
  HandleIntDrawUpdateMsg( Buffer );
}


void TToolDraw::HandleIntDrawUpdateMsg( char* Buffer )
{
  unsigned char tmp_Byte = '\0', j = '\0', I = '\0', ToolNumber = '\0';
  // If we've not initalised yet, handle the interrupt message as if we requested it.
  if ( ( ( DrawObjectStatus & TD_STATUS_INITALISED ) ) != TD_STATUS_INITALISED )
  {
    HandleInitialDrawUpdateMsg( Buffer );
    return;
  }

  // Handle the turning on and off the tool sensor lights.
  // First, detect if a draw has been opened or closed.
  tmp_Byte = ( LDR_Bytes[LDR_STATUS_LOC] ^ ((int) (( char ) ( Buffer )[UPDATE_MSG_STATUS_LOC] ) ));
  if ( ( ( tmp_Byte & LDR_STATUS_DRAW_OPEN ) ) != 0 )
  { // The draw open status has changed.
    if ( ( ( ((int) ((char ) ( Buffer )[UPDATE_MSG_STATUS_LOC] ) & LDR_STATUS_DRAW_OPEN ) ) != 0 ))
    { // The draw has been opened.
      // Turn the Tool sensor lights on, since we're interested in this draw.
      //SetLightOn( DrawNumber, DM.nrhdkabTRAK );
     // if ( DrawToolMaintActive )
       // formMain.swToggleLight.StateOn = true;
    //  formMain.ToolDraw_OpenedOrClosed( );
    //  WriteLog( "Drawer " + IntToStr( DrawNumber ) + " was opened" );
    }
    else
    { // the draw has been closed.
      // The draw has been closed, so we don't need to monitor the tools.
     // SetLightOff( DrawNumber, DM.nrhdkabTRAK );
    //  if ( DrawToolMaintActive )
    ////    formMain.swToggleLight.StateOn = false;
   //   formMain.ToolDraw_OpenedOrClosed( );
   //   WriteLog( "Drawer " + IntToStr( DrawNumber ) + " was closed" );
    }
  }
  if ( tmp_Byte != 0 )
  {
    // update the stored status byte since we've detected the draw change..
    LDR_Bytes[0] = ((int) (( char ) ( Buffer )[UPDATE_MSG_STATUS_LOC] ));
  }

  // Now, is this draw one of the active ones? and also, is the light on, since we don't monitor draws which don't have their lights on.
  if ( ( ( LDR_Bytes[0] & LDR_STATUS_DRAW_LIGHT ) ) == 0 )
  {
 //   if ( DrawToolMaintActive )
 //    formMain.swToggleLight.StateOn = false;
 //   WriteLog( "Ignoring LDR from unlit draw." + IntToStr( DrawNumber ) );
    return;
  }

  // At this point we need to work out which tools have changed.
  // Figure out which bits have been modified..
  for ( int stop = 20, j = 1; j <= stop; j++) // Get LDR Status
  {
    if ( LDR_Bytes[j] != ((int) ( (( char ) ( Buffer )[j + 3] ) ) ))
    {
      tmp_Byte = ( LDR_Bytes[j] ^ ((int) ( ((char ) ( Buffer )[j + 3] ) ) ));
      for ( int stop = 0, I = 7; I >= stop; I--)
      {
        if ( ( ( tmp_Byte & ( 1 << I ) ) ) != 0 )
        {
          // We've found the changed bit.
          ToolNumber = ( ( j - 1 ) * 8 + ( 8 - I ) );

          // Is the tool part of the Slave Mux?
          if ( ( ToolNumber >= 77 ) && ( ( ( LDR_Bytes[LDR_STATUS_LOC] & LDR_STATUS_DRAW_HAS_SLAVE ) ) != 0 ) && ( ( ( LDR_Bytes[LDR_STATUS_LOC] & LDR_STATUS_DRAW_SLAVE_LIGHT ) ) == 0 ) )
          {
          // WriteLog( "Ignoring Slave LDR from draw due to Slave Mux light not being on." + IntToStr( DrawNumber ) );
            // We are exiting this loop before the stored values are changed, so we should ensure a partial update occurs.
            // This means only update the top 4bits, but keep the last 4 unchanged.
            LDR_Bytes[j] = ( LDR_Bytes[j] & 0x0f ) | ( ((int) ( (( char ) ( Buffer )[j + 3] ) )) & 0xf0 );
            return;
          }
        //  WriteLog( "Tool Change ID : " + IntToStr( ToolNumber ) );

          // Log the Tool Change.
          // Was the tool put back or removed?
          if ( ( ( ((int) ( (( char ) ( Buffer )[j + 3] ) ) & ( 1 << I ) ) )) != 0 )
          {
            //if ( ! DrawToolMaintActive )
            //  DM.AttemptToolReturn( DrawNumber, ToolNumber );
           // else
            //  DM.AttemptToolReturnMaint( DrawNumber, ToolNumber );
          }
          else
          {
          //  if ( ! DrawToolMaintActive )
          //    DM.AttemptToolIssue( DrawNumber, ToolNumber );
         //   else
          //    DM.AttempTToolIssueMaint( DrawNumber, ToolNumber );
          }
        }
      }
      // Update our stored values to reflex the change.
      LDR_Bytes[j] = ((int) ( (( char ) ( Buffer )[j + 3] )) );
    }
  }
  }//
