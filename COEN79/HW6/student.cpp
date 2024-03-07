/*
 * Name: Colin Friedel, David Thuita, Logan Calder, Kyle Samonte
 * Email: aigreen@scu.edu, kpazmino@scu.edu, lcalder@scu.edu, wluo@scu.edu
 *
 * Assignment: Create a container representing the
 *             students in a class via a pointer to
 *             an array and implement methods for
 *             add removing and listing the students.
 * 3 of 4: student.cpp
 */

#include "scuclass.h"

using namespace std;

namespace coen79_group6
{
	int Student::getID(void) const
	{
		return this->id;
	}

	string Student::getName(void) const
	{
		return this->name;
	}

	ostream &operator<<(ostream &stream, const Student &student)
	{
		return stream << "id: " << student.getID() << " "
					  << "name: " << student.getName();
	}
}
