// Name: Logan Calder
// Date: 01/16/2025
// Title: Lab2 – Step 2
// Description: This program copies a file from a source file to a destination file using functions and syscalls.

#include <stdio.h>

#define RTT0 3
#define RTT1 20
#define RTT2 26
#define RTTHTTP 47
#define NUM_OBJECTS 6
#define NUM_CONNECTIONS 6

int main()
{
    // PART A
    int total_time_1 = RTT0 + RTT1 + RTT2 + RTTHTTP * 2;

    // PART B
    int total_time_2 = total_time_1 + NUM_OBJECTS * RTTHTTP * 2;

    // PART C
    int total_time_3 = total_time_1 + RTTHTTP * NUM_OBJECTS / NUM_CONNECTIONS;

    // PART D
    int total_time_4 = total_time_1 + RTTHTTP * 2 * NUM_OBJECTS / NUM_CONNECTIONS;

    printf("One Object: %d ms\n", total_time_1);
    printf("Non-Persistent 6 Objects: %d ms\n", total_time_2);
    printf("6 parallel connection - Persistent: %d ms\n", total_time_3);
    printf("6 parallel connection - Non-Persistent: %d ms\n", total_time_4);
    return 0;
}