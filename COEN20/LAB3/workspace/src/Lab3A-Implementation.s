/*
Logan Calder
COEN20L T2:15
Lab #3
*/

/*
    This code was written to support the book, "ARM Assembly for Embedded Applications",
    by Daniel W. Lewis. Permission is granted to freely share this software provided
    that this notice is not removed. This software is intended to be used with a run-time
    library adapted by the author from the STM Cube Library for the 32F429IDISCOVERY 
    board and available for download from http://www.engr.scu.edu/~dlewis/book3.
*/
        .syntax         unified
        .cpu            cortex-m4
        .text

// int32_t Add(int32_t a, int32_t b) ;

        .global         Add
        .thumb_func
        .align
Add:
        ADD             R0,R0,R1 // Add register 0 to register 1 and store in register 0
        BX              LR

// int32_t Less1(int32_t a) ;

        .global         Less1
        .thumb_func
Less1:
        SUB             R0,R0,1 // Subtract 1 from register 0, store in register 0
        BX              LR

// int32_t Square2x(int32_t x) ;

        .global         Square2x
        .thumb_func
Square2x:
        LDR r1, =2  
        MUL             R0,R0,R1 // Multiply register 0 by 2 and store in register 0
        B               Square

// int32_t Last(int32_t x) ;

        .global         Last
        .thumb_func
Last:
        PUSH            {R4,LR} // Store register 4 in stack
        MOV             R4,R0 // Store register 0 in register 4
        BL              SquareRoot // Run sqrt on register 0
        ADD             R0,R4,R0 // Add register 0 to register 4 and store in register 0
        POP             {R4,PC} // Pop register 4's original value

        .end

