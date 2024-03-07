/*
 * Name: Your Name
 * Email: Your email
 * Student ID: optional
 * Contact: Optional, your cell phone or whatever handle
 *
 * Assignment: What assignment is this file for.
 * x of y: if you have more than one file.  Say so here.
 */
#include <string>
#include <vector>
#include "freq.h"

namespace coen79
{
	bool compareTuples(const Tuple &t1, const Tuple &t2)
	{
		// Compare tuples based on frequency in descending order
		return t1.freq > t2.freq;
	}

	void AnalyzeFreq(const size_t *const counts, int len, std::vector<Tuple> &freq)
	{
		// Calculate total count of printable characters
		size_t totalCount = 0;
		for (int i = 0; i < len; ++i)
		{
			totalCount += counts[i];
		}

		// Calculate frequencies and store tuples
		for (int i = 0; i < len; ++i)
		{
			// Check if the character is printable or a newline character
			if (isprint(static_cast<char>(i)) || i == '\n' || i == ' ')
			{
				double frequency = static_cast<double>(counts[i]) / totalCount;
				freq.push_back(Tuple(static_cast<char>(i), frequency));
			}
		}

		// Sort the vector based on frequency
		std::sort(freq.begin(), freq.end(), compareTuples);
	}

}
