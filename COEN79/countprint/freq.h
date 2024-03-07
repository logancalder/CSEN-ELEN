/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: HW#8, Persistance
 * 5 of 5: savefreq.cxx, main.cxx, printFreq.cxx, readback.cxx
 */
#ifndef FREQH
#define FREQH

namespace coen79
{

	class Tuple
	{
	public:
		char letter; // printable character
		double freq; // its frequency

		Tuple(char l, double f) : letter(l), freq(f) {}
	};

	void AnalyzeFreq(const size_t *const counts, int len, std::vector<Tuple> &freq);
	void CountPrintable(const std::string &fn, size_t *counts);
	void SaveFreq(const std::vector<Tuple> &freq, const std::string &fn);
	void printFreq(const std::vector<Tuple> freq);
}

#endif // FREQH
