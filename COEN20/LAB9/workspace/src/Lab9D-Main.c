/*
    This code was written to support the book, "ARM Assembly for Embedded Applications",
    by Daniel W. Lewis. Permission is granted to freely share this software provided
    that this notice is not removed. This software is intended to be used with a run-time
    library adapted by the author from the STM Cube Library for the 32F429IDISCOVERY
    board and available for download from http://www.engr.scu.edu/~dlewis/book3.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include "library.h"
#include "graphics.h"

typedef struct
{
    float x32; // The least-significant 32 bits (returned in S0)
    float y32; // The most-significant 32 bits (returned in S1)
} FLOAT2;

#pragma GCC push_options
#pragma GCC optimize("O0")

// ----------------------------------------------------------------------------
// Support routines for FLOAT2 arithmetic to be implemented in assembly
// ----------------------------------------------------------------------------
FLOAT2 __attribute__((weak)) QuickTwoSum(float a32, float b32)
{
    // assumes a32 > b32
    float s32, e32;

    s32 = a32 + b32;
    e32 = b32 - (s32 - a32); // This is NOT always zero!
    return (FLOAT2){s32, e32};
}

FLOAT2 __attribute__((weak)) TwoSum(float a32, float b32)
{
    float s32, v32, e32;

    s32 = a32 + b32;
    v32 = s32 - a32;                         // This is NOT the same as b32!
    e32 = (a32 - (s32 - v32)) + (b32 - v32); // This is NOT always zero!
    return (FLOAT2){s32, e32};
}

FLOAT2 __attribute__((weak)) Split(float a32)
{
    float p32, ahi32, alo32;

    p32 = 4097.0f * a32;
    ahi32 = p32 - (p32 - a32); // This is NOT the same as a32!
    alo32 = a32 - ahi32;
    return (FLOAT2){ahi32, alo32};
}

#pragma GCC pop_options

typedef struct
{
    int ytop;
    int xlft;
    double want;
    double sum;
    unsigned strt;
    unsigned stop;
    unsigned steps;
} RESULTS;

// Public fonts defined in run-time library
typedef struct
{
    const uint8_t *table;
    const uint16_t Width;
    const uint16_t Height;
} sFONT;

// Series approximations
static void SeriesFP32(void);
static void SeriesFLT2(void);
static void SeriesFP64(void);

// Basic arithmetic operations for double floats
static FLOAT2 Add64(FLOAT2 a64, FLOAT2 b64);
static FLOAT2 Sub64(FLOAT2 a64, FLOAT2 b64);
static FLOAT2 Mul64(FLOAT2 a64, FLOAT2 b64);
static FLOAT2 Div64(FLOAT2 a64, FLOAT2 b64);
static int EQ64(FLOAT2 a64, FLOAT2 b64);

// Additional support routine to implement Add64, Sub64, Mul64, & Div64
static FLOAT2 TwoProd(float a32, float b32);

// Other functions
static double Double(FLOAT2 a64);
static void Results(char *alg, char *type, RESULTS *results);
static void SetFontSize(sFONT *Font);
static int PutStringAt(int row, int col, char *fmt, ...);

// High-precision definitions of PI and e
#pragma GCC push_options
#pragma GCC optimize("no-single-precision-constant")
static const double __attribute__((unused)) PI = 3.1415926535897932384626433;
#pragma GCC pop_options

extern sFONT Font8, Font12, Font16, Font20, Font24;

#define LIMIT 500000

#define FONT_HEIGHT 12
#define FONT_WIDTH 7

#define RESULTS_FONT Font12
#define RESULTS_MARGIN 8
#define RESULTS_PADDING 4
#define RESULTS_WIDTH 220
#define RESULTS_HEIGHT (5 * FONT_HEIGHT + 2 * RESULTS_PADDING)

#define ITER_XLFT ((XPIXELS - RESULTS_WIDTH) / 2)
#define ITER_YTOP 55

#define COLOR_BKGD COLOR_YELLOW
#define COLOR_BRDR COLOR_RED
#define COLOR_TEXT COLOR_BLACK

#define FP32_YTOP (ITER_YTOP + FONT_HEIGHT + RESULTS_MARGIN)
#define FP32_XLFT ITER_XLFT

#define FLT2_YTOP (FP32_YTOP + RESULTS_HEIGHT + RESULTS_MARGIN)
#define FLT2_XLFT ITER_XLFT

#define FP64_YTOP (FLT2_YTOP + RESULTS_HEIGHT + RESULTS_MARGIN)
#define FP64_XLFT ITER_XLFT

int main()
{
    char text[100];

    InitializeHardware(HEADER, "Lab 9D: Extending Precision");

    SetFontSize(&Font12);
    sprintf(text, "Iteration Limit: %u", LIMIT);
    DisplayStringAt(ITER_XLFT, ITER_YTOP, text);

    SeriesFP32();
    SeriesFLT2();
    SeriesFP64();

    return 0;
}

// ----------------------------------------------------------------------------
// Series approximations to PI
// ----------------------------------------------------------------------------
static void SeriesFP32(void)
{
    static RESULTS results = {FP32_YTOP, FP32_XLFT};
    float sum, top, num, err;
    unsigned step;

    sum = 3.0f;
    top = 4.0f;
    num = 3.0f;
    err = 0.0f;

    results.want = PI;
    results.strt = GetClockCycleCount();
    for (step = 0; step < LIMIT; step++)
    {
        float btm = num * num * num - num; // same as (n-1)*n*(n+1)
        float y = top / btm - err;
        float tmp = sum + y;
        if (tmp == sum)
            break;
        err = (tmp - sum) - y; // This is NOT always zero!
        sum = tmp;
        top = -top;
        num += 2.0f;
    }
    results.stop = GetClockCycleCount();
    results.sum = (double)sum;
    results.steps = step;
    Results("Kahan", "float", &results);
}

static void SeriesFLT2(void)
{
    static RESULTS results = {FLT2_YTOP, FLT2_XLFT};
    FLOAT2 sum, top, num;
    unsigned step;

    sum = (FLOAT2){3.0f, 0.0f};
    top = (FLOAT2){4.0f, 0.0f};
    num = (FLOAT2){3.0f, 0.0f};

    results.want = PI;
    results.strt = GetClockCycleCount();
    for (step = 0; step < LIMIT; step++)
    {
        FLOAT2 btm = Sub64(Mul64(num, Mul64(num, num)), num); // same as (n-1)*n*(n+1)
        FLOAT2 tmp = Add64(sum, Div64(top, btm));             // This is NOT always zero!
        if (EQ64(tmp, sum))
            break;
        sum = tmp;
        top.x32 = -top.x32;
        num.x32 += 2.0f;
    }
    results.stop = GetClockCycleCount();
    results.sum = Double(sum);
    results.steps = step;
    Results("Normal", "FLOAT2", &results);
}

static void SeriesFP64(void)
{
    static RESULTS results = {FP64_YTOP, FP64_XLFT};
    double sum, top, num, err;
    unsigned step;

    sum = 3.0;
    top = 4.0;
    num = 3.0;
    err = 0.0;

    results.want = PI;
    results.strt = GetClockCycleCount();
    for (step = 0; step < LIMIT; step++)
    {
        double btm = num * num * num - num; // same as (n-1)*n*(n+1)
        double y = top / btm - err;
        double tmp = sum + y;
        if (tmp == sum)
            break;
        err = (tmp - sum) - y; // This is NOT always zero!
        sum = tmp;
        top = -top;
        num += 2.0f;
    }
    results.stop = GetClockCycleCount();
    results.sum = sum;
    results.steps = step;
    Results("Kahan", "double", &results);
}

// ----------------------------------------------------------------------------
// Basic arithmetic operations for double floats
// ----------------------------------------------------------------------------
static FLOAT2 Add64(FLOAT2 a64, FLOAT2 b64)
{
    FLOAT2 s64, t64;

    s64 = TwoSum(a64.x32, b64.x32);
    t64 = TwoSum(a64.y32, b64.y32);
    s64.y32 += t64.x32;
    s64 = QuickTwoSum(s64.x32, s64.y32);
    s64.y32 += t64.y32;
    return QuickTwoSum(s64.x32, s64.y32);
}

static FLOAT2 Sub64(FLOAT2 a64, FLOAT2 b64)
{
    b64.x32 = -b64.x32;
    b64.y32 = -b64.y32;
    return Add64(a64, b64);
}

static FLOAT2 Mul64(FLOAT2 a64, FLOAT2 b64)
{
    FLOAT2 p64;

    p64 = TwoProd(a64.x32, b64.x32);
    p64.y32 += a64.x32 * b64.y32;
    p64.y32 += a64.y32 * b64.x32;
    return QuickTwoSum(p64.x32, p64.y32);
}

static FLOAT2 Div64(FLOAT2 a64, FLOAT2 b64)
{
    FLOAT2 q64, e64;
    float i32, d32;

    i32 = 1.0f / b64.x32;
    q64 = (FLOAT2){a64.x32 * i32, 0.0f};
    d32 = Sub64(a64, Mul64(b64, q64)).x32;
    e64 = TwoProd(i32, d32);
    return Add64(q64, e64);
}

static int EQ64(FLOAT2 a64, FLOAT2 b64)
{
    return *((uint64_t *)&a64) == *((uint64_t *)&b64);
}

// ----------------------------------------------------------------------------
// Additional support routine to implement Add64, Sub64, Mul64, & Div64
// ----------------------------------------------------------------------------
static FLOAT2 TwoProd(float a32, float b32)
{
    FLOAT2 a64, b64;
    float p32, e32;

    p32 = a32 * b32;
    a64 = Split(a32);
    b64 = Split(b32);
    e32 = ((a64.x32 * b64.x32 - p32) + a64.x32 * b64.y32 + a64.y32 * b64.x32) + a64.y32 * b64.y32;
    return (FLOAT2){p32, e32};
}

// ----------------------------------------------------------------------------
// Other functions
// ----------------------------------------------------------------------------
static double Double(FLOAT2 a64)
{
    return (double)a64.x32 + (double)a64.y32;
}

static void Results(char *alg, char *type, RESULTS *results)
{
    double err = fabs(results->sum - results->want);
    char sum[20], ref[20];
    int row, col, k;

    SetForeground(COLOR_BKGD);
    FillRect(results->xlft, results->ytop, RESULTS_WIDTH, RESULTS_HEIGHT);
    SetForeground(COLOR_BRDR);
    DrawRect(results->xlft, results->ytop, RESULTS_WIDTH, RESULTS_HEIGHT);

    SetFontSize(&RESULTS_FONT);
    SetForeground(COLOR_TEXT);
    SetBackground(COLOR_BKGD);

    sprintf(sum, "%.16lf", results->sum);
    sprintf(ref, "%.16lf", results->want);
    for (k = 0; sum[k] != '\0'; k++)
    {
        if (sum[k] != ref[k])
            break;
    }

    row = results->ytop + RESULTS_PADDING;
    col = results->xlft + RESULTS_PADDING;
    row = PutStringAt(row, col, "%s summation using %s:", alg, type);
    PutStringAt(row, col, "sum = %s", sum);
    SetForeground(COLOR_BRDR);
    row = PutStringAt(row, col + (k + 6) * RESULTS_FONT.Width, sum + k);
    SetForeground(COLOR_TEXT);
    row = PutStringAt(row, col, "err = %.16lf", err);
    row = PutStringAt(row, col, "Iterations: %u (%s)", results->steps, (results->steps == LIMIT) ? "Limited" : "Converged");
    row = PutStringAt(row, col, "Clock cycles/iteration: %u", (results->stop - results->strt) / results->steps);
}

static int PutStringAt(int row, int col, char *fmt, ...)
{
    char text[100];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(text, fmt, ap);
    va_end(ap);
    DisplayStringAt(col, row, text);
    return row + FONT_HEIGHT;
}

static void SetFontSize(sFONT *Font)
{
    extern void BSP_LCD_SetFont(sFONT *);
    BSP_LCD_SetFont(Font);
}
