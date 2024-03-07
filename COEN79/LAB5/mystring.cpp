// Logan Calder, COEN79L TH 2:10
// Lab #5, mystring
//
// This file contains the definitions for all string class methods, both member & non-
// member. This file is the replication of the cstring library in C++ (though likely
// much more inefficient). These methods track & manage memory & the storage of chars
// in an efficient way to permit the usage of strings.
//
// File 1/3: Other files: mystring.h, str_demo.cpp

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "mystring.h"

using namespace std;

namespace coen79_lab5_loganc
{
    string::string(const char str[])
    {
        allocated = strlen(str) + 1;
        t
            current_length = allocated - 1;

        characters = new char[allocated];
        strncpy(characters, str, allocated);
    }

    string::string(char c)
    {
        allocated = 2;
        current_length = 1;
        characters[0] = c;
        characters[1] = '\n';
    } // NEW FUNCTION 1

    string::string(const string &source)
    {
        current_length = source.length();
        allocated = current_length + 1;

        characters = new char[allocated];
        strncpy(characters, source.characters, current_length);
    }

    string::~string()
    {
        allocated = 0;
        current_length = 0;
        delete[] characters;
    }

    // MODIFICATION MEMBER FUNCTIONS
    void string::operator+=(const string &addend)
    {
        current_length += addend.current_length;
        allocated += addend.allocated;
        reserve(allocated);
        strncat(characters, addend.characters, addend.current_length);
    }

    void string::operator+=(const char addend[])
    {
        allocated += strlen(addend) + 1;
        current_length += strlen(addend);
        reserve(allocated);
        strncat(characters, addend, strlen(addend));
    }

    void string::operator+=(char addend)
    {
        allocated += 1;
        current_length += 1;
        reserve(allocated);
        characters[current_length] = addend;
    }

    void string::reserve(size_t n)
    {
        char *tmp = new char[n];
        if (characters != NULL)
        {
            strncpy(tmp, characters, current_length);
            delete[] characters;
        }
        characters = tmp;
    }

    string &string::operator=(const string &source)
    {
        this->dlt(0, current_length);
        if (current_length != source.current_length)
        {
            allocated = source.allocated;
            reserve(allocated);
        }
        strncpy(characters, source.characters, source.current_length);
        current_length = source.current_length;
        return *this;
    }

    void string::insert(const string &source, unsigned int position)
    {
        size_t total_length = current_length + source.current_length;
        if (allocated < (total_length))
            reserve(total_length);
        for (int i = position; i < current_length; i++)
        {
            characters[i + source.length()] = characters[i];
        }
        current_length += source.length();
        for (int i = 0; i < source.length(); i++)
        {
            characters[i + position] = source.characters[i];
        }
    }

    void string::dlt(unsigned int position, unsigned int num)
    {
        for (int i = position; i < current_length; i++)
        {
            characters[i] = characters[i + num];
        }
        current_length -= num;
    }

    void string::replace(char c, unsigned int position)
    {
        characters[position] = c;
    }

    void string::replace(const string &source, unsigned int position)
    {
        for (int i = 0; i < source.length(); i++)
        {
            characters[i + position] = source[i];
        }
    }

    // CONSTANT MEMBER FUNCTIONS
    char string::operator[](size_t position) const
    {
        return characters[position];
    }

    int string::search(char c) const
    {
        for (int i = 0; i < current_length; i++)
        {
            if (characters[i] == c)
            {
                return i;
            }
        }
        return -1;
    }

    int string::search(const string &substring) const
    {
        char *temp = strstr(characters, substring.characters);
        if (temp != NULL)
        {
            return temp[0] - characters[0];
        }
        return -1;
    }

    unsigned int string::count(char c) const
    {
        unsigned int count = 0;
        for (int i = 0; i < current_length; i++)
        {
            if (characters[i] == c)
            {
                count++;
            }
        }
        return count;
    }

    // FRIEND FUNCTIONS
    std::ostream &operator<<(std::ostream &outs, const string &source)
    {
        outs << source.characters;
        return outs;
    }

    bool operator==(const string &s1, const string &s2)
    {
        return (strcmp(s1.characters, s2.characters) == 0);
    }
    bool operator!=(const string &s1, const string &s2)
    {
        return (strcmp(s1.characters, s2.characters) != 0);
    }
    bool operator>(const string &s1, const string &s2)
    {
        return (strcmp(s1.characters, s2.characters) > 0);
    }
    bool operator<(const string &s1, const string &s2)
    {
        return (strcmp(s1.characters, s2.characters) < 0);
    }
    bool operator>=(const string &s1, const string &s2)
    {
        return (strcmp(s1.characters, s2.characters) >= 0);
    }
    bool operator<=(const string &s1, const string &s2)
    {
        return (strcmp(s1.characters, s2.characters) <= 0);
    }

    // NON-MEMBER FUNCTIONS for the string class
    string operator+(const string &s1, const string &s2)
    {
        string dummy;
        dummy.reserve(s1.length() + s2.length() + 1);
        dummy += s1;
        dummy += s2;
        return dummy;
    }
    string operator+(const string &s1, const char addend[])
    {
        string dummy;
        dummy.reserve(s1.length() + strlen(addend) + 1);
        dummy += s1;
        dummy += addend;
        return dummy;
    }

    std::istream &operator>>(std::istream &ins, string &target)
    {
        char *temp = new char[100];
        while (ins && isspace(ins.peek()))
        {
            ins.ignore();
        }
        ins >> temp;
        target = string(temp);
        return ins;
    }
}