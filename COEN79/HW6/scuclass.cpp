/*
 * Name: Colin Friedel, David Thuita, Logan Calder, Kyle Samonte
 * Email: aigreen@scu.edu, kpazmino@scu.edu, lcalder@scu.edu, wluo@scu.edu
 *
 * Assignment: Create a container representing the
 *             students in a class via a pointer to
 *             an array and implement methods for
 *             add removing and listing the students.
 * 2 of 4: scuclass.cpp
 */

#include "scuclass.h"

using namespace std;

namespace coen79_group6
{
	SCUClass::SCUClass(void) : length{0}, maxLength{CAPACITY}
	{
		;
	}

	SCUClass::~SCUClass(void)
	{
		this->students.clear();
	}

	void SCUClass::addStudent(const int studentID, const string studentName)
	{
		Student s = Student(studentID, studentName);
		this->students.push_back(s);
	}

	void SCUClass::remove(const int studentID)
	{
		int i = 0;
		for (const auto &element : this->students)
		{
			if (element.getID() == studentID)
			{
				this->students.erase(this->students.begin() + i);
				break;
			}
			i++;
		}
	}

	void SCUClass::list(void) const
	{
		for (const auto &element : this->students)
		{
			cout << element << endl;
		}
		cout << endl;
	}
}
