// Logan Calder, COEN12L R 9:15, 6/8/23
// Script implements a priority queue using heaping. Permits creating a queue, destroying a queue (freeing all memory),
// obtaining # of elts in queue, adding an elt to the priority queue, and removing the smallest entry from the queue. To do
// the last two items, we utilize comparing parents w/ children and swapping their values depending on if they are greater than/less than
// each other (reheaping).

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"
#include <string.h>
#include <stdbool.h>

#define p(x) (x - 1) / 2 // Parent
#define l(x) (x * 2) + 1 // Left child
#define r(x) (x * 2) + 2 // Right child

// Defining new type PRQ (Priority Queue)
// ---------------------------------------------------------------------------------------
typedef struct pqueue
{
    int count;
    int length;
    void **data;
    int (*compare)();
} PQ;

// createQueue
// ---------------------------------------------------------------------------------------
// Return a pointer to a new priority queue using compare as comparison function
PQ *createQueue(int (*compare)())
{
    PQ *pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    pq->count = 0;
    pq->length = 10;
    pq->compare = compare;
    pq->data = malloc(10 * sizeof(void *));
    return pq;
}

// destroyQueue
// ---------------------------------------------------------------------------------------
// Dealloc memory associated w/ the priority queue
void destroyQueue(PQ *pq)
{
    assert(pq != NULL);
    assert(pq->data != NULL);
    int i;
    for (i = 0; i < pq->count; i++)
    {
        free(pq->data[i]);
    }
    free(pq->data);
    free(pq);
}

// numEntries
// ---------------------------------------------------------------------------------------
// Return the number of entries in the priority queue
int numEntries(PQ *pq)
{
    assert(pq != NULL);
    return (pq->count);
}

// addEntry
// ---------------------------------------------------------------------------------------
// Add entry to priority queue
void addEntry(PQ *pq, void *entry)
{
    assert(pq != NULL);

    // Update length if full, multiply by 2 as per instructions to prevent excessive usage of realloc
    if (pq->length == pq->count)
    {
        pq->length *= 2;
        pq->data = realloc(pq->data, pq->length * sizeof(void *));
        assert(pq->data != NULL);
    }

    pq->data[pq->count] = entry;
    int childIndex = pq->count;
    int parentIndex = p(parentIndex);

    // If child less than parent replace parent w/ child
    while ((*pq->compare)(pq->data[childIndex], pq->data[parentIndex]) < 0)
    {
        void *dummy;
        dummy = pq->data[parentIndex];
        pq->data[parentIndex] = pq->data[childIndex];
        pq->data[childIndex] = dummy;
        childIndex = parentIndex;
        parentIndex = p(parentIndex);
    }

    pq->count++;
}

// removeEntry
// ---------------------------------------------------------------------------------------
// Removes and returns smallest entry from priority queue
void *removeEntry(PQ *pq)
{
    // Asserting q is not empty, then obtain smallest value as first index.
    // Store in dummy variable del bc we will swap order of heap
    assert(pq != NULL);
    PQ *del = malloc(sizeof(PQ));
    assert(del != NULL);
    del = pq->data[0];

    // Begin swapping parents w/ children to find min val
    pq->data[0] = pq->data[pq->count - 1];
    int i = 0;

    while ((i * 2) + 1 <= pq->count - 1)
    { // If left
        int smallestIndex = l(i);
        if (r(i) <= pq->count - 1)
        { // If right
            if ((*pq->compare)(pq->data[r(i)], pq->data[l(i)]) < 0)
            {                         // If right less than left
                smallestIndex = r(i); // Smallest index will be right instead of left
            }
        }

        if ((*pq->compare)(pq->data[i], pq->data[smallestIndex]) < 0)
        { // If parent is less than child break
            break;
        }
        else
        { // Swap parent w/ child
            void *dummy = pq->data[i];
            pq->data[i] = pq->data[smallestIndex];
            pq->data[smallestIndex] = dummy;

            i = smallestIndex; // Increment index
        }
    }
    pq->count--;
    return (del);
}
