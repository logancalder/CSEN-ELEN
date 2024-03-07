/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: HW#8, Persistance
 * 4 of 5: savefreq.cxx, main.cxx, printFreq.cxx, freq.h
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "freq.h"

using namespace std;
using namespace coen79;

int main()
{
	// Read the frequency information
	ifstream inputFile("output.txt");

	if (!inputFile.is_open())
	{
		cerr << "Error opening file." << endl;
		return EXIT_FAILURE;
	}

	vector<Tuple> freq;

	string line;
	while (getline(inputFile, line))
	{
		// Split the line into character and frequency
		istringstream iss(line);
		string charStr, freqStr;

		if (iss >> charStr >> freqStr)
		{
			char character = charStr[0];
			double frequency = stod(freqStr);
			if (character == ':')
			{
				character = ' ';
			}

			// Create Tuple object and store it in the vector
			freq.push_back(Tuple(character, frequency));
		}
	}

	inputFile.close();

	// Print the characters and their frequencies
	for (auto x : freq)
		if (x.freq != 0.0)
		{
			cout << "Char: " << x.letter << ", Freq: " << x.freq << endl;
		}

	return EXIT_SUCCESS;
}
