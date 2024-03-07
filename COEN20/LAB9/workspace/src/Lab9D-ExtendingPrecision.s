/*
    This code was written to support the book,"ARM Assembly for Embedded Applications",
    by Daniel W. Lewis. Permission is granted to freely share this software provided
    that this notice is not removed. This software is intended to be used with a run-time
    library adapted by the author from the STM Cube Library for the 32F429IDISCOVERY 
    board and available for download from http://www.engr.scu.edu/~dlewis/book3.
*/
            .syntax         unified
            .cpu            cortex-m4
            .text

// -----------------------------------------------------------------------------------------
// FLOAT2 QuickTwoSum(float a32, float b32) ;
// -----------------------------------------------------------------------------------------
            .global         QuickTwoSum
            .thumb_func
            .align
QuickTwoSum:                        // S0 = a32, S1 = b32

            VADD.F32 S2,S0,S1       // S2 = s32 = a32 + b32
            VSUB.F32 S3,S2,S0       // S3 = s32 - a32
            VMOV.F32 S0,S2          // S0 = s32
            VSUB.F32 S1,S1,S3       // S1 = e32 = b32 - (s32 - a32)
            
            // return (FLOAT2) {s32, e32}

// -----------------------------------------------------------------------------------------
// FLOAT2 TwoSum(float a32, float b32) ;
// -----------------------------------------------------------------------------------------
            .global         TwoSum
            .thumb_func
            .align

@ s32 = a32 + b32;
@ v32 = s32 - a32;                         
@ e32 = (a32 - (s32 - v32)) + (b32 - v32); 

TwoSum:                             // S0 = a32, S1 = b32

            VMOV.F32 S2,S0          // S2 = a32
            VADD.F32 S0,S2,S1       // S0 = s32 = a32 + b32
            VSUB.F32 S3,S0,S2       // S3 = v32 = s32 - a32
            VSUB.F32 S4,S0,S3       // S4 = s32 - v32
            VSUB.F32 S1,S1,S3       // S1 = b32 - v32
            VSUB.F32 S2,S2,S4       // S2 = a32 - (s32 - v32)
            VADD.F32 S1,S2,S1       // S1 = e32 = (a32 - (s32 - v32)) + (b32 - v32)

            BX              LR      // return (FLOAT2) {s32, e32}

// -----------------------------------------------------------------------------------------
// FLOAT2 Split(float a32) ;
// -----------------------------------------------------------------------------------------
            .global         Split
            .thumb_func
            .align
Split:                          // S0 = a32
                                // R0 = &mpier

            LDR R0,=mpier
            VLDR.F32 S2,[R0]         // S2 = 4097.0
            
            VMUL.F32 S2,S0,S2   // S2 = p32 = 4097.0 * a32
            VMOV.F32 S1,S0      // S1 = a32
            VSUB.F32 S0,S2,S1   // S0 = p32 - a32
            VSUB.F32 S0,S2,S0   // S0 = ahi = p32 - (p32 - a32)
            VSUB.F32 S1,S1,S0   // S1 = alo = a32 - ahi

            BX              LR              // return (FLOAT2) {alo, ahi}

mpier:      .float          4097.0          // 4097 = 2^12 + 1

             .end

















