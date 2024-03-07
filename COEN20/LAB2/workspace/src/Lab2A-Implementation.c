// Logan Calder
// COEN20L T 2:15
// LAB #2 Implementation

// Description \/\/\/\/\/

/*
    This code was written to support the book, "ARM Assembly for Embedded Applications",
    by Daniel W. Lewis. Permission is granted to freely share this software provided
    that this notice is not removed. This software is intended to be used with a run-time
    library adapted by the author from the STM Cube Library for the 32F429IDISCOVERY
    board and available for download from http://www.engr.scu.edu/~dlewis/book3.
*/

#include <stdint.h>

// Convert bits to unsigned int
uint32_t Bits2Unsigned(int8_t bits[8])
{
    uint32_t n = 0;
    for (int i = 7; i >= 0; i--) // Parse through each bit
    {
        n = 2 * n + bits[i]; // Convert this to a number by adding it to current total*2
    }

    return n;
}

// Convert bits to signed int
int32_t Bits2Signed(int8_t bits[8])
{
    int32_t unsigned_val = Bits2Unsigned(bits); // Obtain the unsigned number from bits
    if (unsigned_val > 127)                     // Since signed will have a range of 126, we can take away 256 if this number is exceeded
    {
        unsigned_val = unsigned_val - 256; // Converts to signed
    }
    return unsigned_val;
}

// Increment bit string by 1
void Increment(int8_t bits[8])
{
    for (int i = 0; i < 8; i++) // Parse through bits
    {
        if (bits[i] == 0) // If its a 0, we swap to a 1 and terminate
        {
            bits[i] = 1;
            return;
        }
        else
        {
            bits[i] = 0; // If 1, swap to 0 and continue, because will carry over
        }
    }
    return;
}

// Convert unsigned to bits
void Unsigned2Bits(uint32_t n, int8_t bits[8])
{
    int rem = 0;

    for (int i = 0; i < 8; i++) // Loop through each of 8 bits, starting at left
    {
        rem = n % 2;   // Obtain a 0 or 1 by using mod 2
        n /= 2;        // Half the number, then repeat
        bits[i] = rem; // Store the 0 or 1
    }
    return;
}
