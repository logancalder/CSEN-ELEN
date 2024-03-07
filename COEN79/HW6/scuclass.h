/*
 * Name: Colin Friedel, David Thuita, Logan Calder, Kyle Samonte
 * Email: aigreen@scu.edu, kpazmino@scu.edu, lcalder@scu.edu, wluo@scu.edu
 *
 * Assignment: Create a container representing the
 *             students in a class via a pointer to
 *             an array and implement methods for
 *             add removing and listing the students.
 * 1 of 4: scuclass.h
 */

#ifndef COEN79_GROUP6_SCUCLASS_H_
#define COEN79_GROUP6_SCUCLASS_H_

#include <iostream>
#include <vector>

using namespace std;

namespace coen79_group6
{
	static const size_t CAPACITY{30};

	class Student
	{
	private:
		int id;
		string name;

	public:
		Student(void) : id{0}, name{} {};
		Student(const int studentID, const string &studentName) : id{studentID}, name{studentName} {};

		int getID(void) const;
		string getName(void) const;

		friend ostream &operator<<(ostream &stream, const Student &student);
	};

	class SCUClass
	{
	private:
		vector<Student> students;
		size_t length;
		size_t maxLength;

	public:
		SCUClass(void);
		virtual ~SCUClass(void);

		void addStudent(const int studentID, const string studentName);
		void remove(const int studentID);
		void list(void) const;
	};
}

#endif
