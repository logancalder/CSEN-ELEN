// Logan Calder, COEN12L R 9:15, 4/13/23
// >>> DESCRIPTION HERE <<< STILL NEED TO WRITE THIS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include <string.h>

// Variable declaration
// ---------------------------------------------------------------------------------------
SET *createSet(int maxElts);
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, char *elt);
void removeElement(SET *sp, char *elt);
char *findElement(SET *sp, char *elt);
char **getElements(SET *sp);
static int search(SET *sp, char *elt);

// Defining new type SET
// ---------------------------------------------------------------------------------------
typedef struct set
{
    char **data;
    int len;
    int count;
} SET;

// search
// ---------------------------------------------------------------------------------------
// Accepts a pointer to a set and pointer to char as parameters, will return index of char
// if found and -1 if not.
int search(SET *sp, char *elt)
{
    assert(sp != NULL);
    int i;
    for (i = 0; i < sp->count; i++)
    {
        if (sp->data[i] == elt)
        {
            return i;
        }
    }
    return -1;
}

// createSet
// ---------------------------------------------------------------------------------------
// Returns a pointer to a new set with a maximum capacity of maxElts
SET *createSet(int maxElts)
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->len = maxElts;
    sp->data = malloc(sizeof(char *) * maxElts);
    sp->count = 0;
    assert(sp->data != NULL);
    return sp;
}

// destroySet
// ---------------------------------------------------------------------------------------
// Deallocate memory associated with the set pointed to by sp
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for (int i; i < sp->count; i++)
    {
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}

// numElements
// ---------------------------------------------------------------------------------------
// Return the number of elements in the set pointed to by sp
int numElements(SET *sp)
{
    assert(sp != NULL);
    return (sp->count);
}

// addElement
// ---------------------------------------------------------------------------------------
// Add elt to the set pointed to by sp
void addElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    if (search(sp, elt) == -1)
    {
        sp->data[sp->count] = strdup(elt);
        sp->count++;
    }
}

// removeElement
// ---------------------------------------------------------------------------------------
// Remove elt from the set pointed to by sp
void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    int index;
    if ((index = search(sp, elt)) != -1)
    {
        free(sp->data[index]); // Note to self: can't free last instead because will point to nothing
        sp->data[index] = sp->data[sp->count - 1];
        sp->count--;
    }
}

// findElement
// ---------------------------------------------------------------------------------------
// If elt is present in the set pointed to by sp then return the matching element,
// otherwise return NULL
char *findElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    if (search(sp, elt) != -1)
    {
        return (elt);
    }
    return (NULL);
}

// getElements
// ---------------------------------------------------------------------------------------
// Allocate and return an array of elements in the set pointed to by sp
char **getElements(SET *sp)
{
    assert(sp != NULL);
    char **arr;
    arr = malloc(sizeof(char *) * (sp->count));
    int i;
    for (i = 0; i < sp->count; i++)
    {
        arr[i] = strdup(sp->data[i]);
    }
    return arr;
}
