// Logan Calder, COEN79 TTH 8:30
// Homework #1, Problem #8, Page 15 of Textbook
// Majority of main code provided by textbook, credit:
// Data Structures and other Objects using C++, by Michael Main, Walter Savitch, 4th Edition

// main.h provides definitions for feet_to_meters() & setup_cout_fractions()
// main.cxx provides table display, as well as table information display in console
// utility.cxx provides implementation of main.h functions, as well as preconditions for those
// functions.

#include <iostream> // Provides cout
#include <iomanip>  // Provides setw function for setting output width
#include <cstdlib>  // Provides EXIT_SUCCESS
#include <cassert>  // Provides assert function
#include "main.h"
using namespace std;

int main(int argc, const char *argv[])
{
    const char HEADING1[] = "   Feet"; // Heading for table's 1st column
    const char HEADING2[] = "Meters";  // Heading for table's 2nd column
    const char LABEL1[] = "ft";        // Label for numbers in 1st column
    const char LABEL2 = 'm';           // Label for numbers in 2nd column
    const double TABLE_BEGIN = 1.0;    // The table's first Celsius temp.
    const double TABLE_END = 50.0;     // The table's final Celsius temp.
    const double TABLE_STEP = 10.0;    // Increment between temperatures
    const int WIDTH = 9;               // Number chars in output numbers
    const int DIGITS = 1;              // Number digits right of decimal pt

    double value1; // A value from the table's first column
    double value2; // A value from the table's second column

    // Set up the output for fractions and print the table headings.
    setup_cout_fractions(DIGITS);
    cout << "CONVERSIONS from " << TABLE_BEGIN << " to " << TABLE_END << endl;
    cout << HEADING1 << "  " << HEADING2 << endl;

    // Each iteration of the loop prints one line of the table.
    for (value1 = TABLE_BEGIN; value1 <= TABLE_END; value1 += TABLE_STEP)
    {
        value2 = feet_to_meters(value1);
        cout << setw(WIDTH) << value1 << LABEL1 << "  ";
        cout << setw(WIDTH) << value2 << LABEL2 << endl;
    }

    return EXIT_SUCCESS;
}