// Logan Calder, COEN79L TH 2:10
// Lab #2, Pseudorandom Number Generator

// random.cpp contains the private class function declarations for rand_gen, including next()
// (finds the next number & updates seed), set_seet(int s) which updates the seed, and print_info()
// which displays the numbers in an orderly fashion. The constructor accepts 4 parameters
// for the seed creation.

#include <cassert>
#include <iostream>
#include "random.h"
using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2
{
    // rand_gen constructor
    // Precondition: Parameters MUST be input in the order of: seed, multiplier, increment, mod
    // Initializes the values of the rand_gen object
    rand_gen::rand_gen(int s, int x, int i, int m)
    {
        seed = s;
        mult = x;
        inc = i;
        mod = m;
    }

    // Obtains the next number in sequence using formula, then stores the number into seed.
    // Returns: New number in sequence (updated seed)
    int rand_gen::next()
    {
        int s = (mult * seed + inc) % mod;
        seed = s;
        return s;
    }

    // Updates the private seed variable in rand_gen object
    // Precondition: Parameter must be an inteter
    void rand_gen::set_seed(int s)
    {
        seed = s;
    }

    // Prints the current seed, multiplier, increment, and mod to console, each on a new line.
    void rand_gen::print_info()
    {
        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << mult << endl;
        cout << "Increment: " << inc << endl;
        cout << "Modulus: " << mod << endl;
    }
}