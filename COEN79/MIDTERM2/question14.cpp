#include <iostream>

class LinkedL
{
public:
    LinkedL() : next(NULL), payload(NULL) {}
    ~LinkedL();

    LinkedL *getNext() const { return this->next; }
    LinkedL *findMinNode();

private:
    void *payload;
    LinkedL *next;
};

// Assuming you have implemented the less than operator for the payload type
bool operator<(const LinkedL &lhs, const LinkedL &rhs)
{
    // Implement the logic to compare payloads
    // For example, assuming payloads are integers:
    return (*(static_cast<int *>(lhs.payload)) < *(static_cast<int *>(rhs.payload)));
}

LinkedL::~LinkedL()
{
    // Implement destructor logic if needed
}

LinkedL *LinkedL::findMinNode()
{
    if (!next)
    {
        // If the list is empty, return NULL
        return NULL;
    }

    LinkedL *minNode = this;

    // Assuming you have iterators implemented
    for (LinkedL *current = next; current != NULL; current = current->getNext())
    {
        // Use the less than operator to compare payloads
        if (*current < *minNode)
        {
            minNode = current;
        }
    }

    return minNode;
}

int main()
{
    // Original code
    LinkedL *node1 = new LinkedL();
    LinkedL *node2 = new LinkedL();
    // ... add more nodes as needed

    // New code to find the node with the least value
    LinkedL *minNode = node1->findMinNode();

    if (minNode)
    {
        std::cout << "Node with the least value found!" << std::endl;
    }
    else
    {
        std::cout << "List is empty." << std::endl;
    }

    // Don't forget to deallocate memory
    delete node1;
    delete node2;
    // ... delete other nodes as needed

    return 0;
}
