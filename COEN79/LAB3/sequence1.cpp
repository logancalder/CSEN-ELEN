// Logan Calder, COEN79L TH 2:10
// Lab #2, sequence1
//
// This file contains the class method definations for sequence, including constant member,
// modifyng member, and non-member methods & operator overrides as declared in sequence1.h.
// These are then used in official_seq_test.cpp.
//
// File 1/3: Other files: sequence1.h, official_seq_test.cpp

#include <stdio.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include "sequence1.h"

using namespace std;

namespace coen79_lab3
{

    // CONSTRUCTOR
    // Postcondition: The sequence has been initialized as an empty sequence.
    sequence::sequence()
    {
        this->length = 0;
        this->curr = 0;
    }

    // MODIFICATION MEMBER FUNCTIONS
    // Postcondition: The iterator is reset to position 0;
    void sequence::start()
    {
        curr = 0;
    }

    // Postcondition: The iterator points to the last item in the sequence;
    void sequence::end()
    {
        curr = length - 1;
    }

    // Postcondition: The iterator is reset to CAPACITY - 1, regardless of the numebr of items
    // in the sequence;
    void sequence::last()
    {
        curr = CAPACITY - 1;
    }

    // Precondtion: isitem() returns true
    // Postcondition: The iterator's value is increased by 1, unless it is already at the end of the sequence.
    void sequence::advance()
    {
        if (is_item() && curr < length)
        {
            curr++;
        }
        else
        {
            cout << "is_item is not true or curr is less than length." << endl;
        }
    }

    // Postcondition: The iterator's value is reduced by 1, unless it is already at the beginning
    // of the sequence.
    void sequence::retreat()
    {
        if (curr > 0)
        {
            curr--;
        }
    }

    // Precondition: size() < CAPACITY
    // Postcondition: A new copy of entry has been inserted in the sequence
    // before the current item. If there was no current item, the new entry
    // has been inserted at the front. In either case, the new item is now the
    // current item of the sequence.
    void sequence::insert(const value_type &entry)
    {
        if (!(size() < CAPACITY))
        {
            cout << "Size is not less than capacity." << endl;
            return;
        }

        if (length == 0)
        {
            data[length] = entry;
            curr = 0;
        }
        else
        {
            for (int i = length; i >= curr + 1; i--)
            {
                data[i] = data[i - 1];
            }
            data[curr] = entry;
        }
        length++;
    }

    // Precondition: size() < CAPACITY
    // Postcondition: A new copy of entry has been inserted in the sequence
    // after the current item. If there was no current item, the new entry
    // has been attached to the end. In either case, the new item is now the
    // current item of the sequence.
    void sequence::attach(const value_type &entry)
    {
        if (!(size() < CAPACITY))
        {
            cout << "Size is not less than capacity." << endl;
            return;
        }
        if (!is_item())
        {
            data[length] = entry;
        }
        else
        {
            for (int i = length; i > curr + 1; i--)
            {
                data[i] = data[i - 1];
            }
            data[curr + 1] = entry;
            curr++;
        }
        length++;
    }

    // Precondtion: isitem() returns true
    // Postcondition: The current item has been removed from the sequence,
    // and the item after this (if there is one) is now the current item.
    void sequence::remove_current()
    {
        if (!is_item())
        {
            cout << "There is no current item" << endl;
            return;
        }
        for (int i = curr + 1; i < length; i++)
        {
            data[i - 1] = data[i]; // Overwrites current & then shifts all items down 1
        }
        length--;
    }

    // Precondition: size() < CAPACITY
    // Postcondition: A new copy of entry has been inserted in the sequence
    // at the front. The new item is now the current item of the sequence.
    void sequence::insert_front(const value_type &entry)
    {
        if (!(size() < CAPACITY))
        {
            cout << "Size is not less than capacity." << endl;
            return;
        }
        curr = 0;
        insert(entry);
        length++;
    }

    // Precondition: size() < CAPACITY
    // Postcondition: A new copy of entry has been inserted in the sequence
    // at the back. The new item is now the current item of the sequence.
    void sequence::attach_back(const value_type &entry)
    {
        if (!(size() < CAPACITY))
        {
            cout << "Size is not less than capacity." << endl;
            return;
        }
        data[length] = entry;
        length++;
    }

    // Precondition: isitem() returns true
    // Postcondition: The item at the front of the sequence has been removed from the sequence,
    // and the current item points at the front of the sequence.
    void sequence::remove_front()
    {
        if (!is_item())
        {
            cout << "There is no current item" << endl;
            return;
        }
        for (int i = 0; i < length - 1; i++)
        {
            data[i] = data[i + 1];
        }
        length--;
    }

    // CONSTANT MEMBER FUNCTIONS

    // Postcondition: The return value is the number of items in the ssequence.
    sequence::size_type sequence::size() const
    {
        return length;
    }

    // Postcondition: A true return value indicates that there is a valid
    // "current" item that may be retrieved by activating the current
    // member function (listed below). A false return value indicates that
    // there is no valid current item.
    bool sequence::is_item() const
    {
        if (curr < length)
        {
            return true;
        }
        return false;
    }

    // Precondtion: isitem() returns true
    // Poscondition: Returns the item in the sequence at the current position of the iterator.
    sequence::value_type sequence::current() const
    {
        assert(is_item());
        return data[curr];
    }

    // Precondition: index < used
    // Postcondition: The item returned is the item stored at "index"
    sequence::value_type sequence::operator[](int index) const
    {
        assert(index < length);
        return (data[index]);
    }

    // Postcondition: The value returned is the mean of the values stored in the sequence.
    double sequence::mean() const
    {
        double total = 0.0;
        for (int i = 0; i < length; i++)
        {
            total += data[i];
        }
        return total / length;
    }

    // Postcondition: The value returned is the stadard deviation of the values stored in the sequence.
    double sequence::standardDeviation() const
    {
        double total = 0.0;
        for (int i = 0; i < length; i++)
        {
            total += pow(data[i] - mean(), 2);
        }
        return sqrt(total / length);
    }

    // NON-MEMBER FUNCTIONS

    // Postcondition: The sequence that is returned contains all the
    // numbers of the sequences of lsh and rhs.
    sequence operator+(const sequence &lhs, const sequence &rhs)
    {
        assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
        sequence(dummy);
        dummy += lhs;
        dummy += rhs;
        return dummy;
    }

    // Postcondition: Adds the items of rhs to the lhs. Also returns a copy of lhs.
    sequence operator+=(sequence &lhs, const sequence &rhs)
    {
        assert((lhs.size() + rhs.size()) < sequence::CAPACITY);
        sequence::size_type count = rhs.size();
        for (int i = 0; i < count; i++)
        {
            lhs.attach(rhs[i]);
        }
        return lhs;
    }

    // Postcondition: The value returned is the summation of the values stored in the sequence s.
    sequence::value_type summation(const sequence &s)
    {
        double total = 0.0;
        for (int i = 0; i < s.size(); i++)
        {
            total += s[i];
        }
        return total;
    }
}