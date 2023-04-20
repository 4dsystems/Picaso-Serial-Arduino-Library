#if (ARDUINO >= 100)
	#include "Arduino.h" // for Arduino 1.0
#else
	#include "WProgram.h" // for Arduino 23
#endif

// Warning, ensure correct number of digits are specified, especially if -ve numbers are required as minus sign
// will overlay most significant digit if there are not enough digits.
void LedDigitsDisplaySigned(Picaso_Serial_4DLib Display, word hndl, int16_t newval, word index, word left, word Digits, word MinDigits, word WidthDigit, word LeadingBlanks) ;
