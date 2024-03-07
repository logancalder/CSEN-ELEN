// Logan Calder, COEN79L TH 2:10
// Lab #1, Part #3

// part3.cpp accepts a text file as a parameter when the file is run, then iterates through each
// word in the file, checking if it has 10+ letters. If it does, it capitalizes the word, then
// displays the word to console.

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstring>

#include "main.hpp"
using namespace std;

int main(int argc, const char *argv[])
{
    // Precondition: argv[] is not null
    // Fetch the provided file given in argv[] array (we only need first one, so we use index 1)
    ifstream input_file;
    input_file.open(argv[1]);

    string filestring;
    string finalstring;

    // If we have opened a file:
    if (input_file.is_open())
    {
        while (input_file.good()) // While not at EOF
        {
            input_file >> filestring; // Pipeline the input file word into dummy hold var
            for (int i = filestring.length() - 1; i >= 0; i--)
            {
                if (!(isalnum(filestring[i])))
                {
                    filestring.erase(i, 1);
                }
            }
            if (filestring.length() >= 10) // If the word length is greater than or = 10:
            {
                // Capitalize word, then insert it into final string of 10+ letter words
                string holdstring = "";
                for (int i = 0; i < filestring.length(); i++)
                {
                    holdstring += toupper(filestring[i]);
                }
                holdstring += "\n";
                finalstring += holdstring;
            }
        }
    }

    cout << finalstring; // Display the final list of capitalized 10+ letter words
}