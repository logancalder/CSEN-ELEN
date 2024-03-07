/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: Homework #2
 * 3 of 4: Other files: deckmain.cxx, deck.h, shuffle.cxx
 */
#include <iomanip>
#include <iostream>

using namespace std;
#include "deck.h"

namespace coen79_loganc
{
	static const Card NoCard; // No card obj

	// Precondition: Must be called on an instantiated Deck object
	// Returns the next card in deck, and increases current deck index by 1
	// If end of deck, returns the NoCard obj
	const Card &Deck::deal()
	{
		if (next >= NCARDS)
			return NoCard;
		return cards[next++];
	}

	// CONSTRUCTOR
	// Creates a deck to have the default order of cards (standard form)
	// Sets the next index to start at 0
	Deck::Deck() : next(0)
	{
		for (int i = 0; i < NCARDS; i++)
			cards[i] = Card(i / SUIT_LENGTH + 1, i % SUIT_LENGTH + 1);
	}

	// Checks if end of the deck has been reached, if not creates the proper lettering and
	// numbering for card.
	ostream &operator<<(ostream &os, const Card &c)
	{
		if (c.rank == NoCard.rank && c.suit == NoCard.suit)
			cout << "Bottom of Deck Reached";
		else
		{
			static char s[] = {'S', 'H', 'D', 'C'};
			cout << s[c.suit - 1] << ":";
			if (c.rank == 1)
				cout << 'A';
			else if (c.rank > 10)
			{
				static char honors[] = {'J', 'Q', 'K'};
				cout << honors[c.rank - 11];
			}
			else
				cout << c.rank;
		}
		return os;
	}

	// Couts the current deck index. Couts every card in deck.
	ostream &operator<<(ostream &os, const Deck &d)
	{
		cout << "Deck at " << d.next << endl;
		for (int i = 0; i < d.NCARDS; i++)
			cout << i << ": " << d.cards[i] << endl;
		return os;
	}
}
