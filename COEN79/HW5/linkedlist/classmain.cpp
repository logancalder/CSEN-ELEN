/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 *
 * Assignment: Create a linked list implementation for SCUClass that stores, removes, &
 * 			   lists current students in the class. Implementation using pointers & node
 *   		   utilizing C++ Class.
 * 3 of 4: classmain.cpp
 */

#include <fstream>
#include <string>

#include "scuclass.h"

using namespace coen79;
using namespace std;

// Precondition: All student IDs must be the same length
int main(int argc, char *argv[])
{
	ifstream input("testdata.txt"); // Open and read file

	if (!input.is_open())
	{
		cout << "Failed to open file" << endl;
		return -1;
	}

	cout << "Testing file input:" << endl;

	string line{}; // Obtain a string of the current line in file

	Node *head = NULL; // Create empty linked list

	while (getline(input, line))
	{
		string cmd = line.substr(0, 1); // Get the command

		if (line.length() != 1) // If its not 'L'
		{
			string idString = line.substr(2, 7);			   // Get ID
			string name = line.substr(11, line.length() - 11); // Get Name
			int id{stoi(idString)};							   // Convert ID string to int

			if (cmd == "A") // If append, add to linked list
			{
				Student *stud = new Student(id, name);
				Node::append(&head, *stud);
			}
			if (cmd == "X") // If remove, remove from linked list
			{
				Node::remove(head, id);
			}
		}
		else
		{
			Node::displayList(head); // This will run if the command was 'L'
		}
	}
}
