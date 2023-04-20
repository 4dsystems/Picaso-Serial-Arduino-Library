#if (ARDUINO >= 100)
	#include "Arduino.h" // for Arduino 1.0
#else
	#include "WProgram.h" // for Arduino 23
#endif

#include "Picaso_Serial_4DLib.h"
#include "Picaso_Const4D.h"

// Warning, ensure correct number of digits are specified, especially if -ve numbers are required as minus sign
// will overlay most significant digit if there are not enough digits.
void LedDigitsDisplaySigned(Picaso_Serial_4DLib Display, word hndl, int16_t newval, word index, word left, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) 
{
  int16_t i, m, lstb, nv;

  left = left + WidthDigit * (Digits-1) ;
  nv = newval ;
  lstb = 1 ;
  for (i = Digits; i > 0; i--)
  {
    m = nv % 10 ;
    if ( LeadingBlanks && (i <= Digits - MinDigits) )
    {
      if (nv == 0)
      {
        m = 10 ;
        if (lstb == 1) 
          lstb = i ;
      }
    }
 

    Display.img_SetWord(hndl, index, IMAGE_INDEX, abs(m));
    Display.img_SetWord(hndl, index, IMAGE_XPOS, left) ;
    Display.img_Show(hndl, index);
    nv /= 10 ;
  
    left -= WidthDigit ;
  }
  if (newval < 0)
  {
    left += lstb * WidthDigit ;
    Display.img_SetWord(hndl, index, IMAGE_INDEX, 11);
    Display.img_SetWord(hndl, index, IMAGE_XPOS, left) ;
    Display.img_Show(hndl, index);
  }

}