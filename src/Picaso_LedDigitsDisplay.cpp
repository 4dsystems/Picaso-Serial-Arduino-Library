#if (ARDUINO >= 100)
	#include "Arduino.h" // for Arduino 1.0
#else
	#include "WProgram.h" // for Arduino 23
#endif

#include "Picaso_Serial_4DLib.h"
#include "Picaso_Const4D.h"

// WARNING, this code will crash if newval exceeds maximum displayable number
void LedDigitsDisplay(Picaso_Serial_4DLib Display, word hndl, word newval, word index, word left, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks)
{
  word i, k, l, lb ;
  l = 1 ;
  for (i = 1; i < Digits; i++)
    l *= 10 ;
  lb = LeadingBlanks ;
  for (i = 0; i < Digits; i++)
  {
    k = newval / l ;
    newval -= k * l ;
    if ( lb && (i < Digits - MinDigits) )
    { 
      if (k == 0)
        k = 10 ;
      else
        lb = 0 ;
    }
    l /= 10 ;
    Display.img_SetWord(hndl, index, IMAGE_INDEX, k);
    Display.img_SetWord(hndl, index, IMAGE_XPOS, left+i*WidthDigit) ;
    Display.img_Show(hndl, index);
  }
}

