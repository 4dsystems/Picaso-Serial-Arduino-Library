#if (ARDUINO >= 100)
	#include "Arduino.h" // for Arduino 1.0
#else
	#include "WProgram.h" // for Arduino 23
#endif

// WARNING, this code will crash if newval exceeds maximum displayable number
void LedDigitsDisplay(Picaso_Serial_4DLib Display, word hndl, word newval, word index, word left, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) ;
