/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 * Contact: 4085946314
 *
 * Assignment: Homework #2
 * 1 of 4: Other files: deckmain.cxx, deck.h, deck.cxx
 */
#include <iomanip>
#include <iostream>
#include <cstdlib>

using namespace std;
#include "deck.h"

namespace coen79_loganc
{
	// Precondition: Must be called on an already instantiated Deck object
	// Uses Fisher-Yates Algorithim to randomly shuffle deck object
	void Deck::shuffle(void)
	{
		// Variable declarations
		int randint;
		Card temp;

		// Loop through every card starting from end to start
		for (int i = 51; i >= 0; i--)
		{
			randint = rand() % (i + 1); // Random int in range of 0-i
										// Note: I don't use srand so that the same sequence of random shuffling doesn't
										// occur again. By calling rand, it is different each time.

			if (i != randint) // If the two indexes don't match, we swap them
			{
				temp = this->cards[i];
				this->cards[i] = this->cards[randint];
				this->cards[randint] = temp;
			}
		}
	}
}
