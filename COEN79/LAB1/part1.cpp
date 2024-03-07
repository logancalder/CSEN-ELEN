// Logan Calder, COEN79L TH 2:10
// Lab #1, Part #1

// part1.cpp asks user for input string using getline() & cin, then counts the alphanumeric
// characters within it utilizing isalnum(), if the char is ' ', and if neither, it is a special
// char. It then printf() the final count.

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstring>

#include "main.hpp"
using namespace std;

int main(int argc, const char *argv[])
{
    // Part 1: Counting Alphanumeric Characters & Non-Alphanumeric Characters

    string word;
    cout << "Enter a word: ";
    getline(cin, word); // Get user input, getline() to get a string & not just one word

    // Count int variables
    int alphCount = 0;
    int notAlphCount = 0;

    // For loop to iterate through user input
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == ' ') // Dont count spaces
        {
            continue;
        }
        if (isalnum(word[i])) // Count alphanumeric
        {
            alphCount++;
        }
        else // Must be special character, increase that
        {
            notAlphCount++;
        }
    }
    // Print the final tally of counts
    printf("That word had %d alphanumerics and %d non-alphanumerics\n", alphCount, notAlphCount);
}
