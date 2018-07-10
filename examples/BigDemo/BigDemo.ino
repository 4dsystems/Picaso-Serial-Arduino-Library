/*********************************************************************************************/
/*                                                                                           */
/*  4D Serial Sample                                                                         */
/*                                                                                           */
/*  Date:            4 December 2012 (updated 17 October 2014)                               */
/*                                                                                           */
/*  Description:     Demonstrates Pretty much every 4D Serial command.                       */
/*                   This has been tested on an Arduino Duemilanove ATmega328 using Arduino  */
/*                   1.0.2                                                                   */
/*                   This program, by default, uses the hardware serial on pins 0 and 1 and  */
/*                   thus the 5 pin connector on the 4D Arduino Adapter, or the 4Display     */
/*                   Shield must be unplugged before loading your sketch and plugged back in */
/*                   after the error callback is called (i.e. the LED is flashing), then     */
/*                   reset the Arduino using the Reset button (otherwise you will get a      */
/*                   message like "avrdude: stk500_getsync(): not in sync: resp=0xe0")       */
/*                                                                                           */
/*                   The library also supports other hardware serial ports, for the boards   */
/*                   that support them, as well as software serial.                          */
/*                                                                                           */
/*                   Define the serial port to use here, if using software serial set it to  */
/*                   something like SerialS.                                                 */
  #define DisplaySerial Serial
/*                                                                                           */
/*                   To use SoftwareSerial uncomment the following and set the pins you are  */
/*                   using correctly                                                         */
//#include <SoftwareSerial.h>
//SoftwareSerial DisplaySerial(2,3) ; // pin 2 = TX of display, pin3 = RX
/*                                                                                           */
/*                   If you are not using hardware serial on pins 0 and 1 you can use this   */
/*                   hardware port for logging messages. To do this uncomment the following  */
//#define LOG_MESSAGES
/*                                                                                           */
/* Error Callback    In order to drastically reduce the amount of error checking you need    */
/*                   to do a callback exists to perform 'standard' error handling when an    */
/*                   occurs. If you want to do your own handling set Callback4D to NULL      */
/*                   otherwise set it to the address of the error routine                    */
/*                                                                                           */
/* Baud rate change  Because the stream class used within the library does not support       */
/*                   .end, or .begin the setbaudWait and SetThisBaudrate functions are       */
/*                   coded within this demo                                                  */
/*                                                                                           */
/* Sketch Size!      If you are logging messages, then you may exceed the maximum sketch     */
/*                   size for some of the smaller boards, you can comment out TEST_USD to    */
/*                   exclude tests that require a uSD card to run and/or TEST_OTHER to       */
/*                   exclude tests that do not require a uSD card to run.                    */
#define TEST_USD
#define TEST_OTHER
/*                                                                                           */
/*                                                                                           */
/*                   The following files are needed on the uSD to complete all tests. Their  */
/*                   relative location (from C:\Users\Public\Documents\4D Labs) is shown     */
/*                   gfx2demo.gci    resources\GC Files                                      */
/*                   gfx2demo.dat    resources\GC Files                                      */
/*                   KBFunc.4fn      Picaso ViSi                                             */
/*                   KBFunc.gci      Picaso ViSi                                             */
/*                   KBFunc.dat      Picaso ViSi                                             */
/*                   Space.wav       Picaso ViSi Genie\SoundPlayer.ImgData                   */
/*                                                                                           */
/*********************************************************************************************/

#ifdef LOG_MESSAGES
  #define HWLOGGING Serial
#else
  #define HWLOGGING if (1) {} else Serial
#endif

#include "Picaso_Serial_4DLib.h"
#include "BigDemo.h" 
#include "Picaso_Const4D.h"

Picaso_Serial_4DLib Display(&DisplaySerial);

const char *atoz = {"abcdefghijklmnopqrstuvwxyz"} ;

// globals for this sketch
int fFATtests   ;
int fmediatests ;
int fimgtests   ;
int ftouchtests ;
int floadtests  ;
int fsoundtests ;
unsigned long rawbase ;

int trymount(void)
{
#define retries 15
  int i ;
  int j ;
  i = Display.file_Mount() ;
  j = 0 ;
  if (!i)
  {
    Display.putstr("Please insert uSD card\n") ;
    while (   (!i)
           && (j < retries) )
    {
      Display.putstr(".") ;
      i = Display.file_Mount() ;
      j++ ;
    }
    Display.putstr("\n") ;
  }
  if (j == retries)
    return false ;
  else
    return true ;
}

int RAWPartitionbase(unsigned long * rawbaseo)
{
  unsigned char sector[512] ;
  int rawsize ;
  int FAT ;
  int RAW ;
  int result = false ;
  Display.media_SetAdd(0, 0) ;                    // so we test this, could use SetSector instead
  if (!Display.media_RdSector((char *)sector))
    HWLOGGING.println(F("read sector failed")) ;
  else
  {
    *rawbaseo = 0 ;
    RAW       = false ;
    FAT       = false ;
    if (   (sector[511] == 0xaa)
        && (sector[510] == 0x55) )
    {									 // possible partition table
      if (   (   (sector[446] ==   0)
              || (sector[446] == 0x80) )
          && (   (sector[462] ==   0)
              || (sector[462] == 0x80) )
          && (   (sector[478] ==   0)
              || (sector[478] == 0x80) )
          && (   (sector[494] ==   0)
              || (sector[494] == 0x80) ) )
      {
        if (   (sector[450] == 0x04)
            || (sector[450] == 0x06)
            || (sector[450] == 0x0E) )
          FAT = true ;
        if (sector[466] == 0xDA)
        {
          *rawbaseo = (unsigned)sector[470] + (unsigned)(sector[471] << 8) + (unsigned)(sector[472]  << 16) + (unsigned)(sector[473]  << 24) ;
          rawsize   = (unsigned)sector[474] + (unsigned)(sector[475] << 8) + (unsigned)(sector[476]  << 16) + (unsigned)(sector[477]  << 24) ;
          result    = true ;
          RAW       = true ;
        }
      }
      else
      {
        if (sector[0] == 0xEB) // jmp instruction
          FAT = true ;
        else
          RAW = true ; // but no really possible as we couldn't have gotten this far in this sketch
      }
    }
    else
      RAW = true ; // but no really possible as we couldn't have gotten this far in this sketch
  }
return result ;
}

void Function_Tests (void)
{
  int i, j ;
  int k ;
  int l ;
  int m ;
  word handle, h1, h2 ;
  word parms[20];
  char wks1[255] ;
  char wks2[255] ;
  char wks3[255] ;
  Display.gfx_Cls() ;
  Display.putstr("file_Run, file_Exec and\nfile_LoadFunction Tests") ;
  HWLOGGING.println(F("file_Run, file_Exec and file_LoadFunction Tests")) ;
  j = Display.mem_Heap() ;
  handle = Display.file_LoadFunction(functest) ;
  
  h1 = Display.writeString(0,  "Please enter your name") ;   // prompts string
  h2 = Display.writeString(h1, "") ;                         // result string, must be max length if following strings are to be 'kept'
  HWLOGGING.print(F("String Handles")) ;
  HWLOGGING.print(h1) ;
  HWLOGGING.print(F(", ")) ;
  HWLOGGING.println(h2) ;
  parms[0] = h1 ;                  // prompt string
  parms[1] = h2 ;                  // result string
  parms[2] = 20 ;
  parms[3] = 1 ;                   // 1 = save screen, 0 = don't save screen
  Display.TimeLimit4D = 5000000 ;
  
  i = Display.file_CallFunction(handle, 4, parms) ;         // calls a function
  HWLOGGING.print(F("You typed ")) ;
  HWLOGGING.print(i) ;
  HWLOGGING.print(F(" characters ")) ;
  Display.readString(h2, wks1) ;                              // read string immediately as it will be overwritten 'soon'
  //	HWLOGGING.print((unsigned char)&wks1) ;
  HWLOGGING.println(wks1) ;
  k = Display.mem_Heap() ;
  Display.mem_Free(handle) ;
  l = Display.mem_Heap() ;
  delay(5000) ;                                       // give time to read the 'restored' screen
  
  h1 = Display.writeString(0,  "Please type anything") ;     // prompts string
  h2 = Display.writeString(h1, "") ;                         // result string, must be max length if following strings are to be 'kept'
  parms[0] = h1 ;                  // prompt string
  parms[1] = h2 ;                  // result string
  parms[2] = 20 ;
  parms[3] = 0 ;                   // 1 = save screen, 0 = don't save screen
  i = Display.file_Exec(functest, 4, parms) ;
  Display.readString(h2, wks2) ;                              // read string immediately as it will be overwritten 'soon'
  Display.gfx_Cls() ;
  
  h1 = Display.writeString(0,  "Please some more") ;         // prompts string
  h2 = Display.writeString(h1, "") ;                         // result string, must be max length if following strings are to be 'kept'
  parms[0] = h1 ;                  // prompt string
  parms[1] = h2 ;                  // result string
  parms[2] = 20 ;
  parms[3] = 0 ;                   // 1 = save screen, 0 = don't save screen
  i = Display.file_Run(functest, 4, parms) ;
  Display.readString(h2, wks3) ;                              // read string immediately as it will be overwritten 'soon'
  Display.gfx_Cls() ;
  m = Display.mem_Heap() ;
  HWLOGGING.print(F("Memfree before loadfunction = ")) ;
  HWLOGGING.println(j) ;
  HWLOGGING.print(F("Memfree after loadfunction = ")) ;
  HWLOGGING.println(k) ;
  HWLOGGING.print(F("Memfree after free = ")) ;
  HWLOGGING.println(l) ;
  HWLOGGING.print(F("Memfree at end = ")) ;
  HWLOGGING.println(m) ;
  HWLOGGING.println(F("You typed")) ;
  HWLOGGING.println(wks1) ;
  HWLOGGING.println(wks2) ;
  HWLOGGING.println(wks3) ;
  Display.putstr("You typed\n") ;
  Display.putstr(wks1) ;
  Display.putstr("\n") ;
  Display.putstr(wks2) ;
  Display.putstr("\n") ;
  Display.putstr(wks3) ;
  Display.TimeLimit4D = 2000 ;
}

void gfx_Part1(void)
{
  int i ;
  Display.gfx_BGcolour(LIGHTGOLD) ;           // to check CLS works with different bg color
  Display.gfx_Cls() ;
  Display.txt_BGcolour(LIGHTGOLD) ;           // to ensure text goesn look odd
  Display.txt_FGcolour(RED) ;
  Display.putstr("Display.gfx_A to Display.gfx_L") ;
  HWLOGGING.println(F("Display.gfx_A to Display.gfx_L")) ;
  Display.txt_FGcolour(LIME) ;            // reset
  Display.gfx_BevelShadow(1) ;                // make it really dark
  Display.gfx_BevelWidth(6) ;                 // make the button bigger by increasing the bevel size
  for (i = 1; i <= 10; i++)
  {
    Display.gfx_Button(ON, 120,50, YELLOW, PURPLE, FONT3, 1, 1, "Test Button") ;
    delay(100) ;
    Display.gfx_Button(OFF, 120,50, YELLOW, PURPLE, FONT3, 1, 1, "Test Button") ;
    delay(100) ;
  }
  Display.gfx_BevelShadow(3) ; // back to default
  Display.gfx_ChangeColour(LIME, WHITE) ;
  Display.gfx_Circle(30,30,10,BLUE) ;
  Display.gfx_CircleFilled(130,30,10,BLUE) ;
  Display.gfx_Rectangle(60,60,100,100,RED) ;  // draw a rectange to show where we are clipping
  Display.gfx_ClipWindow(60,60,100,100) ;
  Display.gfx_Clipping(ON) ;                  // turn clipping on but just use it for text
  Display.gfx_MoveTo(40,80) ;
  Display.putstr("1234567890asdfghjkl") ;     // this is clipped
  Display.gfx_Clipping(OFF) ;
  delay(1000) ;
  HWLOGGING.println(F("Display off")) ;
  Display.gfx_Contrast(0) ;
  delay(1000) ;
  Display.gfx_Contrast(15) ;
  HWLOGGING.println(F("Display on")) ;
  Display.gfx_Ellipse(100,230, 50,30,RED) ;
  Display.gfx_EllipseFilled(100,300, 50,30,AQUA) ;
  Display.gfx_FrameDelay(6) ;
  HWLOGGING.print(F("X Res= ")) ;
  HWLOGGING.print(Display.gfx_Get(X_MAX)+1) ;
  HWLOGGING.print(F(" Y Res= ")) ;
  HWLOGGING.println(Display.gfx_Get(Y_MAX)+1) ;
  HWLOGGING.print(F("Pixel at 0,30 is ")) ;
  HWLOGGING.println(Display.gfx_GetPixel(0, 30), HEX) ;
  Display.gfx_Line(0,0,100,200,BLUE) ;
  Display.gfx_LinePattern(0x00aa) ;
  Display.gfx_Set(OBJECT_COLOUR, WHITE);
  Display.gfx_LineTo(239,319) ;
  Display.gfx_LinePattern(0) ;            // reser
  Display.gfx_BGcolour(BLACK) ;           // reset
  Display.txt_BGcolour(BLACK) ;           // reset
}

void gfx_Part2(void)
{
  int i ;
  int k ;
  int l ;
  word orbitx ;
  word orbity ;
  word vx[20] ;    // : array[0..19] of word ;
  word vy[20] ; //     : array[0..19] of word ;
  Display.gfx_Cls() ;
  Display.putstr("Display.gfx_M to Display.gfx_T") ;
  HWLOGGING.println(F("Display.gfx_M to Display.gfx_T")) ;
  k = 180 ;
  l = 80 ;
  Display.gfx_MoveTo(k, l);
  Display.gfx_CircleFilled(k,l,5,BLUE) ;
  i = -90;   // 12 o'clock position
  while (i<270)
  {
    Display.gfx_Orbit(i, 30, &orbitx, &orbity);
    k = 3;
    if ((i % 90) == 0 )
      k = 5;
    Display.gfx_Circle(orbitx , orbity, k, BLUE);
    i += 30;   // each 30 degreees
  }
  
  Display.gfx_OutlineColour(YELLOW) ;
  Display.gfx_Panel(PANEL_RAISED,140,0,190,20, LIME) ;
  Display.gfx_OutlineColour(0) ;                    // turn outline off
  vx[0] = 36;   vy[0] = 110;
  vx[1] = 36;   vy[1] = 80;
  vx[2] = 50;   vy[2] = 80;
  vx[3] = 50;   vy[3] = 110;
  vx[4] = 76;   vy[4] = 104;
  vx[5] = 85;   vy[5] = 80;
  vx[6] = 94;   vy[6] = 104;
  vx[7] = 76;   vy[7] = 70;
  vx[8] = 85;   vy[8] = 76;
  vx[9] = 94;   vy[9] = 70;
  vx[10] = 110; vy[10] = 66;
  vx[11] = 110; vy[11] = 80;
  vx[12] = 100; vy[12] = 90;
  vx[13] = 120; vy[13] = 90;
  vx[14] = 110; vy[14] = 80;
  vx[15] = 101; vy[15] = 70;
  vx[16] = 110; vy[16] = 76;
  vx[17] = 119; vy[17] = 70;
  // house
  Display.gfx_Rectangle(6,50,66,110,RED);             // frame
  Display.gfx_Triangle(6,50,36,9,66,50,YELLOW);       // roof
  Display.gfx_Polyline(4, &vx[0], &vy[0], CYAN);            // door
  // man
  Display.gfx_Circle(85, 56, 10, BLUE);               // head
  Display.gfx_Line(85, 66, 85, 80, BLUE);             // body
  Display.gfx_Polyline(3, &vx[4], &vy[4], CYAN);      // legs
  Display.gfx_Polyline(3, &vx[7], &vy[7], BLUE);      // arms
  // woman
  Display.gfx_Circle(110, 56, 10, PINK);              // head
  Display.gfx_Polyline(5, &vx[10], &vy[10], BROWN);   // dress
  Display.gfx_Line(104, 104, 106, 90, PINK);          // left arm
  Display.gfx_Line(112, 90, 116, 104, PINK);          // right arm
  Display.gfx_Polyline(3, &vx[15], &vy[15], SALMON);  // dress
  
  vx[0] = 10; vy[0] = 130;
  vx[1] = 35; vy[1] = 125;
  vx[2] = 80; vy[2] = 130;
  vx[3] = 60; vy[3] = 145;
  vx[4] = 80; vy[4] = 160;
  vx[5] = 35; vy[5] = 170;
  vx[6] = 10; vy[6] = 160;
  Display.gfx_Polygon(7, vx, vy, RED);
  
  vx[0] = 110; vy[0] = 130;
  vx[1] = 135; vy[1] = 125;
  vx[2] = 180; vy[2] = 130;
  vx[3] = 160; vy[3] = 145;
  vx[4] = 180; vy[4] = 160;
  vx[5] = 135; vy[5] = 170;
  vx[6] = 110; vy[6] = 160;
  Display.gfx_PolygonFilled(7, vx, vy, RED);
  
  Display.gfx_PutPixel(40, 94, LIME) ;          // door knob
  Display.gfx_Rectangle(0,180, 10,200, AQUA) ;
  Display.gfx_RectangleFilled(20,180, 40,200, ORANGE) ;
  Display.gfx_ScreenCopyPaste(0,0, 0,280, 40,40) ;
  Display.gfx_ScreenMode(LANDSCAPE) ;
  //Display.gfx_Set(CLIPPING, ON) ;
  //Display.gfx_SetClipRegion() ;
  Display.gfx_Slider(SLIDER_RAISED, 210, 100, 250,10, BLUE, 100, 50) ; // coordinates are different because we are in landscape mode
  Display.gfx_ScreenMode(PORTRAIT) ;
  Display.gfx_Transparency(ON) ;
  Display.gfx_TransparentColour(YELLOW) ;  // how do we 'test' this?
  Display.gfx_Triangle(6,250, 36,209, 66,250,YELLOW);
  Display.gfx_TriangleFilled(110,210, 130,210, 120,230,CYAN);
}

void text_Tests(void)
{
  Display.gfx_Cls() ;
  HWLOGGING.println(F("Text Tests")) ;
  Display.putstr("Text Tests") ;
  
  Display.txt_Attributes(BOLD + INVERSE + ITALIC + UNDERLINED) ;
  Display.txt_Xgap(3) ;
  Display.txt_Ygap(3) ;
  Display.txt_BGcolour(YELLOW) ;
  Display.txt_FGcolour(WHITE) ;
  Display.txt_FontID(FONT3) ;
  Display.txt_MoveCursor(5, 0) ;
  Display.putstr("Hello There") ;
  
  Display.txt_MoveCursor(6, 2) ;
  Display.txt_Height(2) ;
  Display.txt_Width(2) ;
  Display.txt_Inverse(OFF) ;
  Display.txt_Italic(OFF) ;
  Display.txt_Opacity(TRANSPARENT) ;
  Display.txt_Set(TEXT_COLOUR, LIME) ;
  Display.txt_Underline(ON) ;
  Display.txt_Bold(OFF) ;
  Display.txt_Wrap(88) ;
  Display.putstr("Hello There") ;
  Display.txt_Height(1) ;
  Display.txt_Width(1) ;
  Display.txt_Wrap(0) ;              // reset
  Display.putCH('z') ;
  HWLOGGING.print(F("Char height= ")) ;
  HWLOGGING.print(Display.charheight('w')) ;
  HWLOGGING.print(F(" Width= ")) ;
  HWLOGGING.println(Display.charwidth('w')) ;
  Display.txt_BGcolour(BLACK) ;
  Display.txt_FGcolour(LIME) ;
  Display.txt_FontID(FONT3) ;
  Display.txt_MoveCursor(0,0) ;      // reset
}

void FAT_Tests(void)
{
  int i ;
  int j ;
  int k , handle;
  word w1, w2 ;
  char wks[512] ;
  char bytes[20] ;
  datar data ;
  Display.gfx_Cls() ;
  HWLOGGING.println(F("FAT Tests")) ;
  Display.putstr("FAT Tests\n") ;
  HWLOGGING.print(F("File Error= ")) ;
  HWLOGGING.println(Display.file_Error()) ;
  HWLOGGING.print(F("uSD has ")) ;
  HWLOGGING.print(Display.file_Count("*.*")) ;
  HWLOGGING.println(F(" Files")) ;
  Display.file_Dir("*.dat") ;     // should this get returned!? FindFirst and next certainly should, both need to be manual as they need "to(buffer)"
  
  if (Display.file_Exists(testdat))
  Display.file_Erase(testdat) ;
  handle = Display.file_Open(testdat, 'w') ;
  HWLOGGING.print(F("Handle= ")) ;
  HWLOGGING.println(handle) ;
  // write some stuff to uSD
  Display.file_PutC('a', handle) ;
  Display.file_PutW(1234, handle) ;
  Display.file_PutS("This is a Test", handle) ;
  Display.file_Close(handle) ;
  
  handle = Display.file_Open(testdat, 'r') ;
  HWLOGGING.print(F("Handle= ")) ;
  HWLOGGING.println(handle) ;
  // read it back and dump to screen
  HWLOGGING.println(Display.file_GetC(handle)) ;
  HWLOGGING.println(Display.file_GetW(handle)) ;
  i = Display.file_GetS(wks, 100, handle) ;
  HWLOGGING.println(F("Length=")) ;
  HWLOGGING.print(i) ;
  HWLOGGING.print(F(" String=")) ;
  HWLOGGING.println(wks) ;
  Display.file_Rewind(handle) ;
  i = Display.file_Read(bytes, 10, handle) ;
  HWLOGGING.print(F("Bytes read= ")) ;
  HWLOGGING.print(i) ;
  HWLOGGING.print(F(" Data=")) ;
  for (j = 0; j <= i-1; j++)
    HWLOGGING.print(bytes[j], HEX) ;
  i = Display.file_Tell(handle, &w1, &w2) ;
  HWLOGGING.print(F("\nFile pointer= ")) ;
  HWLOGGING.println((w1 << 16) + w2) ;
  i = Display.file_Size(handle, &w1, &w2) ;
  HWLOGGING.print(F("File size=")) ;
  HWLOGGING.println((w1 << 16) + w2) ;
  
  Display.file_Close(handle) ;
  Display.file_Erase(testdat) ;
  
  handle = Display.file_Open(testdat, 'w') ;
  HWLOGGING.print(F("Handle= ")) ;
  HWLOGGING.println(handle) ;
  for(i = 1; i <= 50; i++)
  {
    data.recnum = i ;
    k = i % 20 ;
    for (j = 0; j <= 4; j++)
    {
      data.values[j] = atoz[k+j] ;
      data.idx = atoz[rand() % 27] ;
    }
    Display.file_Write(sizeof(data), (char *)&data, handle) ;
  }
  Display.file_Close(handle) ;
  handle = Display.file_Open(testdat, 'r') ;
  Display.file_Index(handle, sizeof(data) >> 16, sizeof(data) & 0xFFFF, 5) ;
  i = Display.file_Read((char *)&data, sizeof(data), handle) ;
  HWLOGGING.print(data.recnum) ;
  HWLOGGING.print(data.values[0]) ;
  HWLOGGING.print(data.values[1]) ;
  HWLOGGING.print(data.values[2]) ;
  HWLOGGING.print(data.values[3]) ;
  HWLOGGING.print(data.values[4]) ;
  HWLOGGING.println(data.idx) ;
  Display.file_Seek(handle, 0, 10*sizeof(data)) ;
  i = Display.file_Read((char *)&data, sizeof(data), handle) ;
  HWLOGGING.print(data.recnum) ;
  HWLOGGING.print(data.values[0]) ;
  HWLOGGING.print(data.values[1]) ;
  HWLOGGING.print(data.values[2]) ;
  HWLOGGING.print(data.values[3]) ;
  HWLOGGING.print(data.values[4]) ;
  HWLOGGING.println(data.idx) ;
  Display.file_Close(handle) ;
  Display.file_Erase(testdat) ;
  
  Display.file_FindFirstRet("*.dat", wks) ;
  HWLOGGING.println(wks) ;
  Display.file_FindNextRet(wks) ;
  HWLOGGING.print(wks) ;
  
  handle = Display.file_Open(testdat, 'w') ;
  HWLOGGING.print(F("Handle= ")) ;
  HWLOGGING.println(handle) ;
  i = sizeof(Image) ;
  k = 0 ;
  while (i != 0)
  {
    j = min(512, i) ;
    memcpy_P(wks, (char *)&Image[k], 512) ;
    Display.file_Write(j, &wks[0], handle) ;
    i -= j ;
    k += j ;
  }
  Display.file_Close(handle) ;
  Display.gfx_Cls() ;
  handle = Display.file_Open(testdat, 'r') ;
  Display.file_Image(0,0,handle) ;
  Display.file_Close(handle) ;
  Display.gfx_MoveTo(40,10) ;
  Display.putstr("4D Logo") ;
  
  Display.file_Erase(testdat) ;
  handle = Display.file_Open(testdat, 'w') ;
  HWLOGGING.print(F("Handle= ")) ;
  HWLOGGING.println(handle) ;
  Display.file_ScreenCapture(0,0,100,32, handle) ;
  Display.file_Close(handle) ;
  
  handle = Display.file_Open(testdat, 'r') ;
  Display.file_Image(0,40,handle) ;
  Display.file_Rewind(handle) ;
  Display.file_Image(0,80,handle) ;
  Display.file_Rewind(handle) ;
  Display.file_Image(0,120,handle) ;
  Display.file_Close(handle) ;
  Display.file_Erase(testdat) ;
}

void IMG_Tests(void)
{
  word handle ;
  int i ;
  int j ;
  int k ;
  char wk[10] ;
  Display.gfx_Cls() ;
  Display.txt_MoveCursor(0, 5) ;
  Display.putstr("IMG Tests") ;
  HWLOGGING.println(F("IMG Tests")) ;
  handle = Display.file_LoadImageControl("gfx2demo.dat", "gfx2demo.gci", 1) ;
  HWLOGGING.print(handle) ;
  for (i = 0; i <= 4; i++)  // 4 is "default", same as no dark/light ening
  {
    Display.gfx_BevelShadow(i) ;
    Display.img_Darken(handle, 0) ;
    Display.img_Show(handle, 0) ;
    delay(250) ;
  }
  for (i = 3; i >= 0; i--)
  {
    Display.gfx_BevelShadow(i) ;
    Display.img_Lighten(handle, 0) ;
    Display.img_Show(handle, 0) ;
    delay(250) ;
  }
  Display.gfx_BevelShadow(3) ; // back to default
  
  Display.img_SetPosition(handle, 0, 0, 50) ; // move to a different position
  Display.img_Show(handle, 0) ;
  
  j = Display.img_GetWord(handle, 0, IMAGE_FRAMES) ;
  for (i = 0; i < j; i++)
  {
    Display.img_SetWord(handle, 0, IMAGE_INDEX, i) ;
    Display.img_Show(handle, 0) ;
    delay(500) ;
  }
  
  delay(500) ;
  Display.img_Disable(handle, ALL) ;
  j = 0 ;
  k = 30 ;
  for (i = 36; i <= 39; i++)
  {
    Display.img_SetPosition(handle, i, j, k) ; // move to a different position
    if (j == 119)
    {
      k = 179 ;
      j = 0 ;
    }
    else
      j = 119 ;
    Display.img_Enable(handle, i) ;
  }
  Display.gfx_Cls() ;
  Display.img_Show(handle,ALL) ;
  //  img_ClearAttributes(handle, index, value) ;
  //  img_SetAttributes(handle, index, value) ;
  if (ftouchtests)
  {
    Display.touch_Set(TOUCH_ENABLE) ;
    Display.putstr("Please Touch an Image\n") ;
    i = -1 ;
    do
    {
      j = Display.touch_Get(TOUCH_STATUS) ;
      if (j == TOUCH_PRESSED)
      i = Display.img_Touched(handle, ALL) ;
    } while (i == -1) ;
    Display.putstr("You touched Image Index ") ;
    itoa(i,wk,10) ;
    Display.putstr(wk) ;
  }
  Display.mem_Free(handle) ;
}

void Media_Tests(void)
{
  long i ;
  int j ;
  unsigned long k ;
  int l ;
  int m , handle ;
  unsigned char sector[512] ;
  Display.gfx_Cls() ;
  Display.putstr("Media Tests") ;
  HWLOGGING.println(F("Media Tests")) ;
  Display.file_Unmount() ;    // just to test this and media_Init
  i = Display.media_Init() ;
  if (i == 0)
  {
    HWLOGGING.print(F("Please insert the uSD card")) ;
    while (i = 0)
    {
      HWLOGGING.print(F(".")) ;
      i = Display.media_Init() ;
    }
  }
  
  HWLOGGING.print(F("\nFirst RAW sector=")) ;
  HWLOGGING.println(rawbase) ;
  trymount() ;
  
  handle = Display.file_Open("gfx2demo.gci", 'r') ;
  Display.file_Seek(handle, 0x49, 0x5800) ;   // location of large unicorn file
  i = (long)128 * 128 * 13 * 2 + 8 ;     // size of large unicorn file
  l = (i / 512) + 1 ;
  // we assume here that the raw partition is big enough to write this, could
  k = rawbase ;
  m = 1 ;
  while (i != 0)
  {
    HWLOGGING.print(F("Copying sector ")) ;
    HWLOGGING.print(m) ;
    HWLOGGING.print(F(" of ")) ;
    HWLOGGING.print(l) ;
    HWLOGGING.print(F("\r" )) ;    // Arduino terminal monitor does not seem to recognise \r as of 1.02
    j = min(512, i) ;
    Display.file_Read((char *)sector, j, handle) ;
    Display.media_SetSector(k >> 16, k & 0xFFFF) ;
    k++ ;
    Display.media_WrSector((char *)sector) ;
    i -= j ;
    m++ ;
  }
  Display.file_Close(handle) ;
  Display.media_SetSector(rawbase >> 16, rawbase & 0xFFFF) ;
  Display.media_Image(0,0) ;
  Display.media_SetSector(rawbase >> 16, rawbase & 0xFFFF) ;
  Display.media_Video(0,128) ;
  
  Display.media_SetSector(rawbase >> 16, rawbase & 0xFFFF) ;
  Display.media_WriteByte(0x11) ;
  Display.media_WriteWord(0x2233) ;
  Display.media_Flush() ;            // should write 0xFF over the rest of the sector
  Display.media_SetSector(rawbase >> 16, rawbase & 0xFFFF) ;
  HWLOGGING.print(Display.media_ReadByte(), HEX) ;
  HWLOGGING.print(F(" ")) ;
  HWLOGGING.print(Display.media_ReadWord(), HEX) ;
  HWLOGGING.print(F(" ")) ;
  HWLOGGING.println(Display.media_ReadWord(), HEX);
}

void Sound_Tests(void)
{
  int i ;
  int j ;
  Display.gfx_Cls() ;
  HWLOGGING.println(F("Sound Tests")) ;
  Display.putstr("Sound Tests") ;
  Display.snd_Volume(127) ;
  Display.snd_BufSize(2) ;
  HWLOGGING.println(F("Playing")) ;
  Display.file_PlayWAV(soundtest) ;
  delay(10000) ;
  HWLOGGING.println(F("Pausing")) ;
  Display.snd_Pause() ;
  delay(5000) ;
  HWLOGGING.println(F("Continuing")) ;
  Display.snd_Continue() ;
  delay(5000) ;
  HWLOGGING.println(F("Playing with pitch")) ;
  i = Display.snd_Pitch(0xFFFF) ;
  HWLOGGING.print(F("Original Pitch=")) ;
  HWLOGGING.println(i) ;
  delay(5000) ;
  Display.snd_Pitch(trunc(i*2 /*one octave, 1.0594631 one semitone*/)) ;
  delay(5000) ;
  Display.snd_Pitch(trunc(i/2)) ;
  delay(5000) ;
  Display.snd_Pitch(i) ;
  delay(5000) ;
  for (j = 1; j <= 5; j++)
  {
    i = Display.snd_Playing() ;
    HWLOGGING.print(F("Blocks remaining= ")) ;
    HWLOGGING.print(i) ;
    HWLOGGING.print(F("\r")) ;    // Arduino terminal monitor does not seem to recognise \r as of 1.02
    delay(2000) ;
  }
  HWLOGGING.println(F("")) ;
  for (i = 127; i >= 8; i--)
  {
    Display.snd_Volume(i) ; // 8 to 127 ;
    HWLOGGING.print(F("Volume=")) ;
    HWLOGGING.print(i) ;
    HWLOGGING.print(F("\r")) ;    // Arduino terminal monitor does not seem to recognise \r as of 1.02
    delay(100) ;
  }
  HWLOGGING.println(F("\nStopping")) ;
  Display.snd_Stop() ;
}

void Touch_Tests(void)
{
  int firstx ;
  int firsty ;
  int x ;
  int y ;
  int state ;
  Display.gfx_Cls() ;
  Display.putstr("Touch Tests\n") ;
  HWLOGGING.println(F("Touch Tests.")) ;
  Display.putstr("Please ensure Touch is only\ndetected in the Blue area") ;
  HWLOGGING.println(F("Detecting touch in Region")) ;
  Display.touch_Set(TOUCH_ENABLE) ;
  Display.touch_DetectRegion(100,100, 200, 200) ;
  Display.gfx_RectangleFilled(100,100, 200, 200, BLUE) ;
  do {} while (Display.touch_Get(TOUCH_STATUS) != TOUCH_PRESSED);
  Display.touch_Set(TOUCH_REGIONDEFAULT) ;
  Display.gfx_Cls() ;
  Display.putstr("Draw.. Drawing stops\nwhen touch released\n") ;
  HWLOGGING.println(F("Drawing")) ;
  
  while(Display.touch_Get(TOUCH_STATUS) != TOUCH_PRESSED)
  {      // we"ll wait for a touch
  }
  firstx = Display.touch_Get(TOUCH_GETX);                          // so we can get the first point
  firsty = Display.touch_Get(TOUCH_GETY);
  while(state != TOUCH_RELEASED)
  {
    state = Display.touch_Get(TOUCH_STATUS);                       // look for any touch activity
    x = Display.touch_Get(TOUCH_GETX);                             // grab the x
    y = Display.touch_Get(TOUCH_GETY);                             // and the y coordinates of the touch
    if (state == TOUCH_PRESSED)                               // if there"s a press
    {
      firstx = x;
      firsty = y;
    }
    if (state == TOUCH_MOVING)                                // if there"s movement
    {
      Display.gfx_Line(firstx, firsty, x, y, BLUE);                 // but lines are much better
      firstx = x;
      firsty = y;
    }
  }
  Display.putstr("Done!\n") ;
  Display.touch_Set(TOUCH_DISABLE) ;
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void mycallback(int ErrCode, unsigned char Errorbyte)
{
#ifdef LOG_MESSAGES
  const char *Error4DText[] = {"OK\0", "Timeout\0", "NAK\0", "Length\0", "Invalid\0"} ;
  HWLOGGING.print(F("Serial 4D Library reports error ")) ;
  HWLOGGING.print(Error4DText[ErrCode]) ;
  if (ErrCode == Err4D_NAK)
  {
    HWLOGGING.print(F(" returned data= ")) ;
    HWLOGGING.println(Errorbyte) ;
  }
  else
    HWLOGGING.println(F("")) ;
  while(1) ; // you can return here, or you can loop
#else
// Pin 13 has an LED connected on most Arduino boards. Just give it a name
#define led 13
  while(1)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(200);               // wait for a second
  }
#endif
}

void SetThisBaudrate(int Newrate)
{
  int br ;
  DisplaySerial.flush() ;
  DisplaySerial.end() ;
  switch(Newrate)
  {
    case BAUD_110    : br = 110 ;
      break ;
    case BAUD_300    : br = 300 ;
      break ;
    case BAUD_600    : br = 600 ;
      break ;
    case BAUD_1200   : br = 1200 ;
      break ;
    case BAUD_2400   : br = 2400 ;
      break ;
    case BAUD_4800   : br = 4800 ;
      break ;
    case BAUD_9600   : br = 9600 ;
      break ;
    case BAUD_14400  : br = 14400 ;
      break ;
    case BAUD_19200  : br = 19200 ;
      break ;
    case BAUD_31250  : br = 31250 ;
      break ;
    case BAUD_38400  : br = 38400 ;
      break ;
    case BAUD_56000  : br = 56000 ;
      break ;
    case BAUD_57600  : br = 57600 ;
      break ;
    case BAUD_115200 : br = 115200 ;
      break ;
    case BAUD_128000 : br = 133928 ; // actual rate is not 128000 ;
      break ;
    case BAUD_256000 : br = 281250 ; // actual rate is not  256000 ;
      break ;
    case BAUD_300000 : br = 312500 ; // actual rate is not  300000 ;
      break ;
    case BAUD_375000 : br = 401785 ; // actual rate is not  375000 ;
      break ;
    case BAUD_500000 : br = 562500 ; // actual rate is not  500000 ;
      break ;
    case BAUD_600000 : br = 703125 ; // actual rate is not  600000 ;
      break ;
  }
  DisplaySerial.begin(br) ;
  delay(50) ; // Display sleeps for 100
  DisplaySerial.flush() ;
}

void setbaudWait(word  Newrate)
{
  DisplaySerial.print((char)(F_setbaudWait >> 8));
  DisplaySerial.print((char)(F_setbaudWait));
  DisplaySerial.print((char)(Newrate >> 8));
  DisplaySerial.print((char)(Newrate));
  SetThisBaudrate(Newrate); // change this systems baud rate to match new display rate, ACK is 100ms away
  Display.GetAck() ;
}

#define RESETLINE 4

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(RESETLINE, OUTPUT);  // Set D4 on Arduino to Output (4D Arduino Adaptor V2 - Display Reset)
  digitalWrite(RESETLINE, 1);  // Reset the Display via D4
  delay(100);
  digitalWrite(RESETLINE, 0);  // unReset the Display via D4
  delay(5000);
 
#ifdef LOG_MESSAGES
  HWLOGGING.begin(19200);
  HWLOGGING.print(F("\n\nBigDemo for Arduino\n"));
#endif
}

void loop()
{
  int i, rc ;
  char wks[20] ;
  DisplaySerial.begin(9600) ;
  Display.TimeLimit4D   = 5000 ; // 5 second timeout on all commands
//  Display.Callback4D = NULL ;
  Display.Callback4D = mycallback ;

  Display.gfx_Cls() ;
  fFATtests   = trymount() ;
  fmediatests = false ;
  fimgtests   = false ;
  ftouchtests = false ;
  floadtests  = false ;
  fsoundtests = false ;
//  Display.gfx_Cls() ;
  Display.sys_GetModel(wks) ; // length is also returned, but we don't need that here
  HWLOGGING.print(F("Display model: ")) ;
  HWLOGGING.println(wks) ;
  Display.putstr("Display model: ") ;
  Display.putstr(wks) ;
  i = strlen(wks) ;
  if (   (wks[i] == 'T')
      || (wks[i-1] == 'T')
      || (wks[i-2] == 'T') )
    ftouchtests = true ;
  //for(int j=0; j<= i; j++)
  //{
  //  HWLOGGING.write(wks[j]);
  //}
  ftouchtests = true;  
  HWLOGGING.print(F("SPE2 Version: ")) ;
  HWLOGGING.println(Display.sys_GetVersion(),HEX) ;
  HWLOGGING.print(F("PmmC Version: ")) ;
  HWLOGGING.println(Display.sys_GetPmmC(),HEX) ;
  if (fFATtests)
  {
    if (RAWPartitionbase(&rawbase))
      fmediatests = true ;
    if (   (Display.file_Exists(gfx2demodat) != 0)
        && (Display.file_Exists(gfx2demogci) != 0) )
      fimgtests = true ;
    if (   (Display.file_Exists(functest) != 0)
        && (Display.file_Exists(functestg) != 0)
        && (Display.file_Exists(functestd) != 0) )
      floadtests = true ;
    if (Display.file_Exists(soundtest))
      fsoundtests = true ;
  }
  if (fFATtests)
  {
    HWLOGGING.println(F("FAT Tests will be done")) ;
    if (fmediatests)
    {
      if (Display.file_Exists(gfx2demogci))
      HWLOGGING.println(F("Media tests will be done\n")) ;
      else
      {
        HWLOGGING.print(F("Media tests cannot be done, missing ")) ;
        HWLOGGING.println(gfx2demogci) ;
        fmediatests = false ;
      }
    }
    else
      HWLOGGING.println(F("Media tests cannot be done, no RAW Partition")) ;
    if (fimgtests)
      HWLOGGING.println(F("Image tests will be done")) ;
    else
    {
      HWLOGGING.print(F("Image tests will not be done, missing ")) ;
      HWLOGGING.print(gfx2demogci) ;
      HWLOGGING.print(F(" or ")) ;
      HWLOGGING.println(gfx2demodat) ;
    }
    if (floadtests)
      HWLOGGING.println(F("Load tests will be done")) ;
    else
    {
      HWLOGGING.print(F("Load tests will not be done, missing ")) ;
      HWLOGGING.print(functest) ;
      HWLOGGING.print(F(" or ")) ;
      HWLOGGING.print(functestg) ;
      HWLOGGING.print(F(" or ")) ;
      HWLOGGING.println(functestd) ;
    }
    if (fsoundtests)
      HWLOGGING.println(F("Sound tests will be done")) ;
    else
    {
      HWLOGGING.print(F("Sound tests will not be done, missing ")) ;
      HWLOGGING.println(soundtest) ;
    }
  }
  else
  {
    HWLOGGING.println(F("FAT Tests cannot be done, either no uSD card or no FAT partition")) ;
    HWLOGGING.println(F("Neither will Media, Image, Load or Sound Tests")) ;
  }
  if (ftouchtests)
    HWLOGGING.println(F("Touch Tests will be done")) ;
  else
    HWLOGGING.println(F("Touch Tests will not be done, display doesn't appear capable")) ;
    
//  HWLOGGING.println(freeRam()) ;
  delay(5000) ;
  
#ifdef TEST_OTHER
  gfx_Part1() ; // GFX Part 1 tests
  delay(5000) ;
  
  gfx_Part2() ; // GFX Part 2 tests
  delay(5000) ;
  
  text_Tests() ; // text tests
  delay(5000) ;
#endif
  
#ifdef TEST_USD
  if (fFATtests)
  {
    FAT_Tests() ;
    delay(5000) ;
  }
  if (fimgtests)
  {
    IMG_Tests() ;
    delay(5000) ;
  }
 
  if (fmediatests)
  {
    Media_Tests() ;
    delay(5000) ;
  }

  if (floadtests)
  {
    Function_Tests() ;
    delay(5000) ;
  }

  if (fsoundtests)
  {
    Sound_Tests() ;
    delay(5000) ;
  }
#endif
  
#ifdef TEST_OTHER
  if (ftouchtests)
  {
    Touch_Tests() ;
    delay(5000) ;
  }

  setbaudWait(BAUD_19200) ;
  Display.putstr("Hello at 19200\n") ;
  setbaudWait(BAUD_9600) ;
  Display.putstr("Back to 9600\n") ;
  delay(5000) ;
#endif 
}














