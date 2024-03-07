/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: HW#8, Persistance
 * 3 of 5: readback.cxx, main.cxx, printFreq.cxx, freq.h
 */
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "freq.h"

using namespace std;

namespace coen79
{

	void SaveFreq(const std::vector<Tuple> &freq, const std::string &fn)
	{
		// Open the file for writing
		std::ofstream outputFile(fn);

		// Check if the file is open
		if (!outputFile.is_open())
		{
			std::cerr << "Error opening file for writing: " << fn << std::endl;
			return;
		}

		// Write each Tuple to the file
		for (const auto &tuple : freq)
		{
			std::string displayLetter = (tuple.letter == '\n') ? "~" : std::string(1, tuple.letter);
			std::cout << displayLetter << ": " << tuple.freq << std::endl;
			outputFile << displayLetter << ": " << tuple.freq << std::endl;
		}

		// Close the file
		outputFile.close();
	}

}
