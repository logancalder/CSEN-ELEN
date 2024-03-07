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

// uint32_t Time2Msecs(uint32_t hour, uint32_t mins, uint32_t secs) ;

        .global     Time2Msecs
        .thumb_func

        .align
Time2Msecs:
        // R0 = hour
        // R1 = mins
        // R2 = secs

        //
        // R3 = 60*hour
        LSL   R3, R0, #6      // R3 = hour << 6 (hour * 64)
        SUB   R3, R3, R0, LSL #2
        // R3 = 60*hour + mins
        ADD R3,R3,R1
        //

        // R0 = 60*(60*hour+mins)
        LSL   R0, R3, #6      
        SUB   R0, R0, R3, LSL #2
        // R0 = 60*(60*hour+mins)+secs
        ADD R0,R2,R0

        // R0 = 1000*(secs+60*(mins+60*hours))
        LSL   R1, R0, #10      // * 1024
        SUB   R1, R1, R0, LSL #5 // - 32 
        ADD   R0, R1, R0, LSL #3 // + 8

        BX          LR                          // return

// void Msecs2Time(uint32_t msec, uint32_t *hour, uint32_t *mins, uint32_t *secs) ;

        .global     Msecs2Time
        .thumb_func

    .align
Msecs2Time:

        // R0 = msec
        // R1 = ptr to hour
        // R2 = ptr to mins
        // R3 = ptr to secs

        PUSH        {R4,LR}

        // R0 (s) = msec / 1000
        LDR R12,=274877907
        UMULL R12,R0,R12,R0
        LSRS R0,R0,6

        // R4 (h) = s/3600
        LDR R12,=2443359173
        UMULL R12,R4,R12,R0
        LSRS R4,R4,11 // ?

        // *hour <-- R4
        STR R4,[R1] // ?

        // R0 (s) = s - 3600*h
        LDR R12,=3600
        MLS   R0,R12,R4,R0 

        // R4 (m) = s/60
        LDR R12,=2290649225
        UMULL R12,R4,R12,R0
        LSRS R4,R4,5
        // *mins <-- R4
        STR R4,[R2]

        // *secs = s - 60*m
        LDR R12,=60
        MLS R0,R12,R4,R0 
        STR R0,[R3]

        POP         {R4,PC}                     // return

        .end

 





















