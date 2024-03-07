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

// uint64_t TireDiam(uint32_t W, uint32_t A, uint32_t R) ;

        .global     TireDiam
        .thumb_func

        .align
TireDiam:                       // R0 = W, R1 = A, R2 = R

        MUL R0,R1,R0           	// R0 = AxW
        
        LDR R3,=1270
        UDIV R1,R0,R3           // R1 = (AxW)/1270

        MLS R0,R3,R1,R0         // R0 = (AxW)%1270

        ADD R1,R2,R1            // R1 = R + (AxW)/1270
        BX          LR

// uint64_t TireCirc(uint32_t W, uint32_t A, uint32_t R) ;

        .global     TireCirc
        .thumb_func

        .align
TireCirc:                               // R0 = W, R1 = A, R2 = R
        PUSH        {LR}
        BL          TireDiam            // R1 = R + (A*W)/1270, R0 = (A*W) % 1270
        
        LDR R3,=4987290                 // R1 = 4987290*(R + (A*W)/1270)
        MUL R1,R1,R3

        LDR R3,=3927                    // numerator (R0) = 3927*((A*W) % 1270) + 4987290*(R + (A*W)/1270)
        MUL R0,R0,R3         		  
        ADD R0,R1,R0

        LDR R3,=1587500                 // circumference[1] (R1) = numerator / 1587500
        UDIV R1,R0,R3                   // circumference[0] (R0) = numerator % 1587500
        MLS R0,R3,R1,R0
                  		 
        POP         {PC}

        .end
