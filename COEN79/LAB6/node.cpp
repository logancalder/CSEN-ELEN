// Logan Calder, COEN79L TH 2:10
// Lab #6, node
//
// This file contains all node methods for linked list implementation. It contains methods to search,
// create sub lists, delete, and append.
//
// File 1/3: Other files: node.h, node_test.cpp
// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert> // Provides assert
#include <cstdlib> // Provides NULL and size_t
#include <cstdlib>
#include <iostream>

using namespace std;

namespace coen79_lab6
{
	size_t list_length(const node *head_ptr)
	// Library facilities used: cstdlib
	{
		const node *cursor;
		size_t answer;

		answer = 0;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			++answer;

		return answer;
	}

	void list_head_insert(node *&head_ptr, const node::value_type &entry)
	{
		head_ptr = new node(entry, head_ptr);
	}

	void list_insert(node *previous_ptr, const node::value_type &entry)
	{
		node *insert_ptr;

		insert_ptr = new node(entry, previous_ptr->link());
		previous_ptr->set_link(insert_ptr);
	}

	node *list_search(node *head_ptr, const node::value_type &target)
	// Library facilities used: cstdlib
	{
		node *cursor;

		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			if (target == cursor->data())
				return cursor;

		return NULL;
	}

	const node *list_search(const node *head_ptr, const node::value_type &target)
	// Library facilities used: cstdlib
	{
		const node *cursor;

		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
			if (target == cursor->data())
				return cursor;

		return NULL;
	}

	node *list_locate(node *head_ptr, size_t position)
	// Library facilities used: cassert, cstdlib
	{
		node *cursor;
		size_t i;

		assert(0 < position);
		cursor = head_ptr;
		for (i = 1; (i < position) && (cursor != NULL); i++)
			cursor = cursor->link();

		return cursor;
	}

	const node *list_locate(const node *head_ptr, size_t position)
	// Library facilities used: cassert, cstdlib
	{
		const node *cursor;
		size_t i;

		assert(0 < position);
		cursor = head_ptr;
		for (i = 1; (i < position) && (cursor != NULL); i++)
			cursor = cursor->link();

		return cursor;
	}

	void list_head_remove(node *&head_ptr)
	{
		node *remove_ptr;

		remove_ptr = head_ptr;
		head_ptr = head_ptr->link();
		delete remove_ptr;
	}

	void list_remove(node *previous_ptr)
	{
		node *remove_ptr;

		remove_ptr = previous_ptr->link();
		previous_ptr->set_link(remove_ptr->link());
		delete remove_ptr;
	}

	void list_clear(node *&head_ptr)
	// Library facilities used: cstdlib
	{
		while (head_ptr != NULL)
			list_head_remove(head_ptr);
	}

	void list_copy(const node *source_ptr, node *&head_ptr, node *&tail_ptr)
	// Library facilities used: cstdlib
	{
		head_ptr = NULL;
		tail_ptr = NULL;

		// Handle the case of the empty list.
		if (source_ptr == NULL)
			return;

		// Make the head node for the newly created list, and put data in it.
		list_head_insert(head_ptr, source_ptr->data());
		tail_ptr = head_ptr;

		// Copy the rest of the nodes one at a time, adding at the tail of new list.
		source_ptr = source_ptr->link();
		while (source_ptr != NULL)
		{
			list_insert(tail_ptr, source_ptr->data());
			tail_ptr = tail_ptr->link();
			source_ptr = source_ptr->link();
		}
	}

	// implemented methods

	void list_piece(node *start_ptr, node *end_ptr, node *&head_ptr, node *&tail_ptr)
	{
		head_ptr = NULL;
		tail_ptr = NULL;
		if (start_ptr == end_ptr || start_ptr == NULL)
			return;
		list_head_insert(head_ptr, start_ptr->data());
		tail_ptr = head_ptr;
		while (start_ptr->link() != end_ptr)
		{
			start_ptr = start_ptr->link();
			list_insert(tail_ptr, start_ptr->data());
			tail_ptr = tail_ptr->link();
		}
	}

	void list_insert_at(node *&head_ptr, const node::value_type &entry, size_t position)
	{
		assert(position > 0 && position <= list_length(head_ptr) + 1);
		if (position == 1)
			list_head_insert(head_ptr, entry);
		else
			list_insert(list_locate(head_ptr, position - 1), entry);
	}

	size_t list_occurrences(node *head_ptr, const node::value_type &target)
	{
		if (head_ptr == NULL)
		{
			return 0;
		}

		size_t occurence = 0;
		node *temp = head_ptr;
		while (temp != NULL)
		{
			if (temp->data() == target)
			{
				occurence++;
			}
			temp = temp->link();
		}
		return occurence;
	}

	node::value_type list_remove_at(node *&head_ptr, size_t position)
	{
		assert(position > 0 && position <= list_length(head_ptr));
		node::value_type tmp;
		if (position == 1)
		{								// If we want to remove head
			tmp = head_ptr->data();		// assign temp value
			list_head_remove(head_ptr); // call list_head_remove
			return tmp;
		}
		else
			tmp = list_locate(head_ptr, position - 1)->data(); // elsewhere, find position
		list_remove(list_locate(head_ptr, position - 1));	   // find position and remove node there
		return tmp;
	}

	// Returns a pointer to the head pointer of new list of copied list segment
	node *list_copy_segment(node *head_ptr, size_t start, size_t finish)
	{
		assert(1 <= start && start <= finish && finish <= list_length(head_ptr));
		node *newHead = NULL;
		node *newTail = NULL;
		if (head_ptr == NULL) // If empty, return null
			return NULL;
		// List piece assigns pointer of start and finish to newHead and newTail.
		// We call locate to find location of start and finish+1
		list_piece(list_locate(head_ptr, start), list_locate(head_ptr, finish + 1), newHead, newTail);
		return newHead;
	}

	// Prints all value_type data of all nodes
	void list_print(const node *head_ptr)
	{
		if (head_ptr == NULL)
		{				  // Check if list empty
			cout << endl; // print out nothing
			return;
		}
		while (head_ptr != NULL)
		{ // iterate through list
			if (head_ptr->link() == NULL)
			{								 // if we're on last node on list
				cout << head_ptr->data();	 // print data without comma
				head_ptr = head_ptr->link(); // shift to escape while loop
			}
			else
			{									  // Else (not last element)
				cout << head_ptr->data() << ", "; // print data with comma
				head_ptr = head_ptr->link();
			}
		}
		cout << endl;
		return;
	}

	// Remove all duplicates from linked list
	void list_remove_dups(node *head_ptr)
	{
		if (head_ptr == NULL) // If empty, return
			return;
		node *cursor1;
		node *cursor2;
		node *dup;
		cursor1 = head_ptr; // Start cursor 1 at head
		while (cursor1 != NULL)
		{					   // iterate through cursor1
			cursor2 = cursor1; // start cursor 2 at cursor 1
			while (cursor2->link() != NULL)
			{ // iterate through cursor2
				if (cursor1->data() == cursor2->data())
				{						 // if we find a match
					node *tmp = cursor2; // temporary node
					list_remove(tmp);	 // remove that node
				}
				else
				{							   // if we don't find match
					cursor2 = cursor2->link(); // keep shifting cursor2
				}
			}
			cursor1 = cursor1->link(); // keep shifting cursor1
		}
	}

	// Floyd's Loop Detection algorithm
	node *list_detect_loop(node *head_ptr)
	{
		node *slow;
		node *fast;
		slow = fast = head_ptr; // Start both pointers at head
		while (fast != NULL && fast->link() != NULL)
		{								 // iterate through list
			slow = slow->link();		 // slow moves by one
			fast = fast->link()->link(); // fast moves by two
			if (slow == fast)			 // once they meet, break
				break;
		}
		if (fast == NULL || fast->link() == NULL) // if we never meet (aka fast/fast->link is null)
			return NULL;						  // return null
		slow = head_ptr;						  // else, start slow at head again
		while (slow != fast)
		{						 // iterate through list again
			slow = slow->link(); // iterate both by one
			fast = fast->link();
		}
		return slow; // return the position where fast and slow meet
	}

}