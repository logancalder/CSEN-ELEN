/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: Homework #2
 * 4 of 4: Other files: deckmain.cxx, shuffle.cxx, deck.cxx
 */

#ifndef DECK_H
#define DECK_H

namespace coen79_loganc
{
	// Card definition
	// State your invariants
	class Card
	{
	public:
		int rank;
		int suit;
		Card() : rank(0), suit(0) {}
		Card(int s, int r) : rank(r), suit(s) {} // This line had a bug, using {} instead of ()

		friend ostream &operator<<(ostream &os, const Card &c);
	};

	// Deck definition
	// State your invariants
	class Deck
	{
	public:
		const size_t NCARDS = 52; // This line threw a bug unless setting flag -std=c++17
		Deck();
		const Card &deal();
		void shuffle(void);

		friend ostream &operator<<(ostream &os, const Deck &);

	private:
		const size_t SUIT_LENGTH = 13;
		Card cards[52];
		int next;
	};
}

#endif