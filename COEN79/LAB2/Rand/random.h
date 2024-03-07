// Logan Calder, COEN79L TH 2:10
// Lab #2, .hpp File for Rand

// FILE: rand_gen.h
// CLASS PROVIDED: rand_gen
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//   (a class to generate pseudorandom numbers)
//   This class is part of the namespace coen79_2C
//
// CONSTRUCTOR for the rand_gen class:
//   rand_gen( );
//     Postcondition: The object has been initialized, and is ready to generate pseudorandom numbers.
//
// PUBLIC MODIFICATION member functions for the rand_gen class:
//  void set_seed(int newSeed)
//    Postcondition: the number new_seed is the new seed
//  int next()
//    Postcondition: The return value is the next random integer, and the return value is set as the new seed
//
// PUBLIC CONSTANT member functions for the rand_gen class:
//  void print_info()
//    Postcondition: Prints the values of the private member variables

#ifndef RAND_NUM_GEN_H
#define RAND_NUM_GEN_H

namespace coen79_lab2
{
    // Class declaration for rand_gen
    class rand_gen
    {
        // Public functions & constructor
    public:
        rand_gen(int s, int x, int i, int m);
        int next(void);
        void set_seed(int s);
        void print_info();

        // Private data
    private:
        int seed;
        int mult;
        int inc;
        int mod;
    };
}

#endif
