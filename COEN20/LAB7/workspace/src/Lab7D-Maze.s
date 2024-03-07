/*
    This code was written to support the book, "ARM Assembly for Embedded Applications",
    by Daniel W. Lewis. Permission is granted to freely share this software provided
    that this notice is not removed. This software is intended to be used with a run-time
    library adapted by the author from the STM Cube Library for the 32F429IDISCOVERY 
    board and available for download from http://www.engr.scu.edu/~dlewis/book3.
*/
        .syntax     unified
        .cpu        cortex-m4
        .text

// void PutNibble(void *nibbles, uint32_t index, uint32_t nibble) ;

        .global     PutNibble
        .thumb_func
        .align

PutNibble:
        // R1 = byte offset; C = which (0 or 1)
        // R0 = byte containing nibble
        PUSH {R4,LR} // Store R4 in stack
        LSR R4,R1,1
        LDRB R3,[R0,R4]
        AND R1,R1,1 // If even/odd
        CMP R1,1

        ITE EQ // IT Block to run line 46 if so
        BFIEQ R3,R2,#4,#4 // Insert 4 bits at 4 if equal
        BFINE R3,R2,#0,#4 // Else insert 4 bits at 0

        STRB R3,[R0,R4]
        POP {R4,PC} // Retrieve r4
        BX          LR

// uint32_t GetNibble(void *nibbles, uint32_t index) ;

        .global     GetNibble
        .thumb_func
        .align

GetNibble:
        // R1 = byte offset; C = which (0 or 1)
        // Rx = byte containing nibble

        LSR R2,R1,1
        LDRB R2,[R0,R2] // Address shift
        AND R1,R1,1 // If even/odd
        CMP R1,1

        // Shift byte right by 4 bits if
        // need most-significant nibble
        // strip other bits

        ITE EQ
        UBFXEQ R0,R2,#4,#4 // Insert 4 bits at 4 if equal
        UBFXNE R0,R2,#0,#4 // Else insert 4 bits at 0

        BX LR

        .end
        