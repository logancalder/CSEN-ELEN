// Logan Calder, COEN79L TH 2:10
// Lab #1, Part #2

// part2.cpp obtains a user input, then replicates the provided pattern utilizing a string
// reversing function, reverseString(string s) defined in part2.cpp, and inserts specialized
// spacing between words utilizing for loop iteration.

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstring>

#include "main.hpp"
using namespace std;

int main(int argc, const char *argv[])
{
    // Obtain user input number as a string
    string numList;
    cout << "Enter a 10 digit number (no whitespace): ";
    getline(cin, numList);

    if (numList.length() > 10)
    {
        printf("That was not a 10 digit #. Please try again.");
        return 0;
    }

    int tester = stoi(numList);
    if (tester < 1000000000)
    {
        printf("That was not a 10 digit #. Please try again.");
        return 0;
    }

    cout << numList << "\n";

    int mult = 1;               // Initial offset of the pattern
    for (int i = 1; i < 5; i++) // For loop to increment tab of pattern
    {
        if (i > 1)
        {
            mult = 2; // For iterations of 2 or more, the spacing is wider
        }
        // Send the line
        cout << setw(i * mult) << " " << reverseString(numList) << setw(10 + i * 3) << " " << numList << "\n";
    }
    // Send final line, as it is  different
    cout << setw(10) << " " << reverseString(numList) << "\n";
}

// reverseString(string s) accepts a string s as parameter, and uses a backwards for loop to
// reverse and return the flipped string.
string reverseString(string s)
{
    string reversed = "";
    for (int i = s.length() - 1; i >= 0; i--) // Backwards iteration
    {
        reversed += s[i];
    }
    return reversed;
}