// Logan Calder, COEN79L TH 2:10
// Lab #4, keyed_bag
//
// This file contains all the method initializations for the class keyed_bag. It also contains the initializations
// for operator overrides.
//
// File 1/3: Other files: keyed_bag_teser.cpp, keyed_bag.h

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4_loganc
{
    keyed_bag::keyed_bag()
    {
        erase(); // Same as erase(), so can just call it here
    }

    void keyed_bag::erase()
    {
        for (int i = 0; i < CAPACITY; i++)
        {
            data[i] = -1;
            keys[i] = '\0';
        }
        used = 0;
    }

    bool keyed_bag::erase(const key_type &key)
    {
        for (int i = 0; i < CAPACITY; i++)
        {
            if (keys[i] == key)
            {
                for (int j = i; j < CAPACITY - 1; j++) // Shift data over after erased key
                {
                    keys[j] = keys[j + 1];
                    data[j] = data[j + 1];
                }
                used--;
                return true;
            }
        }
        return false;
    }

    void keyed_bag::insert(const value_type &entry, const key_type &key)
    {
        keys[used] = key;
        data[used] = entry;
        used++;
    }

    void keyed_bag::operator+=(const keyed_bag &addend)
    {
        for (int i = 0; i < addend.used; i++)
        {
            if (!has_key(addend.keys[i]))
            {
                keys[used] = addend.keys[i];
                data[used] = addend.data[i];
                used++;
            }
        }
    }

    // CONSTANT MEMBER FUNCTIONS for the keyed_bag class:
    bool keyed_bag::has_key(const key_type &key) const
    {
        for (int i = 0; i < used; i++)
        {
            if (keys[i] == key)
            {
                return true;
            }
        }
        return false;
    }

    keyed_bag::value_type keyed_bag::get(const key_type &key) const
    {
        for (int i = 0; i < used; i++)
        {
            if (keys[i] == key)
            {
                return data[i];
            }
        }
        return -1;
    }

    keyed_bag::size_type keyed_bag::size() const
    {
        return used;
    }

    keyed_bag::size_type keyed_bag::count(const value_type &target) const
    {
        size_type counter = 0;
        for (int i = 0; i < used; i++)
        {
            if (data[i] == target)
            {
                counter++;
            }
        }
        return counter;
    }

    bool keyed_bag::hasDuplicateKey(const keyed_bag &otherBag) const
    {
        for (int i = 0; i < otherBag.used; i++)
        {
            if (has_key(otherBag.keys[i]))
            {
                return true;
            }
        }
        return false;
    }

    keyed_bag operator+(const keyed_bag &b1, const keyed_bag &b2)
    {
        keyed_bag dummy;
        dummy += b1;
        dummy += b2;
        return dummy;
    }

}