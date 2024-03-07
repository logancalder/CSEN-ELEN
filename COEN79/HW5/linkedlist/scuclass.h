/*
 * Name: Logan Calder
 * Email: lcalder@scu.edu
 *
 * Assignment: Create a linked list implementation for SCUClass that stores, removes, &
 * 			   lists current students in the class. Implementation using pointers & node
 *   		   utilizing C++ Class.
 * 2 of 4: scuclass.h
 */

#ifndef COEN79_GROUP5_SCUCLASS_H_
#define COEN79_GROUP5_SCUCLASS_H_

#include <iostream>

namespace coen79
{
	class Student
	{
	private:
		int id;
		std::string name;

	public:
		Student(void) : id(0), name(){};
		Student(const int studentID, const std::string &studentName) : id(studentID), name(studentName){};
		virtual ~Student(void){};

		int getID(void) const;
		std::string getName(void) const;

		friend std::ostream &operator<<(std::ostream &stream, const Student &student);
	};

	class Node // Node class declaration
	{
	public:
		Student student;
		Node *next;

		static void append(Node **head, Student s);
		static void displayList(struct Node *node);
		static void remove(Node *head, int id);
	};

}

#endif
