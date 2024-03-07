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

// void Hanoi(int num, int fm, int to, int aux) ;

        .global     Hanoi
        .thumb_func
        .align

Hanoi:  PUSH        {R4-R7,LR}
        MOV R4,R0 // R4 = num
        MOV R5,R1 // R5 = fm
        MOV R6,R2 // R6 = to
        MOV R7,R3  // R7 = aux
        
        CMP R4,1

        BLE         Hanoi1 // if <=1 do this , otherwise do hanoi

        SUB R0,R4,1
        MOV R1,R5
        MOV R2,R7
        MOV R3,R6
        BL          Hanoi        // Yes --> Hanoi(num - 1, fm, aux, to)
Hanoi1: //
        MOV R0,R5
        MOV R1,R6

        BL          Move1Disk    // Move1Disk(fm, to)

        CMP R4,1
        
        BLE         Hanoi2 // if <=1 do this, otherwise do hanoi
        
        SUB R0,R4,1
        MOV R1,R7
        MOV R2,R6
        MOV R3,R5

        BL          Hanoi        // Yes --> Hanoi(num - 1, aux, to, fm)

Hanoi2: POP         {R4-R7,PC}

        .end


