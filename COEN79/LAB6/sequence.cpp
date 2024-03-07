// Logan Calder, COEN79L TH 2:10
// Lab #6, sequence
//
// This file contains a sequence implementaton using linked list class node. It permits for the insertion, attachment, and deletion of 
// data from a sequence.
//
// File 1/3: Other files: sequence.h, seq_test.cpp
// 
// FILE: sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//   COEN 79
//   --- Behnam Dezfouli, COEN, SCU ---
//
//
// INVARIANT for the sequence class
//   1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//   2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//       and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//       sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//       stored in the rest of the data.
//
//   3. If there is a current item, then it lies in *cursor; if there is no
//      current item, then cursor* equals NULL.
//
//   4. If there is a previous item, then it lies in precursor*.  If there is no previous
//        item, then precursor equals NULL.

#include <iostream>
#include <algorithm>  //provides copy function
#include <cassert>    //for assert function
#include "sequence.h" //header file for class
#include "node.h"     // provides node class

using namespace std; // For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        // Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        // Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    // CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence ::sequence()
    {
        init();
    }

    // Copy Constructor
    sequence ::sequence(const sequence &source)
    {
        init();
        *this = source;
    }

    sequence::~sequence()
    {
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

    void sequence::start()
    {
        cursor = head_ptr;
        precursor = head_ptr;
    }

    void sequence::end()
    {
        if (many_nodes == 0)
            return;
        cursor = tail_ptr;
        if (head_ptr == tail_ptr)
            precursor = NULL;
        else
            precursor = list_locate(head_ptr, many_nodes - 1);
    }

    void sequence::advance()
    {
        assert(is_item());
        precursor = cursor;
        cursor = cursor->link();
    }

    void sequence::insert(const value_type &entry)
    {
        if (precursor == NULL || !is_item())
        {
            list_head_insert(head_ptr, entry);
            if (tail_ptr == NULL)
            {
                tail_ptr = head_ptr;
            }
            cursor = head_ptr;
            precursor = NULL;
        }
        else
        {
            list_insert(precursor, entry);
            cursor = precursor->link();
        }
        many_nodes++;
    }

    void sequence::attach(const value_type &entry)
    {
        if (head_ptr == NULL)
        {
            list_head_insert(head_ptr, entry);
            precursor = NULL;
            tail_ptr = head_ptr;
            cursor = head_ptr;
        }
        else if (cursor == NULL)
        {
            list_insert(tail_ptr, entry);
            precursor = tail_ptr;
            cursor = tail_ptr->link();
            tail_ptr = tail_ptr->link();
        }
        else
        {
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = cursor->link();

            if (cursor->link() == NULL)
                tail_ptr = cursor;
        }

        many_nodes++;
    }

    void sequence::operator=(const sequence &source)
    {
        if (this == &source)
        {
            return;
        }
        many_nodes = source.many_nodes;
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        start();

        node *dummy = source.head_ptr;
        while (dummy != source.cursor)
        {
            advance();
            dummy = dummy->link();
        }
    }

    void sequence::remove_current()
    {
        if (head_ptr == cursor && head_ptr == tail_ptr)
        {
            list_head_remove(head_ptr);
            init();
        }
        else if (head_ptr == cursor && head_ptr != tail_ptr)
        {
            list_head_remove(head_ptr);
            precursor = NULL;
            cursor = head_ptr;
        }
        else if (cursor == tail_ptr)
        {
            list_remove(precursor);
            tail_ptr = precursor;
            cursor = NULL;
        }
        else
        {
            list_remove(precursor);
            cursor = precursor->link();
        }
        many_nodes--;
    }

    // CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size() const
    {
        return many_nodes;
    }

    bool sequence::is_item() const
    {
        return (cursor != NULL);
    }

    sequence::value_type sequence::current() const
    {
        return cursor->data();
    }
}
