/*
 * Name: Your Name
 * Email: Your email
 * Student ID: optional
 * Contact: Optional, your cell phone or whatever handle
 *
 * Assignment: What assignment is this file for.
 * x of y: if you have more than one file.  Say so here.
 */
#include <climits>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "freq.h"

using namespace std;

namespace coen79
{
	void CountPrintable(const std::string &fn, size_t *counts)
	{
		// Initialize the counts array to zero
		for (int i = 0; i < 128; ++i)
		{
			counts[i] = 0;
		}

		// Open the file
		std::ifstream file(fn);

		// Check if the file is open
		if (!file.is_open())
		{
			std::cerr << "Error opening file: " << fn << std::endl;
			return;
		}

		// Read each character from the file
		char c;
		while (file.get(c))
		{
			// Increment the count for this character, including newline and space
			if (isprint(c) || c == '\n' || c == ' ')
			{
				++counts[static_cast<unsigned char>(c)];
			}
		}

		// Close the file
		file.close();
	}

}
