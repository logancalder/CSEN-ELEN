// Logan Calder, COEN12L R 9:15, 4/13/23
// Script implements a generic set ADT that utilizes a hashing algorithim to store and
// find data. This prevents the ability to free individual data, but this is a task given
// to the client. Using the an internal search function, this script assigns keys, finds
// Strings, and updates the respected flags for each elt in the set.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
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
static int search(SET *sp, void *elt, bool *found);

#define EMPTY 0
#define FILLED 1
#define DELETED 2

// Defining new type SET
// ---------------------------------------------------------------------------------------
typedef struct set
{
    void **data;
    int len;
    int count;
    char *flags; // E : 0, F : 1, D : 2
    int (*compare)();
    unsigned (*hash)();
} SET;

// search O(n)
// ---------------------------------------------------------------------------------------
// Accepts a pointer to a set and pointer to char as parameters, will return index of char
// if found and -1 if not. Updates boolean found to be true/false if found.
int search(SET *sp, void *elt, bool *found)
{
    assert(sp != NULL && elt != NULL);
    int loctemp, i, loc;
    bool fd = false; // Found deletion
    unsigned hash = (*sp->hash)(elt);
    for (i = 0; i < sp->len; i++)
    {
        loc = (i + hash) % (sp->len);
        if (sp->flags[loc] == FILLED)
        {
            if ((*sp->compare)(sp->data[loc], elt) == 0)
            {
                *found = true;
                return (loc);
            }
        }

        if (sp->flags[loc] == DELETED)
        {
            if (!fd)
            {
                fd = true;
                loctemp = loc;
            }
        }

        if (sp->flags[loc] == EMPTY)
        {
            if (fd)
            {
                return (loctemp);
            }
            return (loc);
        }
    }
    return -1;
}

// createSet O(n)
// ---------------------------------------------------------------------------------------
// Returns a pointer to a new set with a maximum capacity of maxElts
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->len = maxElts;
    sp->data = malloc(sizeof(char *) * maxElts);
    sp->flags = malloc(sizeof(char) * maxElts);
    sp->compare = compare;
    sp->hash = hash;
    int i;
    for (i = 0; i < maxElts; i++) // O(n)
    {
        sp->flags[i] = EMPTY;
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
    free(sp->data);
    free(sp->flags);
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
    int locn = search(sp, elt, &found);
    if (!found)
    {
        assert(sp->count < sp->len);
        sp->data[locn] = strdup(elt);
        assert(sp->data[locn] != NULL);
        sp->flags[locn] = FILLED;
        sp->count++;
    }
}

// removeElement O(n)
// ---------------------------------------------------------------------------------------
// Remove elt from the set pointed to by sp, no longer frees memory as we do not know type
void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);
    if (found == true)
    {
        assert(sp->data[index] != NULL);
        sp->flags[index] = DELETED;
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
    assert(elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found); // O(n)
    if (found == true)
    {
        return (sp->data[index]);
    }
    return (NULL);
}

// getElements O(n)
// ---------------------------------------------------------------------------------------
// Allocate and return an array of elements in the set pointed to by sp
void *getElements(SET *sp)
{
    assert(sp != NULL);
    void **arr;
    arr = malloc(sizeof(char *) * (sp->count));
    int i, j;
    for (i = 0; i < sp->len; i++)
    {
        if (sp->flags[i] == FILLED)
        {
            arr[j] = strdup(sp->data[i]);
        }
    }
    return arr;
}
