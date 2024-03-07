/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: HW#8, Persistance
 * 1 of 5: savefreq.cxx, readback.cxx, printFreq.cxx, freq.h
 */
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "freq.h"

using namespace std;
using namespace coen79;

int main(int argc, char *argv[])
{
	std::string fn;
	if (argc > 1)
		fn = argv[1];
	else
		cerr << "Need a file name" << endl;

	size_t counts[UCHAR_MAX + 1] = {0};
	vector<Tuple> freq;
	CountPrintable(fn, counts);
	AnalyzeFreq(counts, UCHAR_MAX + 1, freq); // Removed the & operator
	SaveFreq(freq, "output.txt");

	return EXIT_SUCCESS;
}
