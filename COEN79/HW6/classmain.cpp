/*
 * Name: Colin Friedel, David Thuita, Logan Calder, Kyle Samonte
 * Email: aigreen@scu.edu, kpazmino@scu.edu, lcalder@scu.edu, wluo@scu.edu
 *
 * Assignment: Implement homework #5 with either STL vector or list.
 *
 * 4 of 4: classmain.cpp
 */

#include <fstream>
#include <string>
#include <vector>
#include "scuclass.h"

using namespace coen79_group6;
using namespace std;

int main(int argc, char *argv[])
{
	ifstream input("TestStudentData.txt"); // Open and read file

	if (!input.is_open())
	{
		cout << "Failed to open file" << endl;
		return -1;
	}

	cout << "Testing file input:" << endl;

	string line{}; // Obtain a string of the current line in file

	SCUClass coen79{};

	// Precondition: All IDs are the same; L has no other input on line; every line starts w/ A, X, or L.
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
				coen79.addStudent(id, name);
			}
			if (cmd == "X") // If remove, remove from linked list
			{
				coen79.remove(id);
			}
		}
		else
		{
			coen79.list();
		}
	}
}