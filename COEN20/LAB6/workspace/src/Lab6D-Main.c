/*
    This code was written to support the book, "ARM Assembly for Embedded Applications",
    by Daniel W. Lewis. Permission is granted to freely share this software provided
    that this notice is not removed. This software is intended to be used with a run-time
    library adapted by the author from the STM Cube Library for the 32F429IDISCOVERY 
    board and available for download from http://www.engr.scu.edu/~dlewis/book3.
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include "library.h"
#include "graphics.h"

#pragma GCC push_options
#pragma GCC optimize ("O0")

// Function defined here and called from assembly
void                    Move1Disk(int fm, int to) ;

// Function to be implemented in assembly
void __attribute__((weak)) Hanoi(int num, int fm, int to, int aux)
    {
    if (num > 1) Hanoi(num - 1, fm, aux, to) ;
    Move1Disk(fm, to) ;
    if (num > 1) Hanoi(num - 1, aux, to, fm) ;
    }

#pragma GCC pop_options

#define DISK_NUM        10
#define DISK_THICKNESS  15
#define DISK_SPACING    80
#define DISK_XOFFSET    2
#define DISK_YOFFSET    225
#define DISK_MSEC       20

#define LBL_YPOS        (DISK_YOFFSET + 10)
#define MSG_YPOS        (LBL_YPOS + 30)

#define FONT_LBL        Font16
#define FONT_MOVE       Font12
#define FONT_START      Font20
#define FONT_FINI       Font20
#define FONT_ERR        Font12

#define ERR_BGND_COLOR  COLOR_RED
#define ERR_FGND_COLOR  COLOR_WHITE
#define ERR_BRDR_COLOR  COLOR_BLACK

typedef enum {FALSE = 0, TRUE = 1} BOOL ;

typedef struct
    {
    unsigned            count ;
    unsigned            diams[DISK_NUM] ;
    } STACK ;

// Public fonts defined in run-time library
typedef struct
    {
    const uint8_t *     table ;
    const uint16_t      Width ;
    const uint16_t      Height ;
    } sFONT ;

extern sFONT Font8, Font12, Font16, Font20, Font24 ;

// Functions local to this file
static void             Add(int to, int diam) ;
static void             Delay(uint32_t msec) ;
static void             DisplayMessage(sFONT *newFont, char *format, ...) ;
static void             Error(char *function, char *problem) ;
static uint32_t         GetTimeout(uint32_t msec) ;
static void             LEDs(int grn_on, int red_on) ;
static void             PutStringAt(uint32_t x, uint32_t y, char *format, ...) ;
static void             SetFontSize(sFONT *pFont) ;
static int              Sub(int fm) ;

static STACK            disks[3] ;
static BOOL             step = FALSE ;
static uint32_t         colors[DISK_NUM] =
    {
    COLOR_BLUE,         COLOR_GREEN,        COLOR_RED,          COLOR_CYAN,         COLOR_MAGENTA,
    COLOR_YELLOW,       COLOR_LIGHTRED,     COLOR_DARKYELLOW,   COLOR_DARKCYAN,     COLOR_ORANGE
    } ;

int main()
    {
    int k ;

    InitializeHardware(NULL, "Lab 6D: Towers of Hanoi") ;
    LEDs(1, 0) ;

    SetColor(COLOR_BLACK) ;
    DrawHLine(0, DISK_YOFFSET, 240) ;
    for (k = 0; k < 3; k++)
        {
        int xpos = DISK_XOFFSET + DISK_SPACING/2 + DISK_SPACING*k - 2 ;
        int ypos = DISK_YOFFSET - DISK_THICKNESS*DISK_NUM ;
        FillRect(xpos, ypos, 4, DISK_THICKNESS*DISK_NUM) ;
        }

    for (k = 0; k < DISK_NUM; k++)
        {
        Add(0, DISK_NUM - k) ;
        }

    SetFontSize(&FONT_LBL) ;
    for (k = 0; k < 3; k++)
        {
        int xpos = DISK_XOFFSET + DISK_SPACING/2 + DISK_SPACING*k - FONT_LBL.Width/2 ;
        DisplayChar(xpos, LBL_YPOS, '1' + k) ;
        }

    for (k = 3; k > 0; k--)
        {
        uint32_t timeout = GetTimeout(1000) ;
        DisplayMessage(&FONT_START, "Starting in %d", k) ;
        while ((int) (timeout - GetTimeout(0)) > 0)
            {
            if (PushButtonPressed()) step = TRUE ;
            }
        }

    Hanoi(DISK_NUM, 0, 1, 2) ;
    DisplayMessage(&FONT_FINI, "Finished!") ;
    return 0 ;
    }

void Move1Disk(int fm, int to)
    {
    int diam ;

    if (fm < 0 || fm > 2) Error("Move1Disk", "fm < 0 or > 2") ;
    if (to < 0 || to > 2) Error("Move1Disk", "to < 0 or > 2") ;

    DisplayMessage(&FONT_MOVE, "Move from %d to %d", fm + 1, to + 1) ;

    if (PushButtonPressed()) step = TRUE ;
    if (step) WaitForPushButton() ;
    else Delay(DISK_MSEC) ;

    diam = Sub(fm) ;
    Add(to, diam) ;
    }

static int Sub(int fm)
    {
    int disk = --disks[fm].count ;
    int diam = disks[fm].diams[disk] ;
    int xpos = DISK_XOFFSET + DISK_SPACING/2 + DISK_SPACING*fm - 4*diam ;
    int ypos = DISK_YOFFSET - DISK_THICKNESS*(disk + 1) ;
    SetColor(COLOR_WHITE) ;
    FillRect(xpos, ypos, 8*diam + 1, DISK_THICKNESS) ;
    SetColor(COLOR_BLACK) ;
    xpos = DISK_XOFFSET + DISK_SPACING/2 + DISK_SPACING*fm - 2 ;
    FillRect(xpos, ypos, 4, DISK_THICKNESS) ;
    return diam ;
    }

static void Add(int to, int diam)
    {
    int disk = disks[to].count++ ;
    int xpos = DISK_XOFFSET + DISK_SPACING/2 + DISK_SPACING*to - 4*diam ;
    int ypos = DISK_YOFFSET - DISK_THICKNESS*(disk + 1) ;
    SetColor(colors[diam - 1]) ;
    FillRect(xpos, ypos, 8*diam, DISK_THICKNESS) ;
    SetColor(COLOR_BLACK) ;
    DrawRect(xpos, ypos, 8*diam, DISK_THICKNESS - 1) ;
    disks[to].diams[disk] = diam ;
    }

static uint32_t GetTimeout(uint32_t msec)
    {
#   define CPU_CLOCK_SPEED_MHZ 168
    uint32_t cycles = 1000 * msec * CPU_CLOCK_SPEED_MHZ ;
    return GetClockCycleCount() + cycles ;
    }

static void Delay(uint32_t msec)
    {
    uint32_t timeout = GetTimeout(msec) ;
    while ((int) (timeout - GetClockCycleCount()) > 0) ;
    }

static void DisplayMessage(sFONT *newFont, char *format, ...)
    {
    static char prev[100] = "" ;
    static sFONT *oldFont = NULL ;
    va_list args ;
    char text[100] ;
    int x ;

    if (oldFont != NULL)
        {
        SetColor(COLOR_WHITE) ;
        SetFontSize(oldFont) ;
        x = (XPIXELS - oldFont->Width*strlen(prev))/2 ;
        DisplayStringAt(x, MSG_YPOS, prev) ;
        }

    va_start(args, format) ;
    vsprintf(text, format, args) ;
    va_end(args) ;

    SetColor(COLOR_BLACK) ;
    SetFontSize(newFont) ;
    x = (XPIXELS - newFont->Width*strlen(text))/2 ;
    DisplayStringAt(x, MSG_YPOS, text) ;
    strcpy(prev, text) ;

    oldFont = newFont ;
    }

static void SetFontSize(sFONT *Font)
    {
    extern void BSP_LCD_SetFont(sFONT *) ;
    BSP_LCD_SetFont(Font) ;
    }

static void LEDs(int grn_on, int red_on)
    {
    static uint32_t * const pGPIOG_MODER    = (uint32_t *) 0x40021800 ;
    static uint32_t * const pGPIOG_ODR      = (uint32_t *) 0x40021814 ;
    
    *pGPIOG_MODER |= (1 << 28) | (1 << 26) ;    // output mode
    *pGPIOG_ODR &= ~(3 << 13) ;         // both off
    *pGPIOG_ODR |= (grn_on ? 1 : 0) << 13 ;
    *pGPIOG_ODR |= (red_on ? 1 : 0) << 14 ;
    }

static void Error(char *function, char *problem)
    {
#   define  GFXROW1 54
#   define  GFXROWN 215
#   define  GFXROWS (GFXROWN - GFXROW1 + 1)
    uint32_t width, row, col, chars ;

    chars = strlen("Error: ") + strlen(function) ;
    width = FONT_ERR.Width * (chars + 2) ;
    col = (XPIXELS - width) / 2 ;
    row = GFXROW1 + GFXROWS / 2 ;

    SetFontSize(&FONT_ERR) ;
    SetColor(ERR_BGND_COLOR) ;
    FillRect(col + 1, row, width - 1, 3*FONT_ERR.Height) ;
    SetColor(ERR_BRDR_COLOR) ;
    DrawRect(col, row, width, 3*FONT_ERR.Height) ;
    row += FONT_ERR.Height/2 ;

    SetForeground(ERR_FGND_COLOR) ;
    SetBackground(ERR_BGND_COLOR) ;
    PutStringAt(col + FONT_ERR.Width, row, "Error: %s", function) ;
    row += FONT_ERR.Height ;
    PutStringAt(col + FONT_ERR.Width, row, problem) ;

    LEDs(0, 1) ;
    for (;;) ;
    }

static void PutStringAt(uint32_t x, uint32_t y, char *format, ...)
    {
    va_list args ;
    char text[100] ;

    va_start(args, format) ;
    vsprintf(text, format, args) ;
    va_end(args) ;

    DisplayStringAt(x, y, text) ;
    }



