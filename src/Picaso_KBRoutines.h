#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define KbDown      0
#define KbMvt       1
#define KbState     2
#define KbIgn       3
#define KbCaps      4
#define KbShift1    5
#define KbShift2    6
#define KbCtrl1     7
#define KbCtrl2     8
#define KbLock      9
#define KbButtons   10
#define KbShiftCaps 11

typedef void        (*Callback) (int);

void refreshstate(Picaso_Serial_4DLib Display, word hndl, int8_t iKB, int8_t * oKB) ;

void kbDown(Picaso_Serial_4DLib Display, word hndl, int8_t iKB, int8_t * oKB, uint8_t * KBKeys, int8_t key, Callback handler) ;

void kbUp(Picaso_Serial_4DLib Display, word hndl, int8_t iKB, int8_t * oKB) ;

void setkeystate(Picaso_Serial_4DLib Display, word hndl, int8_t key, int8_t idx) ;


