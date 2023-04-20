// color conversion routines seem to be based on http://support.microsoft.com/kb/29240
// My copy seem to have been around since the MSDOS days, I don't know if it came from another source
#define HLSMAX     127                     // HLS vary over 0-HLSMAX
#define HLSMAXm2d3 HLSMAX* 2 / 3 
#define HLSMAXd12  HLSMAX / 12 
#define HLSMAXd6   HLSMAX / 6 
#define HLSMAXd2   HLSMAX / 2 
#define HLSMAXd3   HLSMAX / 3 
#define RGBMAX     127                     // R,G, and B vary over 0-RGBMAX
#define RGBMAXm2   RGBMAX*2 
// HLSMAX BEST IF DIVISIBLE BY 6
// RGBMAX, HLSMAX must each fit in a byte.

// Hue is undefined if Saturation is 0 (grey-scale) *
// This value determines where the Hue scrollbar is
// initially set for achromatic colors
#define UNDEFINED  127 * 2 / 3  

uint16_t RGBs2COL(int16_t r, int16_t g, int16_t b) ;

void c565toRGBs(int16_t i565, int16_t * red, int16_t * green, int16_t * blue);

void RGB2HLS(int16_t red, int16_t green, int16_t blue, int16_t * h, int16_t * l, int16_t * s) ;

uint16_t hue_RGB(int16_t Hin, int16_t M1, int16_t M2) ;

void HLS2RGB(int16_t H, int16_t L, int16_t S, int16_t * r, int16_t * g, int16_t * b);

