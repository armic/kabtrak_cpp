#ifndef ToolDrawH
#define ToolDrawH


const int UPDATE_MSG_STATUS_LOC = 3;
const int LDR_STATUS_LOC = 0;

  // define the byte masks when dealing with the LDR Status byte

const int LDR_STATUS_DRAW_OPEN = 0x01;
const int LDR_STATUS_DRAW_LIGHT = 0x10;
const int LDR_STATUS_DRAW_HAS_SLAVE = 0x20;
const int LDR_STATUS_DRAW_SLAVE_COMMS = 0x40;
const int LDR_STATUS_DRAW_SLAVE_LIGHT = 0x80;
const int TD_STATUS_ACTIVE = 0x01;
const int TD_STATUS_INITALISED = 0x02;


class TToolDraw
    // class definition
{
private:
  int LDR_Bytes [ 21];
  int DrawNumber;
  int DrawObjectStatus;
  int DrawInitCount;

public:
  // Called when creating an instance (object) from this class
  TToolDraw( );

    // Connects to the Draw (via the backplane's main processor) and queries the status of the draw and the LDR bits.
  void InitaliseToolDraw( int mDrawNumber );

  void  SetToolDrawActive( bool mIsActive );
  void  HandleInitialDrawUpdateMsg( char* Buffer );
  void  HandleReqDrawUpdateMsg( char* Buffer );
  void  HandleIntDrawUpdateMsg( char* Buffer );
  bool  IsOpen( );
};


#endif //  ToolDrawH
