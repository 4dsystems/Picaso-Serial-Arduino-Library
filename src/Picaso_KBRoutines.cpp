#include "Picaso_Serial_4DLib.h"
#include "Picaso_Const4D.h"

#include "Picaso_KBRoutines.h"

#define KbShiftBit        01
#define KbCapsBit         02
#define KbShiftCapsBits   03
#define KbCtrlBit         04

#if (ARDUINO >= 100)
 #include "Arduino.h" // for Arduino 1.0
#else
 #include "WProgram.h" // for Arduino 23
#endif

void refreshstate(Picaso_Serial_4DLib Display, word hndl, int8_t iKB, int8_t * oKB)
{
  int8_t shifted ;
  shifted = oKB[KbState] & KbShiftCapsBits ;
  if (!shifted || (shifted == KbShiftCapsBits))
  {
    shifted = 0 ;
    oKB[KbCaps] = 0 ;
  }
  else
  {
    shifted = 1 ;
    oKB[KbCaps] = 2 ;
  }
  setkeystate(Display, hndl, iKB, shifted) ;
  if (oKB[KbState] & KbCapsBit)
    setkeystate(Display, hndl, iKB + oKB[KbLock],1) ;
  if ((oKB[KbState] & KbShiftBit) && (shifted))
  {
    setkeystate(Display, hndl, iKB + oKB[KbShift1],1) ;
    setkeystate(Display, hndl, iKB + oKB[KbShift2],1) ;
  }
  if (oKB[KbState] & KbCtrlBit)
  {
    setkeystate(Display, hndl, iKB +oKB[KbCtrl1],1) ;
    setkeystate(Display, hndl, iKB + oKB[KbCtrl2],1) ;
  }
}


void kbDown(Picaso_Serial_4DLib Display, word hndl, int8_t iKB, int8_t * oKB, uint8_t * KBKeys, int8_t key, Callback handler)
{
  int8_t keyval ;
  oKB[KbMvt] = 1 ;
  oKB[KbIgn] = 0 ;
  if ((key == oKB[KbShift1]) || (key == oKB[KbShift2]))
  {
    if (oKB[KbState] & KbShiftBit)
    {
      oKB[KbState] &= ~KbShiftBit ;
      oKB[KbMvt] = 0 ;
    }
    else
      oKB[KbState] |= KbShiftBit ;
    refreshstate(Display, hndl, iKB, oKB) ;
    oKB[KbIgn] = 1 ;
  }
  else if ((key == oKB[KbCtrl1]) || (key == oKB[KbCtrl2]))
  {
    if (oKB[KbState] & KbCtrlBit)
    {
      oKB[KbState] &= ~KbCtrlBit ;
      oKB[KbMvt] = 0 ;
    }
    else
      oKB[KbState] |= KbCtrlBit ;
    setkeystate(Display, hndl, iKB + oKB[KbCtrl1],oKB[KbMvt]) ;
    key = oKB[KbCtrl2] ;
    oKB[KbIgn] = 1 ;
  }
  else if (key == oKB[KbLock])
  {
    if (oKB[KbState] & KbCapsBit)
    {
      oKB[KbState] &= ~KbCapsBit ;
      oKB[KbMvt] = 0 ;
    }
    else
      oKB[KbState] |= KbCapsBit ;
    refreshstate(Display, hndl, iKB, oKB) ;
    oKB[KbIgn] = 1 ;
  }

  if (!oKB[KbIgn])
  {
    if (oKB[KbShiftCaps])
      keyval = (oKB[KbState] & KbShiftCapsBits) * oKB[KbButtons] - 1 ;
    else if (((oKB[KbState] & KbShiftCapsBits) == 0) || ((oKB[KbState] & KbShiftCapsBits) == KbShiftCapsBits))
      keyval = - 1 ;
    else
      keyval = oKB[KbButtons] - 1 ;
    keyval = KBKeys[key+keyval] ;
    if (oKB[KbState] & KbCtrlBit) keyval &= 0x9F ;
    handler(keyval & 0xFF) ;
    setkeystate(Display, hndl, iKB + key,oKB[KbMvt]+oKB[KbCaps]) ;
  }
  oKB[KbDown] = key ;
}

void setkeystate(Picaso_Serial_4DLib Display, word hndl, int8_t key, int8_t idx)
{
  Display.img_SetWord(hndl, key,IMAGE_INDEX, idx);
  Display.img_Show(hndl,key) ;
}

void kbUp(Picaso_Serial_4DLib Display, word hndl, int8_t iKB, int8_t * oKB)
{
  if (!oKB[KbIgn])
  {
    setkeystate(Display, hndl, iKB + oKB[KbDown], oKB[KbCaps]) ;
    if (oKB[KbState] & KbShiftBit)
    {
      oKB[KbState] &= ~KbShiftBit ;
      refreshstate(Display, hndl, iKB, oKB) ;
    }
    if (oKB[KbState] & KbCtrlBit)
    {
      oKB[KbState] &= ~KbCtrlBit ;
      setkeystate(Display, hndl, iKB + oKB[KbCtrl1],0) ;
      setkeystate(Display, hndl, iKB + oKB[KbCtrl2],0) ;
    }
    oKB[KbDown] = -1 ;
  }
}

