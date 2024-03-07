// Logan Calder, COEN12L R 9:15, 4/13/23
// Script implements a generic set ADT that utilizes a hashing algorithim to store and
// find data. This prevents the ability to free individual data, but this is a task given
// to the client. Using the an internal search function, this script assigns keys, finds
// Strings, and updates the respected flags for each elt in the set.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "list.h"
#include <string.h>
#include <stdbool.h>

// Variable declaration
// ---------------------------------------------------------------------------------------
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()); // malloc for flag array & initialize flags on E
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, void *elt);
void removeElement(SET *sp, void *elt);
void *findElement(SET *sp, void *elt);
void *getElements(SET *sp);

// Defining new type SET
// ---------------------------------------------------------------------------------------
typedef struct set
{
    LIST **data;
    int len;
    int count;
    int (*compare)();
    unsigned (*hash)();
} SET;

// createSet O(n)
// ---------------------------------------------------------------------------------------
// Returns a pointer to a new set with a maximum capacity of maxElts
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->len = maxElts;
    sp->data = malloc(sizeof(char *) * maxElts);
    sp->compare = compare;
    sp->hash = hash;
    int i;
    for (i = 0; i < sp->len; i++) // O(n)
    {
        sp->data[i] = createList(sp->compare);
    }
    sp->count = 0;
    assert(sp->data != NULL);
    return sp;
}

// destroySet O(1)
// ---------------------------------------------------------------------------------------
// Deallocate memory associated with the set pointed to by sp
// Can no longer free individual data as we do not know type
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for (i = 0; i < sp->len; i++)
    {
        destroyList(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}

// numElements O(1)
// ---------------------------------------------------------------------------------------
// Return the number of elements in the set pointed to by sp
int numElements(SET *sp)
{
    assert(sp != NULL);
    return (sp->count);
}

// addElement O(n)
// ---------------------------------------------------------------------------------------
// Add elt to the set pointed to by sp
void addElement(SET *sp, void *elt)
{
    bool found = false;
    assert(sp != NULL && elt != NULL);
    int i = (sp->hash)(elt) % sp->len;
    if (findItem(sp->data[i], elt) == NULL)
    {
        addLast(sp->data[i], elt);
        sp->count++;
    }
}

// removeElement O(n)
// ---------------------------------------------------------------------------------------
// Remove elt from the set pointed to by sp, no longer frees memory as we do not know type
void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    int i = (sp->hash)(elt) % sp->len;
    if (findItem(sp->data[i], elt) != NULL)
    {
        removeItem(sp->data[i], elt);
        sp->count--;
    }
}

// findElement O(n)
// ---------------------------------------------------------------------------------------
// If elt is present in the set pointed to by sp then return the matching element,
// otherwise return NULL
void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL);
    int i = (sp->hash)(elt) % sp->len;
    return (findItem(sp->data[i], elt));
}

// getElements O(n)
// ---------------------------------------------------------------------------------------
// Allocate and return an array of elements in the set pointed to by sp
void *getElements(SET *sp)
{
    assert(sp != NULL);
    void **arr;
    void **dummy;
    int num = 0;
    arr = malloc(sizeof(char *) * (sp->count));
    int i, j;
    assert(arr != NULL);
    for (i = 0, j = 0; i < sp->len; i++, j++)
    {
        dummy = getItems(sp->data[i]);
        memcpy(arr + j, dummy, numItems(sp->data[i]) * sizeof(void *));
    }
    return arr;
}