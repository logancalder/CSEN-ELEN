/*
 * Name: Your Name
 * Email: Your email
 * Student ID: optional
 * Contact: Optional, your cell phone or whatever handle
 *
 * Assignment: What assignment is this file for.
 * x of y: if you have more than one file.  Say so here.
 */
#include <iomanip>
#include <iostream>
#include <fstream>
#include "palindrome.h"

using namespace std;
using namespace coen79;

/*
 * Open a file expecting a string per line
 * If the string is a palindrome, print it out.
 * Reject lines with less than 3 characters
 *
 * Possible enhancement:
 * Read one word at a time and check palindrome for each word.
 */
int main(int argc, char *argv[]) {
	
	ifstream wordFile;
	wordFile.open("words.txt");
	string oneline;
	while (wordFile >> oneline) {
		if (oneline.length() >= 3 && isPalindrome(oneline))
			cout << oneline << endl;
	}
	return EXIT_SUCCESS;
}
