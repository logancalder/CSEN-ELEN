// Logan Calder, COEN12L R 9:15, 5/4/23
// Script implements a set ADT for Strings that utilizes a hashing algorithim to store and
// find data. This script has the ability to allocate and free memory for each elt added
// to the set. Using the provided strhash(char *s) function, this script assigns keys, finds
// Strings, and updates the respected flags for each elt in the set.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include <string.h>
#include <stdbool.h>

// Variable declaration
// ---------------------------------------------------------------------------------------
SET *createSet(int maxElts); // malloc for flag array & initialize flags on E
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, char *elt);
void removeElement(SET *sp, char *elt);
char *findElement(SET *sp, char *elt);
char **getElements(SET *sp);
static int search(SET *sp, char *elt, bool *found);

#define EMPTY 0
#define FILLED 1
#define DELETED 2

// Defining new type SET
// ---------------------------------------------------------------------------------------
typedef struct set
{
    char **data;
    int len;
    int count;
    char *flags; // E : 0, F : 1, D : 2
} SET;

// Hash function provided O(1)
// ---------------------------------------------------------------------------------------
unsigned strhash(char *s)
{
    unsigned hash = 0;
    while (*s != '\0')
    {
        hash = 31 * hash + *s++;
    }
    return hash;
}

// search O(n)
// ---------------------------------------------------------------------------------------
// Accepts a pointer to a set and pointer to char as parameters, will return index of char
// if found and -1 if not. Updates boolean found to be true/false if found.
int search(SET *sp, char *elt, bool *found)
{
    assert(sp != NULL && elt != NULL);
    int loctemp, i, loc;
    bool fd = false; // Found deletion
    unsigned hash = strhash(elt);
    for (i = 0; i < sp->len; i++)
    {
        loc = (i + hash) % (sp->len);
        if (sp->flags[loc] == FILLED)
        {
            if (strcmp(sp->data[loc], elt) == 0)
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
SET *createSet(int maxElts)
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->len = maxElts;
    sp->data = malloc(sizeof(char *) * maxElts);
    sp->flags = malloc(sizeof(char) * maxElts);
    int i;
    for (i = 0; i < maxElts; i++)
    {
        sp->flags[i] = EMPTY;
    }
    sp->count = 0;
    assert(sp->data != NULL);
    return sp;
}

// destroySet O(n)
// ---------------------------------------------------------------------------------------
// Deallocate memory associated with the set pointed to by sp
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for (i; i < sp->count; i++)
    {
        if (sp->flags[i] == FILLED)
        {
            free(sp->data[i]);
        }
    }
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
void addElement(SET *sp, char *elt)
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
// Remove elt from the set pointed to by sp
void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);
    if (found == true)
    {
        assert(sp->data[index] != NULL);
        sp->flags[index] = DELETED;
        free(sp->data[index]);
        sp->count--;
    }
}

// findElement O(n)
// ---------------------------------------------------------------------------------------
// If elt is present in the set pointed to by sp then return the matching element,
// otherwise return NULL
char *findElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);
    if (found == true)
    {
        return (sp->data[index]);
    }
    return (NULL);
}

// getElements O(n)
// ---------------------------------------------------------------------------------------
// Allocate and return an array of elements in the set pointed to by sp
char **getElements(SET *sp)
{
    assert(sp != NULL);
    char **arr;
    arr = malloc(sizeof(char *) * (sp->count));
    int i;
    int j = 0;
    for (i = 0; i < sp->len; i++)
    {
        if (sp->flags[i] == FILLED)
        {
            arr[j] = strdup(sp->data[i]);
            j++;
        }
    }
    return arr;
}
