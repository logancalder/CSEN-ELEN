// Logan Calder, COEN79L TH 2:10
// Lab #2, Statistician

// statistician.cpp contains the constructor for a statistician (either empty, which creates
// a statistician object of default values, or with parameters that are entered accordingly).
// Contains reset(), which returns private values to default values, len(), which returns
// length. sum(), minimum(), maximum() all return their respective values. mean() calculates
// the mean and returns it. next(double d) updates private data accordingly.

// The file also contains operator overrides that may be used to add, multiply, and test the
// equality of objects.

#include <cassert>
#include <iostream>
#include "statistician.h"
using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2
{
    // No parameter constructor, runs reset() & returns to default values
    statistician::statistician()
    {
        this->reset();
    }

    // Parameter constructor, updates private data w/ respective values
    // Precondition: Must have 4 parameters, each being the correct data type specified.
    statistician::statistician(int l, double s, double mi, double mx)
    {
        length = l;
        sums = s;
        mins = mi;
        maxs = mx;
    }

    // Returns all varaibles to be the value of 0.0, or in the case of mins: INT_MAX.
    void statistician::reset(void)
    {
        length = sums = maxs = last = 0;
        mins = INT_MAX;
    }

    // Returns private variable length
    int statistician::len(void) const
    {
        return length;
    }

    // Returns private variable sum
    double statistician::sum(void) const
    {
        return sums;
    }
    // Returns private variable mins
    double statistician::minimum(void) const
    {
        return mins;
    }
    // Returns private variable maxs
    double statistician::maximum(void) const
    {
        return maxs;
    }

    // Calculates mean using len and sum values
    double statistician::mean(void) const
    {
        return sums / length;
    }

    // Using a new double, updates the new total sum, len, last insert (this parameter), and
    // min and max.
    // Precondition: d must be a double value
    void statistician::next(double d)
    {
        length++;
        sums += d;
        if (d < mins)
        {
            mins = d;
        }
        if (d > maxs)
        {
            maxs = d;
        }
        last = d;
    }

    // NON-MEMBER functions for the statistician class:
    statistician operator+(const statistician &s1, const statistician &s2)
    {
        // Postcondition: The statistician that is returned contains all the
        // numbers of the sequences of s1 and s2.

        double min;
        double max;

        if (s1.mins < s2.mins)
        {
            min = s1.mins;
        }
        else
        {
            min = s2.mins;
        }

        if (s1.maxs > s2.maxs)
        {
            max = s1.maxs;
        }
        else
        {
            max = s2.maxs;
        }

        return statistician(s1.length + s2.length, s1.sums + s2.sums, min, max);
    }

    statistician operator*(double scale, const statistician &s)
    {
        // Postcondition: The statistician that is returned contains the same
        // numbers that s does, but each number has been multiplied by the
        // scale number.
        double min_hold = s.mins * scale;
        double max_hold = s.maxs * scale;
        if (max_hold < min_hold)
        {
            double hold = min_hold;
            min_hold = max_hold;
            max_hold = hold;
        }

        return statistician(s.length, s.sums * scale, min_hold, max_hold);
    }

    bool operator==(const statistician &s1, const statistician &s2)
    {
        // Postcondition: The return value is true if s1 and s2 have the zero
        // length. Also, if the length is greater than zero, then s1 and s2 must
        // have the same length, the same mean, the same minimum,
        // the same maximum, and the same sum.
        if (s1.len() == 0 && s2.len() == 0)
        {
            return true;
        }
        if (s1.len() == s2.len() && s1.sum() == s2.sum() && s1.maximum() == s2.maximum() && s1.minimum() == s2.minimum())
        {
            return true;
        }
        return false;
    }
}