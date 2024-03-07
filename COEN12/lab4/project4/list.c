// Logan Calder, COEN12L R 9:15, 5/18/23
// Script implements a linked list system to store void pointers. The list is a double circuraly linked list, allowing for
// backward and forward continious traversal. Some functions from this script are used in set.c.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include <string.h>
#include <stdbool.h>

// Defining new type LIST
// ---------------------------------------------------------------------------------------
struct list
{
    int count;
    struct node *head;
    int (*compare)();
};

// Defining new type NODE
// ---------------------------------------------------------------------------------------
typedef struct node
{
    void *data;
    struct node *next;
    struct node *prev;
} NODE;

// createList
// ---------------------------------------------------------------------------------------
// Returns a pointer to a new list with a maximum capacity of maxElts
LIST *createList(int (*compare)())
{
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->head = malloc(sizeof(NODE));
    assert(lp->head != NULL);
    lp->compare = compare;
    lp->count = 0;

    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
}

// destroyList
// ---------------------------------------------------------------------------------------
// Destroys and frees mememory for all elts in list
void destroyList(LIST *lp)
{
    assert(lp != NULL);
    NODE *dummy = lp->head->prev; // Start at last elt
    NODE *prevN = dummy->prev;
    int i;
    while (dummy != lp->head)
    { // Go until head (reverse order)
        dummy = prevN;
        prevN = dummy->prev;
        free(dummy);
    }
    free(lp);
}

// numItems
// ---------------------------------------------------------------------------------------
// Returns number of elts
int numItems(LIST *lp)
{
    assert(lp != NULL);
    return (lp->count);
}

// addFirst
// ---------------------------------------------------------------------------------------
// Adds an elt as the first elt in list
void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL);
    NODE *addN = malloc(sizeof(NODE));
    assert(addN != NULL);
    addN->data = item;

    lp->head->next->prev = addN;
    addN->next = lp->head->next; // 1 - Must be before 2 as haven't yet updated head->next
    lp->head->next = addN;       // 2
    addN->prev = lp->head;

    lp->count++;
}

// addLast
// ---------------------------------------------------------------------------------------
// Adds an elt as last elt in list
void addLast(LIST *lp, void *item)
{
    assert(lp != NULL);
    NODE *addN = malloc(sizeof(NODE));
    assert(addN != NULL);
    addN->data = item;

    // Update list prev & next
    lp->head->prev->next = addN;
    addN->prev = lp->head->prev;
    lp->head->prev = addN;

    // Update addN to know the prev & next
    addN->next = lp->head;

    lp->count++;
}

// *removeFirst
// ---------------------------------------------------------------------------------------
// Removes first elt in list
void *removeFirst(LIST *lp)
{
    assert(lp != NULL);

    NODE *dummy = lp->head->next;
    void *dataS = dummy->data;
    assert(dataS != NULL);
    lp->head->next = dummy->next;
    dummy->next->prev = lp->head;
    free(dummy);
    lp->count--;

    return (dataS);
}

// *removeLast
// ---------------------------------------------------------------------------------------
// Removes last elt in list
void *removeLast(LIST *lp)
{
    assert(lp != NULL);

    NODE *dummy = lp->head->prev;
    void *dataS = dummy->data;
    assert(dataS != NULL);
    dummy->prev->next = lp->head;
    lp->head->prev = dummy->prev;
    free(dummy);
    lp->count--;

    return (dataS);
}

// *getFirst
// ---------------------------------------------------------------------------------------
// Returns data of first elt in list
void *getFirst(LIST *lp)
{
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE *dummy = lp->head->next;
    assert(dummy != NULL);
    return (dummy->data);
}

// *getLast O()
// ---------------------------------------------------------------------------------------
// Returns data of last elt in list
void *getLast(LIST *lp)
{
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE *dummy = lp->head->prev;
    assert(dummy != NULL);
    return (dummy->data);
}

// removeItem
// ---------------------------------------------------------------------------------------
// Searches for an elt, then removes it if it exists.
void removeItem(LIST *lp, void *item)
{
    assert(lp != NULL);
    if (lp->count > 0)
    {
        NODE *dummy = lp->head->next; // Start at head
        while (dummy != lp->head)
        { // Go until hits head
            if ((*lp->compare)(dummy->data, item) == 0)
            {
                dummy->prev->next = dummy->next;
                dummy->next->prev = dummy->prev;
                free(dummy);
                lp->count--;
                break;
            }
            else
            {
                dummy = dummy->next;
            }
        }
    }
}

// *findItem
// ---------------------------------------------------------------------------------------
// Returns the elt's data if found in list.
void *findItem(LIST *lp, void *item)
{
    assert(lp != NULL);
    if (lp->count > 0)
    {
        NODE *dummy = lp->head->next; // Start at head
        while (dummy != lp->head)
        { // Go until hits head
            if ((*lp->compare)(dummy->data, item) == 0)
            {
                return (dummy->data);
            }
            else
            {
                dummy = dummy->next;
            }
        }
    }
    return (NULL);
}

// *getItems
// ---------------------------------------------------------------------------------------
// Returns an array of all elts in list.
void *getItems(LIST *lp)
{
    assert(lp != NULL);
    void **arr;
    NODE *dummy = lp->head->next;
    arr = malloc(sizeof(void *) * lp->count);
    assert(arr != NULL);
    int i = 0;
    while (i < lp->count && dummy != lp->head)
    {
        arr[i] = dummy->data;
        dummy = dummy->next;
        i++;
    }
    return arr;
}
