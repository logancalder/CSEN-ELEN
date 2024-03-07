// Logan Calder, COEN79 TTH 8:30
// Homework #1, Problem #8, Page 15 of Textbook
// setup_cout_fractions(int fraction_digits) provided by textbook, credit:
// Data Structures and other Objects using C++, by Michael Main, Walter Savitch, 4th Edition

#include <iostream> // Provides cout
#include <iomanip>  // Provides setw function for setting output width
#include <cstdlib>  // Provides EXIT_SUCCESS
#include <cassert>  // Provides assert function
#include "main.h"
using namespace std;

// Precondition: feet is greater than 0.0
// Return: Converted feet to meters value, double
double feet_to_meters(double feet)
{
    assert(feet > 0);
    return (feet * .3048);
}

// Provided by textbook, credit colorado.edu
// Precondition: fraction_digits is not negative.
// Postcondition: All double or float numbers printed to cout will now be
// rounded to the specified digits on the right of the decimal.
void setup_cout_fractions(int fraction_digits)
{
    assert(fraction_digits > 0);
    cout.precision(fraction_digits);
    cout.setf(ios::fixed, ios::floatfield);
    if (fraction_digits == 0)
        cout.unsetf(ios::showpoint);
    else
        cout.setf(ios::showpoint);
}