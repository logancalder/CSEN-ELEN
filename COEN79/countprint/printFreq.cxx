/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: HW#8, Persistance
 * 2 of 5: savefreq.cxx, main.cxx, readback.cxx, freq.h
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

namespace coen79
{

	void printFreq(const vector<Tuple> &freq)
	{
		for (auto x : freq)
			cout << "Char: " << x.letter << ", Freq: " << x.freq << endl;
	}

}
