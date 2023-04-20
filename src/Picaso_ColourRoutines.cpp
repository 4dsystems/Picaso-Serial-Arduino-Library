#if (ARDUINO >= 100)
	#include "Arduino.h" // for Arduino 1.0
#else
	#include "WProgram.h" // for Arduino 23
#endif

//#include "Picaso_Serial_4DLib.h"
//#include "Picaso_Const4D.h"

#define HLSMAX     127                     // HLS vary over 0-HLSMAX
#define HLSMAXm2d3 (HLSMAX* 2 / 3 )
#define HLSMAXd12  (HLSMAX / 12 )
#define HLSMAXd6   (HLSMAX / 6 )
#define HLSMAXd2   (HLSMAX / 2 )
#define HLSMAXd3   (HLSMAX / 3 )
#define RGBMAX     127                     // R,G, and B vary over 0-RGBMAX
#define RGBMAXm2   (RGBMAX*2) 
// HLSMAX BEST IF DIVISIBLE BY 6
// RGBMAX, HLSMAX must each fit in a byte.

// Hue is undefined if Saturation is 0 (grey-scale) *
// This value determines where the Hue scrollbar is
// initially set for achromatic colors
#define UNDEFINED  (127 * 2 / 3 ) 

// color conversion routines seem to be based on http://support.microsoft.com/kb/29240
// My copy seem to have been around since the MSDOS days, I don't know if it came from another source

uint16_t RGBs2COL(int16_t r, int16_t g, int16_t b)
{
    return (b >> 2) | (g & 0x7E) << 4 | (r & 0x7c) << 9  ;
}

void c565toRGBs(int16_t i565, int16_t * red, int16_t * green, int16_t * blue)
{
    *red   = (i565 & 0xF800) >> 9 ;
    *green = (i565 & 0x07E0) >> 4 ;
    *blue  = (i565 & 0x001F) << 2 ;
}

void RGB2HLS(int16_t red, int16_t green, int16_t blue, int16_t * h, int16_t * l, int16_t * s)
{
    int16_t  cMax, cMin, Rdelta, Gdelta, Bdelta, cMpM, cMmM ;
    // calculate lightness
    cMax = max( max(red,green), blue);
    cMin = min( min(red,green), blue);
    cMpM = cMax+cMin ;
    cMmM = cMax-cMin ;

    *l = ( (cMpM*HLSMAX) + RGBMAX ) / RGBMAXm2;

    if (cMax == cMin) // r=g=b --> achromatic case
    {
        *s = 0;
        *h = UNDEFINED;
    }
    else // chromatic case
    {
        // saturation
        if (*l <= (HLSMAX/2))
            *s = ( (cMmM*HLSMAX) + (cMpM / 2) ) / cMpM ;
        else
            *s = ( (cMmM*HLSMAX) + ((RGBMAXm2-cMpM) / 2) ) / (RGBMAXm2-cMpM);

        // hue
        Rdelta = ( ((cMax-red)* HLSMAXd6) + (cMmM / 2) ) / cMmM;
        Gdelta = ( ((cMax-green)* HLSMAXd6) + (cMmM / 2) ) / cMmM;
        Bdelta = ( ((cMax-blue)* HLSMAXd6) + (cMmM / 2) ) / cMmM;

        if (red == cMax)
            *h = Bdelta - Gdelta ;
        else if (green == cMax)
            *h = HLSMAXd3 + Rdelta - Bdelta ;
        else
            *h = HLSMAXm2d3 + Gdelta - Rdelta;

        if (*h < 0) *h += HLSMAX;
        if (*h > HLSMAX) *h -= HLSMAX;
    }
}

int16_t hue_RGB(int16_t Hin, int16_t M1, int16_t M2)
{
    int16_t Value ;
    if (Hin < 0)
        Hin += HLSMAX ;
    else if (Hin > HLSMAX)
        Hin -= HLSMAX ;

    if (Hin < HLSMAXd6)
        Value = M1 + ( (M2 - M1) * Hin + HLSMAXd12 ) / HLSMAXd6 ;
    else if (Hin < HLSMAXd2 )
        Value = M2 ;
    else if (Hin < HLSMAXm2d3)
        Value = M1 + ( (M2 - M1) * (HLSMAXm2d3 - Hin) + HLSMAXd12) / HLSMAXd6 ;
    else
        Value = M1 ;
    return Value ;
}

void HLS2RGB(int16_t H, int16_t L, int16_t S, int16_t * red, int16_t * green, int16_t * blue)
{
    int16_t M1, M2 ;

    if (S == 0)
    {
        *red   = L ;
        *green = L ;
        *blue  = L ;
    }
    else
    {
        if (L <= HLSMAXd2)
            M2 = (L * (HLSMAX + S) + HLSMAXd2) / HLSMAX ;
        else
            M2 = L + S - ((L * S + HLSMAXd2) / HLSMAX) ;

        M1 = 2 * L - M2 ;
        // Determine levels of primary colours.
        if ((H > HLSMAX ) || (H < 0)) H = 0 ;
        *red   = hue_RGB( H+HLSMAXd3, M1, M2 ) ;
        *green = hue_RGB( H,          M1, M2 ) ;
        *blue  = hue_RGB( H-HLSMAXd3, M1, M2 ) ;
    }

 }
