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
    // Will add a new elt to the BEGINNING of the linked list
    // Precondition: Head is a valid pointer & Student s is not NULL
    void Node::append(Node **head, Student s)
    {
        Node *node = new Node();
        node->student = s;
        node->next = *head;
        *head = node;
    }

    // Will cout the entirety of SCUClass linked list
    // Precondition: Pointer must be to a Node object
    void Node::displayList(struct Node *node)
    {
        while (node != NULL)
        {
            std::cout << "id: " << node->student.getID() << " "
                      << "name: " << node->student.getName() << std::endl;
            node = node->next;
        }
        std::cout << "\n";
    }

    // Will remove the provided student from linked list using parameter ID
    // Precondition: ID must be in linked list
    void Node::remove(Node *head, int id)
    {
        while (head != NULL)
        {
            if (head->next->student.getID() == id)
            {
                Node *dummy = head->next;
                head->next = head->next->next;
                delete dummy;
                return;
            }
            head = head->next;
        }
        return;
    }
}
