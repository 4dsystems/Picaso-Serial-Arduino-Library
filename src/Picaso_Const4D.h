// SPE Version 1.2 added peekM and pokeM functions
// SPE Version 1.1 added bus_ and pin_ functions
// undef windows definitions that are also 4DGL definitions
#ifdef TRANSPARENT
    #undef TRANSPARENT
#endif
#ifdef OPAQUE
    #undef OPAQUE
#endif
#ifdef BAUD_110
    #undef BAUD_110
#endif
#ifdef BAUD_300
    #undef BAUD_300
#endif
#ifdef BAUD_600
    #undef BAUD_600
#endif
#ifdef BAUD_1200
    #undef BAUD_1200
#endif
#ifdef BAUD_2400
    #undef BAUD_2400
#endif
#ifdef BAUD_4800
    #undef BAUD_4800
#endif
#ifdef BAUD_9600
    #undef BAUD_9600
#endif
#ifdef BAUD_14400
    #undef BAUD_14400
#endif
#ifdef BAUD_19200
    #undef BAUD_19200
#endif
#ifdef BAUD_38400
    #undef BAUD_38400
#endif
#ifdef BAUD_57600
    #undef BAUD_57600
#endif
#ifdef BAUD_115200
    #undef BAUD_115200
#endif

// baud divisor rates for setbaud(n);
#define MIDI                    9
#define BAUD_110                0
#define BAUD_300                1
#define BAUD_600                2
#define BAUD_1200               3
#define BAUD_2400               4
#define BAUD_4800               5
#define BAUD_9600               6
#define BAUD_14400              7
#define BAUD_19200              8
#define BAUD_31250              9
#define BAUD_38400              10
#define BAUD_56000              11
#define BAUD_57600              12
#define BAUD_115200             13
#define BAUD_128000             14
#define BAUD_256000             15
#define BAUD_300000             16
#define BAUD_375000             17
#define BAUD_500000             18
#define BAUD_600000             19

//------------------------------------------------------------------//
// CONSTANTS
//------------------------------------------------------------------//

// generic constants
#define ENABLE                  1
#define DISABLE                 0
#define HI                      1
#define LO                      0
#define INPUT4d                 1
#define OUTPUT4d                0
#define ON                      1
#define OFF                     0

//------------------------------------------------------------------------------
// Pin related constants
//------------------------------------------------------------------------------
#define IO1_PIN                 1 // pin 2 J1
#define IO2_PIN                 2 // pin 1 J1
#define IO3_PIN                 3 // pin 3 J1
#define IO4_PIN                 4 // pin 5 J1 (also used for BUS_RD)
#define IO5_PIN                 5 // pin 9 J2 (also used for BUS_WR)
#define BUS_RD_PIN              4 // pin 5 J1 (alias IO4_PIN)
#define BUS_WR_PIN              5 // pin 9 J2 (alias IO5_PIN)
#define BACKLITE                6 // backlite control pin
#define AUDIO_ENABLE            7 // amplifier chip control pin
#define BUS_0                   8 // pin 27 of J1
#define BUS_1                   9 // pin 25 of J1
#define BUS_2                   10 // pin 23 of J1
#define BUS_3                   11 // pin 21 of J1
#define BUS_4                   12 // pin 19 of J1
#define BUS_5                   13 // pin 17 of J1
#define BUS_6                   14 // pin 13 of J2
#define BUS_7                   15 // pin 11 of J2

//------------------------------------------------------------------------------
//gfx_Set() related constants
//------------------------------------------------------------------------------
#define PEN_SIZE                16 // not necessary to use (legacy mode)
#define BACKGROUND_COLOUR       17
#define OBJECT_COLOUR           18 // line / circle / rectangle generic colour
#define CLIPPING                19 // clipping ON / OFF
#define TRANSPARENT_COLOUR      20 // (only on displays with specific hware feature)
#define TRANSPARENCY            21 // 0 = OFF, 1 = ON (only on displays with specific hware feature)
#define FRAME_DELAY             22 // legacy mode, see pokeB(IMAGE_DELAY, n);
#define SCREEN_MODE             23 // LANDSCAPE, LANDSCAPE_R, PORTRAIT, PORTRAIT_R
#define OUTLINE_COLOUR          24 // if not BLACK (0) , used for outline around circles,rectangles and filled polygons
#define CONTRAST                25 // for OLED,cahnge contrast, for LCD on or off only
#define LINE_PATTERN            26 // used for patterned lines, 16bit value (0 = no pattern, '1's = pattern)
#define COLOUR_MODE             27 // select 8 or 16 bit colour mode
#define BEVEL_WIDTH             28 // button bevel width
#define BEVEL_SHADOW            29 // button bevel shadow depth
#define X_ORIGIN                30 // display position X offset
#define Y_ORIGIN                31 // display position X offset


//gfx_Get() related constants
#define X_MAX                   0 // current orientations screen maximum X co-ordinate
#define Y_MAX                   1 // current orientations screen maximum Y co-ordinate
#define LEFT_POS                2 // last objects left co-ord
#define TOP_POS                 3 // last objects top co-ord
#define RIGHT_POS               4 // last objects right co-ord
#define BOTTOM_POS              5 // last objects bottom co-ord
#define X_ORG                   6 // display position X offset
#define Y_ORG                   7 // display position X offset




#define SOLID                   0 // PEN_SIZE
#define OUTLINE                 1 // PEN_SIZE
#define STYLE1                  2
#define STYLE2                  3

#define LANDSCAPE               0 // SCREEN_MODE (north)
#define LANDSCAPE_R             1 // SCREEN_MODE (south)
#define PORTRAIT                2 // SCREEN_MODE (west)
#define PORTRAIT_R              3 // SCREEN_MODE (east)

#define COLOUR8                 1 // COLOUR_MODE 8 bit colour mode (not supported)
#define COLOUR16                0 // COLOUR_MODE 16 bit colour mode


#define DOWN                    0
#define UP                      1
#define HIDE                    2
#define SELECT                  3
#define SELECT_MULTIPLE         4


#define BUTTON_DOWN             0
#define BUTTON_UP               1

#define SLIDER_SUNKEN           0
#define SLIDER_RAISED           1
#define SLIDER_HIDE             2

#define PROGRESSBAR_RAISED      0xFFFF
#define PROGRESSBAR_SUNKEN      0xFFFE
#define PROGRESSBAR_HIDE        2

#define PANEL_SUNKEN            0
#define PANEL_RAISED            1
#define PANEL_HIDE              2


//------------------------------------------------------------------------------
//txt_Set() related constants
//------------------------------------------------------------------------------
#define TEXT_COLOUR             0 // text foreground colr
#define TEXT_BACKGROUND         1 // text background colr
#define TEXT_HIGHLIGHT          1 // text background colr
#define FONT_ID                 2 // default 0, else points to data statement font
#define FONT_SIZE               2 // compatibility
#define TEXT_WIDTH              3 // text width multiplier
#define TEXT_HEIGHT             4 // text height multiplier
#define TEXT_XGAP               5 // horizontal text gap (default 1)
#define TEXT_YGAP               6 // vertical text gap (default 1)
#define TEXT_PRINTDELAY         7 // for 'teletype' like effect when printing
#define TEXT_OPACITY            8 // text mode flag, TRANSPARENT or OPAQUE
#define TEXT_BOLD               9 // embolden text (auto reset)
#define TEXT_ITALIC             10 // italicize text (auto reset)
#define TEXT_INVERSE            11 // invert text (auto reset)
#define TEXT_UNDERLINED         12 // underline text (auto reset)
#define TEXT_ATTRIBUTES         13 // controls BOLD/ITALIC/INVERSE/UNDERLINE simultaneously
#define TEXT_WRAP               14 // Sets the pixel position where text wrap will occur at RHS




//------------------------------------------------------------------------------
//txt_Set() related arguments
// NB:- FONT4 must be inherited if required,
// eg #inherit "FONT4.fnt"
//------------------------------------------------------------------------------
#define FONT1                   0 // (same as system font)
#define FONT2                   1
#define FONT3                   2

#define TRANSPARENT             0 // TEXT_OPACITY  transparent  text
#define OPAQUE                  1 // TEXT_OPACITY  opaque text

#define BOLD                    16 // TEXT_ATTRIBUTES bold text
#define ITALIC                  32 // TEXT_ATTRIBUTES italic text
#define INVERSE                 64 // TEXT_ATTRIBUTES inverse text
#define UNDERLINED              128 // TEXT_ATTRIBUTES underlined



//touch_Set() related constants
#define TOUCH_ENABLE            0
#define TOUCH_DISABLE           1
#define TOUCH_REGIONDEFAULT     2

//touch_Get() related constants
#define TOUCH_STATUS            0
#define TOUCH_GETX              1
#define TOUCH_GETY              2
#define NOTOUCH                 0
#define TOUCH_PRESSED           1
#define TOUCH_RELEASED          2
#define TOUCH_MOVING            3

// image control offset related constants
#define IMG_COUNT               0
#define IMG_ENTRYLEN            1
#define IMG_MODE                2
#define IMG_GCI_FILENAME        3
#define IMG_DAT_FILENAME        4
#define IMG_GCIFILE_HANDLE      5

// image attribute flags
// for img_SetAttributes(...) and img_ClearAttributes(...)
#define I_ENABLED               0x8000 // bit 15,  set for image enabled
#define I_DARKEN                0x4000 // bit 14,  display dimmed
#define I_LIGHTEN               0x2000 // bit 13,  display bright
#define I_TOUCHED               0x1000 // bit 12,  touch test result
#define I_Y_LOCK                0x0800 // bit 11,  stop Y movement
#define I_X_LOCK                0x0400 // bit 10,  stop X movement
#define I_TOPMOST               0x0200 // bit 9,   draw on top of other images next update (auto reset)
#define I_STAYONTOP             0x0100 // bit 8,   draw on top of other images always
#define I_MOVIE                 0x0080 // bit 7,   image is a movie
#define I_NOGROUP               0x0040 // bit 6,   set to exclude image refresh when using img_Show(hndl, ALL);
#define I_TOUCH_DISABLE         0x0020 // bit 5,   set to disable touch for this image, default=1 for movie, 0 for image
#define I_COLOUR16              0x0010 // bit 4,   indicates 16 bit colour mode
    // bits 0-3 reserved


#define ALL                     0xFFFF // argument for img_xxx functions to update all images

// image control entry offsets
#define IMAGE_LOWORD            0 // WORD image address LO
#define IMAGE_HIWORD            1 // WORD image address HI
#define IMAGE_XPOS              2 // WORD image location X
#define IMAGE_YPOS              3 // WORD image location Y
#define IMAGE_WIDTH             4 // WORD image width
#define IMAGE_HEIGHT            5 // WORD image height
#define IMAGE_FLAGS             6 // WORD image flags
#define IMAGE_DELAY             7 // WORD inter frame delay
#define IMAGE_FRAMES            8 // WORD number of frames
#define IMAGE_INDEX             9 // WORD current frame
#define IMAGE_CLUSTER           10 // WORD image start cluster  pos (for FAT16 only)
#define IMAGE_SECTOR            11 // WORD image start sector in cluster pos (for FAT16 only)
#define IMAGE_TAG               12 // WORD user variable #1
#define IMAGE_TAG2              13 // WORD user variable #2

// DISK struct offsets
#define DISK_FIRST_SECT_LO      0 // DWORD address of the first sector of the FAT partition (LO word)
#define DISK_FIRST_SECT_HI      1 //       address of the first sector of the FAT partition (HI word)
#define DISK_FAT_LO             2 // DWORD address of FAT (LO word)
#define DISK_FAT_HI             3 //       address of FAT (HI word)
#define DISK_ROOT_LO            4 // DWORD address of root directory (LO word)
#define DISK_ROOT_HI            5 //       address of root directory (HI word)
#define DISK_DATA_LO            6 // DWORD address of data area (LO word)
#define DISK_DATA_HI            7 //       address of data area (HI word)
#define DISK_MAXCLUS_LO         8 // DWORD max number of clusters in partition (LO word)
#define DISK_MAXCLUS_HI         9 //       max number of clusters in partition (HI word)
#define DISK_MAXROOT            10 // WORD  max entries in root directory
#define DISK_FATSIZE            11 // WORD  number of sectors in FAT
#define DISK_FATCOPIES          12 // WORD  number of fat copies
#define DISK_SECT_PER_CLUS      13 // WORD  number of sectors per cluster
#define DISK_TYPE               14 // WORD  type of fat
#define DISK_BUF                15 // WORD  pointer to 512 byte info buffer




// FILE struct offsets
#define FILE_FIRST_CLUSTER      0 // WORD  first cluster
#define FILE_CURR_CLUSTER       1 // WORD  current cluster in file
#define FILE_CURR_SECTOR        2 // WORD  sector in current cluster
#define FILE_CURR_SECTOR_POS    3 // WORD  position in current sector
#define FILE_CURR_SECTOR_TOP    4 // WORD  number bytes in current sector buffer
#define FILE_SEEK_POS_LO        5 // DWORD position in the file (LO word)
#define FILE_SEEK_POS_HI        6 //       position in the file (HI word)
#define FILE_SIZE_LO            7 // DWORD file size (LO word)
#define FILE_SIZE_HI            8 //       file size (HI word)
#define FILE_TIME               9 // WORD  last update time
#define FILE_DATE               10 // WORD  last update date
#define FILE_NAME               11 // WORD  12 byte buffer for filename
#define FILE_MODE               17 // WORD  file mode 'r', 'w', 'a'
#define FILE_ATTRIBUTES         18 // WORD  files attributes
#define FILE_PAGEFLAG           19 // WORD  cache check flag
#define FILE_ENTRY              20 // WORD  entry position in cur directory
#define FILE_DISK               21 // WORD* pointer to DISK mount media structure
#define FILE_BUFFER             22 // WORD*  sector buffer



// timer control  related constants
#define TIMER04d                0
#define TIMER14d                1
#define TIMER24d                2
#define TIMER34d                3
#define TIMER44d                4
#define TIMER54d                5
#define TIMER64d                6
#define TIMER74d                7

// I2C timing related constants
#define I2C_SLOW                0
#define I2C_MED                 1
#define I2C_FAST                2


// spi_Init(...)  mode arguments
#define SPI_SLOW                2 // 750khz
#define SPI_MED                 1 // 3mhz
#define SPI_FAST                0 // 12mhz
#define RXMODE_0                0 // receive sample pos
#define RXMODE_1                1 // receive sample pos
#define CKMODE_0                0 // transmit sample pos
#define CKMODE_1                1 // transmit sample pos
#define CKMODE_2                2 // transmit sample pos
#define CKMODE_3                3 // transmit sample pos

//------------------------------------------------------------------------------
// system WORD variables accesible with peekW and pokeW or pointer access
// Note that the txt_Set variables (0-15) and gfx_set variables (16-31)
// can also be accessed with peekW and pokeW
//------------------------------------------------------------------------------

#define RANDOM_LO               32 // random number generator LO word
#define RANDOM_HI               33 // random number generator LO word
#define SYSTEM_TIMER_LO         34 // 1msec 32 bit free running timer LO word
#define SYSTEM_TIMER_HI         35 // 1msec 32 bit free running timer HI word
#define TMR0                    36 // user timer0
#define TMR1                    37 // user timer1
#define TMR2                    38 // user timer2
#define TMR3                    39 // user timer3 (10msec resolution)
#define TMR4                    40 // user timer0
#define TMR5                    41 // user timer1
#define TMR6                    42 // user timer2
#define TMR7                    43 // user timer3 (10msec resolution)
#define SYS_X_MAX               44 // display hardware X res-1
#define SYS_Y_MAX               45 // display hardware Y res-1
#define GFX_XMAX                46 // current display width-1 determined by portrait / landscape swapping
#define GFX_YMAX                47 // current display width-1 determined by portrait / landscape swapping
#define GFX_LEFT                48 // virtual left point for most recent object
#define GFX_TOP                 49 // virtual top point for most recent object
#define GFX_RIGHT               50 // virtual right point for most recent object
#define GFX_BOTTOM              51 // virtual bottom point for most recent object
#define GFX_X1                  52 // clipped left point for current object
#define GFX_Y1                  53 // clipped top point for current object
#define GFX_X2                  54 // clipped right point for current object
#define GFX_Y2                  55 // clipped bottom point for current object
#define GFX_X_ORG               56 // current X origin
#define GFX_Y_ORG               57 // current Y origin
#define GFX_HILITE_LINE         58 // current multi line button hilite line
#define GFX_LINE_COUNT          59 // count of lines in multiline button
#define GFX_LAST_SELECTION      60 // last selected line
#define GFX_HILIGHT_BACKGROUND  61 // multi button hilite background colour
#define GFX_HILIGHT_FOREGROUND  62 // multi button hilite background colour
#define GFX_BUTTON_FOREGROUND   63 // store default text colour for hilite line tracker
#define GFX_BUTTON_BACKGROUND   64 // store default button colour for hilite line tracker
#define GFX_BUTTON_MODE         65 // store current buttons mode
#define GFX_TOOLBAR_HEIGHT      66 // height above
#define GFX_STATUSBAR_HEIGHT    67 // height below
#define GFX_LEFT_GUTTER_WIDTH   68 // width to left
#define GFX_RIGHT_GUTTER_WIDTH  69 // width to right
#define GFX_PIXEL_SHIFT         70 // pixel shift for button depress illusion (default 1)
#define GFX_RECT_X1             71 // gp rect, used by multiline button to hilite required line
#define GFX_RECT_Y1             72
#define GFX_RECT_X2             73
#define GFX_RECT_Y2             74
#define GFX_THUMB_PERCENT       75 // size of slider thumb as percentage
#define GFX_THUMB_BORDER_DARK   76 // darker shadow of thumb
#define GFX_THUMB_BORDER_LIGHT  77 // lighter shadow of thumb
#define TOUCH_XMINCAL           78 // touch calibration value
#define TOUCH_YMINCAL           79 // touch calibration value
#define TOUCH_XMAXCAL           80 // touch calibration value
#define TOUCH_YMAXCAL           81 // touch calibration value
#define IMG_WIDTH               82 // width of currently loaded image
#define IMG_HEIGHT              83 // height of currently loaded image
#define IMG_FRAME_DELAY         84 // 0 if image, else inter frame delay for movie
#define IMG_FLAGS               85 // bit 4 determines colour mode, other bits reserved
#define IMG_FRAME_COUNT         86 // count of frames in a movie
#define IMG_PIXEL_COUNT_LO      87 // count of pixels in the current frame
#define IMG_PIXEL_COUNT_HI      88 // count of pixels in the current frame
#define IMG_CURRENT_FRAME       89 // last frame shown
#define MEDIA_ADDRESS_LO        90 // uSD byte address LO
#define MEDIA_ADDRESS_HI        91 // uSD byte address HI
#define MEDIA_SECTOR_LO         92 // uSD sector address LO
#define MEDIA_SECTOR_HI         93 // uSD sector address HI
#define MEDIA_SECTOR_COUNT      94 // uSD number of bytes remaining in sector
#define TEXT_XPOS               95 // text current x pixel position
#define TEXT_YPOS               96 // text current y pixel position
#define TEXT_MARGIN             97 // text left pixel pos for carriage return
#define TXT_FONT_ID             98 // font type, 0 = system font, else pointer to user font
#define TXT_FONT_MAX            99 // max number of chars in font
#define TXT_FONT_OFFSET         100 // starting offset (normally 0x20)
#define TXT_FONT_WIDTH          101 // current font width
#define TXT_FONT_HEIGHT         102 // current font height
#define GFX_TOUCH_REGION_X1     103 // touch capture region
#define GFX_TOUCH_REGION_Y1     104
#define GFX_TOUCH_REGION_X2     105
#define GFX_TOUCH_REGION_Y2     106
#define GFX_CLIP_LEFT_VAL       107 // left clipping point (set with gfx_ClipWindow(...)
#define GFX_CLIP_TOP_VAL        108 // top clipping point (set with gfx_ClipWindow(...)
#define GFX_CLIP_RIGHT_VAL      109 // right clipping point (set with gfx_ClipWindow(...)
#define GFX_CLIP_BOTTOM_VAL     110 // bottom clipping point (set with gfx_ClipWindow(...)
#define GFX_CLIP_LEFT           111 // current clip value (reads full size if clipping turned off)
#define GFX_CLIP_TOP            112 // current clip value (reads full size if clipping turned off)
#define GFX_CLIP_RIGHT          113 // current clip value (reads full size if clipping turned off)
#define GFX_CLIP_BOTTOM         114 // current clip value (reads full size if clipping turned off)
#define GRAM_PIXEL_COUNT_LO     115 // LO word of count of pixels in the set GRAM area
#define GRAM_PIXEL_COUNT_HI     116 // HI word of count of pixels in the set GRAM area
#define TOUCH_RAW_X             117 // 12 bit raw A2D X value from touch screen
#define TOUCH_RAW_Y             118 // 12 bit raw A2D Y value from touch screen
#define GFX_LAST_CHAR_WIDTH     119 // calculated char width from last call to charWidth function
#define GFX_LAST_CHAR_HEIGHT    120 // calculated height from last call to charHeight function
#define GFX_LAST_STR_WIDTH      121 // calculated width from last call to strWidth function
#define GFX_LAST_STR_HEIGHT     122 // calculated height from last call to strHeight function

//------------------------------------------------------------------------------
// FILEIO Error Code Constants
//------------------------------------------------------------------------------
#define FE_OK                   0 // IDE function succeeded
#define FE_IDE_ERROR            1 // IDE command execution error
#define FE_NOT_PRESENT          2 // CARD not present
#define FE_PARTITION_TYPE       3 // WRONG partition type, not FAT16
#define FE_INVALID_MBR          4 // MBR sector invalid signature
#define FE_INVALID_BR           5 // Boot Record invalid signature
#define FE_DISK_NOT_MNTD        6 // Media not mounted
#define FE_FILE_NOT_FOUND       7 // File not found in open for read
#define FE_INVALID_FILE         8 // File not open
#define FE_FAT_EOF              9 // Fat attempt to read beyond EOF
#define FE_EOF                  10 // Reached the end of file
#define FE_INVALID_CLUSTER      11 // Invalid cluster value > maxcls
#define FE_DIR_FULL             12 // All root dir entry are taken
#define FE_DISK_FULL            13 // All clusters in partition are taken
#define FE_FILE_OVERWRITE       14 // A file with same name exist already
#define FE_CANNOT_INIT          15 // Cannot init the CARD
#define FE_CANNOT_READ_MBR      16 // Cannot read the MBR
#define FE_MALLOC_FAILED        17 // Malloc could not allocate the FILE struct
#define FE_INVALID_MODE         18 // Mode was not r.w.
#define FE_FIND_ERROR           19 // Failure during FILE search
#define FE_INVALID_FNAME        20 // bad filename
#define FE_INVALID_MEDIA        21 // bad media
#define FE_SECTOR_READ_FAIL     22 // sector read failed
#define FE_SECTOR_WRITE_FAIL    23 // sector write failed

/*
    16 bit RGB (565) Colour Chart
    Original work by 4D Forum Member: skadoo
*/



#define ALICEBLUE               0xF7DF
#define ANTIQUEWHITE            0xFF5A
#define AQUA                    0x07FF
#define AQUAMARINE              0x7FFA
#define AZURE                   0xF7FF
#define BEIGE                   0xF7BB
#define BISQUE                  0xFF38
#define BLACK                   0x0000
#define BLANCHEDALMOND          0xFF59
#define BLUE                    0x001F
#define BLUEVIOLET              0x895C
#define BROWN                   0xA145
#define BURLYWOOD               0xDDD0
#define CADETBLUE               0x5CF4
#define CHARTREUSE              0x7FE0
#define CHOCOLATE               0xD343
#define CORAL                   0xFBEA
#define CORNFLOWERBLUE          0x64BD
#define CORNSILK                0xFFDB
#define CRIMSON                 0xD8A7
#define CYAN                    0x07FF
#define DARKBLUE                0x0011
#define DARKCYAN                0x0451
#define DARKGOLDENROD           0xBC21
#define DARKGRAY                0xAD55
#define DARKGREEN               0x0320
#define DARKKHAKI               0xBDAD
#define DARKMAGENTA             0x8811
#define DARKOLIVEGREEN          0x5345
#define DARKORANGE              0xFC60
#define DARKORCHID              0x9999
#define DARKRED                 0x8800
#define DARKSALMON              0xECAF
#define DARKSEAGREEN            0x8DF1
#define DARKSLATEBLUE           0x49F1
#define DARKSLATEGRAY           0x2A69
#define DARKTURQUOISE           0x067A
#define DARKVIOLET              0x901A
#define DEEPPINK                0xF8B2
#define DEEPSKYBLUE             0x05FF
#define DIMGRAY                 0x6B4D
#define DODGERBLUE              0x1C9F
#define FIREBRICK               0xB104
#define FLORALWHITE             0xFFDE
#define FORESTGREEN             0x2444
#define FUCHSIA                 0xF81F
#define GAINSBORO               0xDEFB
#define GHOSTWHITE              0xFFDF
#define GOLD                    0xFEA0
#define GOLDENROD               0xDD24
#define GRAY                    0x8410
#define GREEN                   0x0400
#define GREENYELLOW             0xAFE5
#define HONEYDEW                0xF7FE
#define HOTPINK                 0xFB56
#define INDIANRED               0xCAEB
#define INDIGO                  0x4810
#define IVORY                   0xFFFE
#define KHAKI                   0xF731
#define LAVENDER                0xE73F
#define LAVENDERBLUSH           0xFF9E
#define LAWNGREEN               0x7FE0
#define LEMONCHIFFON            0xFFD9
#define LIGHTBLUE               0xAEDC
#define LIGHTCORAL              0xF410
#define LIGHTCYAN               0xE7FF
#define LIGHTGOLD               0xFFDA
#define LIGHTGREEN              0x9772
#define LIGHTGREY               0xD69A
#define LIGHTPINK               0xFDB8
#define LIGHTSALMON             0xFD0F
#define LIGHTSEAGREEN           0x2595
#define LIGHTSKYBLUE            0x867F
#define LIGHTSLATEGRAY          0x7453
#define LIGHTSTEELBLUE          0xB63B
#define LIGHTYELLOW             0xFFFC
#define LIME                    0x07E0
#define LIMEGREEN               0x3666
#define LINEN                   0xFF9C
#define MAGENTA                 0xF81F
#define MAROON                  0x8000
#define MEDIUMAQUAMARINE        0x6675
#define MEDIUMBLUE              0x0019
#define MEDIUMORCHID            0xBABA
#define MEDIUMPURPLE            0x939B
#define MEDIUMSEAGREEN          0x3D8E
#define MEDIUMSLATEBLUE         0x7B5D
#define MEDIUMSPRINGGREEN       0x07D3
#define MEDIUMTURQUOISE         0x4E99
#define MEDIUMVIOLETRED         0xC0B0
#define MIDNIGHTBLUE            0x18CE
#define MINTCREAM               0xF7FF
#define MISTYROSE               0xFF3C
#define MOCCASIN                0xFF36
#define NAVAJOWHITE             0xFEF5
#define NAVY                    0x0010
#define OLDLACE                 0xFFBC
#define OLIVE                   0x8400
#define OLIVEDRAB               0x6C64
#define ORANGE                  0xFD20
#define ORANGERED               0xFA20
#define ORCHID                  0xDB9A
#define PALEGOLDENROD           0xEF55
#define PALEGREEN               0x9FD3
#define PALETURQUOISE           0xAF7D
#define PALEVIOLETRED           0xDB92
#define PAPAYAWHIP              0xFF7A
#define PEACHPUFF               0xFED7
#define PERU                    0xCC27
#define PINK                    0xFE19
#define PLUM                    0xDD1B
#define POWDERBLUE              0xB71C
#define PURPLE                  0x8010
#define RED                     0xF800
#define ROSYBROWN               0xBC71
#define ROYALBLUE               0x435C
#define SADDLEBROWN             0x8A22
#define SALMON                  0xFC0E
#define SANDYBROWN              0xF52C
#define SEAGREEN                0x2C4A
#define SEASHELL                0xFFBD
#define SIENNA                  0xA285
#define SILVER                  0xC618
#define SKYBLUE                 0x867D
#define SLATEBLUE               0x6AD9
#define SLATEGRAY               0x7412
#define SNOW                    0xFFDF
#define SPRINGGREEN             0x07EF
#define STEELBLUE               0x4416
#define TAN                     0xD5B1
#define TEAL                    0x0410
#define THISTLE                 0xDDFB
#define TOMATO                  0xFB08
#define TURQUOISE               0x471A
#define VIOLET                  0xEC1D
#define WHEAT                   0xF6F6
#define WHITE                   0xFFFF
#define WHITESMOKE              0xF7BE
#define YELLOW                  0xFFE0
#define YELLOWGREEN             0x9E66

#define Err4D_OK 		0
#define Err4D_Timeout		1
#define Err4D_NAK		2 // other than ACK received

#define t4DWordArray 			word *
#define t4DByteArray 			char *
#define t4DSector 				char *

#define F_charheight 29
#define F_charwidth 30
#define F_bus_In -45
#define F_bus_Out -46
#define F_bus_Read -49
#define F_bus_Set -47
#define F_bus_Write -48
#define F_file_Close -232
#define F_file_Count 1
#define F_file_Dir 2
#define F_file_Erase 3
#define F_file_Error -225
#define F_file_Exec 4
#define F_file_Exists 5
#define F_file_FindFirst 6
#define F_file_FindNext -229
#define F_file_GetC -242
#define F_file_GetS 7
#define F_file_GetW -244
#define F_file_Image -239
#define F_file_Index -235
#define F_file_LoadFunction 8
#define F_file_LoadImageControl 9
#define F_file_Mount -253
#define F_file_Open 10
#define F_file_PlayWAV 11
#define F_file_PutC 31
#define F_file_PutS 32
#define F_file_PutW -243
#define F_file_Read 12
#define F_file_Rewind -248
#define F_file_Run 13
#define F_file_ScreenCapture -240
#define F_file_Seek -234
#define F_file_Size 14
#define F_file_Tell 15
#define F_file_Unmount -254
#define F_file_Write 16
#define F_gfx_BevelShadow -104
#define F_gfx_BevelWidth -103
#define F_gfx_BGcolour -92
#define F_gfx_Button 17
#define F_gfx_ChangeColour -76
#define F_gfx_Circle -61
#define F_gfx_CircleFilled -62
#define F_gfx_Clipping -94
#define F_gfx_ClipWindow -75
#define F_gfx_Cls -51
#define F_gfx_Contrast -100
#define F_gfx_Ellipse -78
#define F_gfx_EllipseFilled -79
#define F_gfx_FrameDelay -97
#define F_gfx_Get -90
#define F_gfx_GetPixel -64
#define F_gfx_Line -56
#define F_gfx_LinePattern -101
#define F_gfx_LineTo -54
#define F_gfx_MoveTo -52
#define F_gfx_Orbit 18
#define F_gfx_OutlineColour -99
#define F_gfx_Panel -81
//#define F_gfx_PenSize -91
#define F_gfx_Polygon 19
#define F_gfx_PolygonFilled 20
#define F_gfx_Polyline 21
#define F_gfx_PutPixel -63
#define F_gfx_Rectangle -59
#define F_gfx_RectangleFilled -60
#define F_gfx_ScreenCopyPaste -83
#define F_gfx_ScreenMode -98
#define F_gfx_Set -50
#define F_gfx_SetClipRegion -77
#define F_gfx_Slider -82
#define F_gfx_Transparency -96
#define F_gfx_TransparentColour -95
#define F_gfx_Triangle -65
#define F_gfx_TriangleFilled -87
#define F_img_ClearAttributes -187
#define F_img_Darken -181
#define F_img_Disable -180
#define F_img_Enable -179
#define F_img_GetWord -184
#define F_img_Lighten -182
#define F_img_SetAttributes -186
#define F_img_SetPosition -178
#define F_img_SetWord -183
#define F_img_Show -185
#define F_img_Touched -188
#define F_media_Flush -118
#define F_media_Image -117
#define F_media_Init -119
#define F_media_RdSector 22
#define F_media_ReadByte -113
#define F_media_ReadWord -114
#define F_media_SetAdd -109
#define F_media_SetSector -110
#define F_media_Video -107
#define F_media_VideoFrame -108
#define F_media_WriteByte -115
#define F_media_WriteWord -116
#define F_media_WrSector 23
#define F_mem_Free -220
#define F_mem_Heap -221
#define F_peekM 39
#define F_pin_HI -42
#define F_pin_LO -43
#define F_pin_Read -44
#define F_pin_Set -41
#define F_pokeM 40
#define F_putCH -2
#define F_putstr 24
#define F_snd_BufSize -258
#define F_snd_Continue -261
#define F_snd_Pause -260
#define F_snd_Pitch -257
#define F_snd_Playing -262
#define F_snd_Stop -259
#define F_snd_Volume -256
#define F_sys_Sleep -197
#define F_touch_DetectRegion -199
#define F_touch_Get -201
#define F_touch_Set -200
#define F_txt_Attributes -38
#define F_txt_BGcolour -26
#define F_txt_Bold -34
#define F_txt_FGcolour -25
#define F_txt_FontID -27
#define F_txt_Height -29
#define F_txt_Inverse -36
#define F_txt_Italic -35
#define F_txt_MoveCursor -23
#define F_txt_Opacity -33
#define F_txt_Set -24
#define F_txt_Underline -37
#define F_txt_Width -28
#define F_txt_Wrap -39
#define F_txt_Xgap -30
#define F_txt_Ygap -31
#define F_file_CallFunction 25
#define F_sys_GetModel 26
#define F_sys_GetVersion 27
#define F_sys_GetPmmC 28
#define F_writeString 33
#define F_readString 34
#define F_blitComtoDisplay 35
#define F_file_FindFirstRet 36
#define F_file_FindNextRet 37
#define F_setbaudWait 38