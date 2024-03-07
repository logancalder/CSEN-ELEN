/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 *
 * Assignment: Create a linked list implementation for SCUClass that stores, removes, &
 * 			   lists current students in the class. Implementation using pointers & node
 *   		   utilizing C++ Class.
 * 1 of 4: student.cpp
 */

#include "scuclass.h"

namespace coen79
{
	int Student::getID(void) const
	{
		return this->id;
	}

	std::string Student::getName(void) const
	{
		return this->name;
	}

	std::ostream &operator<<(std::ostream &stream, const Student &student)
	{
		return stream << student.getName() << ":" << student.getID();
	}
}
