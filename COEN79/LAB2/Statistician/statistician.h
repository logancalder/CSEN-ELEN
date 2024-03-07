// Logan Calder, COEN79L TH 2:10
// Lab #2, .hpp File for Statistician

// FILE: statistician.h
// CLASS PROVIDED: statistician
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//   (a class to keep track of statistics on a sequence of real numbers)
//   This class is part of the namespace coen79_2C
//
// CONSTRUCTOR for the statistician class:
//   statistician( );
//     Postcondition: The object has been initialized, and is ready to accept
//     a sequence of numbers. Various statistics will be calculated about the
//     sequence.
//
// PUBLIC MODIFICATION member functions for the statistician class:
//   void next(double r)
//     The number r has been given to the statistician as the next number in
//     its sequence of numbers.
//   void reset( );
//     Postcondition: The statistician has been cleared, as if no numbers had
//     yet been given to it.
//
// PUBLIC CONSTANT member functions for the statistician class:
//   int length( ) const
//     Postcondition: The return value is the length of the sequence that has
//     been given to the statistician (i.e., the number of times that the
//     next(r) function has been activated).
//   double sum( ) const
//     Postcondition: The return value is the sum of all the numbers in the
//     statistician's sequence.
//   double mean( ) const
//     Precondition: length( ) > 0
//     Postcondition: The return value is the arithmetic mean (i.e., the
//     average of all the numbers in the statistician's sequence).
//   double minimum( ) const
//     Precondition: length( ) > 0
//     Postcondition: The return value is the tiniest number in the
//     statistician's sequence.
//   double maximum( ) const
//     Precondition: length( ) > 0
//     Postcondition: The return value is the largest number in the
//     statistician's sequence.
//
// NON-MEMBER functions for the statistician class:
//   statistician operator +(const statistician& s1, const statistician& s2)
//     Postcondition: The statistician that is returned contains all the
//     numbers of the sequences of s1 and s2.
//   statistician operator *(double scale, const statistician& s)
//     Postcondition: The statistician that is returned contains the same
//     numbers that s does, but each number has been multiplied by the
//     scale number.
//   bool operator ==(const statistician& s1, const statistician& s2)
//     Postcondition: The return value is true if s1 and s2 have the zero
//     length. Also, if the length is greater than zero, then s1 and s2 must
//     have the same length, the same  mean, the same minimum,
//     the same maximum, and the same sum.
//
// VALUE SEMANTICS for the statistician class:
// Assignments and the copy constructor may be used with statistician objects.

#ifndef STATS_H
#define STATS_H
namespace coen79_lab2
{
    // Statistician class declaration
    class statistician
    {
        // Public methods & friend methods
    public:
        statistician();
        statistician(int l, double s, double mi, double mx);

        void reset(void);
        int len(void) const;
        double sum(void) const;
        double minimum(void) const;
        double maximum(void) const;
        double mean(void) const;
        void next(double d);

        // Friend methods which may access private data of objects
        friend statistician operator+(const statistician &s1, const statistician &s2);
        friend statistician operator*(double scale, const statistician &s);

        // Private variable declaration
    private:
        int length;
        double sums;
        double mins;
        double maxs;
        double last;
    };

    bool operator==(const statistician &s1, const statistician &s2);
}
#endif