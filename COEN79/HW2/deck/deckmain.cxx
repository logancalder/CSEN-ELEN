/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: Homework #2
 * 2 of 4: Other files: shuffle.cxx, deck.h, deck.cxx
 */
#include <iomanip>
#include <iostream>
using namespace std;
#include "deck.h"
using namespace coen79_loganc;

int main(void)
{
	Deck deck; // Creating a deck in standard order

	// Deal every card individually
	for (int i = 0; i < deck.NCARDS; i++)
		cout << deck.deal() << endl;
	cout << deck.deal() << endl; // Print the deck ended line

	deck.shuffle(); // This shuffles the deck using Fisher-Yates

	cout << deck << endl
		 << endl
		 << "SHUFFLING ONCE AGAIN:" << endl; // Prints the entire deck at once

	// Now proving the deck is shuffled:

	cout << endl
		 << endl
		 << "Now shuffling a brand new deck to compare:";

	Deck deck2;
	deck2.shuffle();

	cout << deck2 << endl;

	return 0;
}
