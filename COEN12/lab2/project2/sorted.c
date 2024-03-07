// Logan Calder, COEN12L R 9:15, 4/13/23
// >>> DESCRIPTION HERE <<< STILL NEED TO WRITE THIS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include <string.h>
#include <stdbool.h>

// DONE
// Variable declaration
// ---------------------------------------------------------------------------------------
SET *createSet(int maxElts);
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, char *elt);
void removeElement(SET *sp, char *elt);
char *findElement(SET *sp, char *elt);
char **getElements(SET *sp);
static int search(SET *sp, char *elt, bool *found);

// DONE
// Defining new type SET
// ---------------------------------------------------------------------------------------
typedef struct set
{
    char **data;
    int len;
    int count;
} SET;

// DONE
// search
// ---------------------------------------------------------------------------------------
// Accepts a pointer to a set and pointer to char as parameters, will return index of char
// if found and -1 if not.
static int search(SET *sp, char *elt, bool *found)
{
    assert(sp != NULL);
    int i;
    int low = 0;
    int high = (sp->count) - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (strcmp(sp->data[mid], elt) < 0)
        {
            low = mid + 1;
        }
        else if (strcmp(sp->data[mid], elt) > 0)
        {
            high = mid - 1;
        }
        else
        {
            *found = true;
            return (mid);
        }
    }
    *found = false;
    return low;
}

// DONE
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

// DONE
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

// DONE
// numElements
// ---------------------------------------------------------------------------------------
// Return the number of elements in the set pointed to by sp
int numElements(SET *sp)
{
    assert(sp != NULL);
    return (sp->count);
}

// DONE
// addElement
// ---------------------------------------------------------------------------------------
// Add elt to the set pointed to by sp
void addElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = false;
    int searchIndex = search(sp, elt, &found);
    int i;
    if (found == false)
    {
        for (int i = sp->count; i >= searchIndex; i--)
        {
            sp->data[i] = sp->data[i - 1];
        }
        sp->data[searchIndex] = strdup(elt);
        sp->count++;
    }
}

// DONE
// removeElement
// ---------------------------------------------------------------------------------------
// Remove elt from the set pointed to by sp
void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    int i;
    bool found = false;
    int searchIndex = search(sp, elt, &found);
    if (found == true)
    {
        free(sp->data[searchIndex]); // Note to self: can't free last instead because will point to nothing
        for (i = searchIndex; i < (sp->count); i++)
        {
            sp->data[i] = sp->data[i + 1];
        }
        sp->count--;
    }
}

// NEEDS FINISHED
// findElement
// ---------------------------------------------------------------------------------------
// If elt is present in the set pointed to by sp then return the matching element,
// otherwise return NULL
char *findElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = false;
    int searchIndex = search(sp, elt, &found);
    if (found == true)
    {
        return (elt);
    }
    return (NULL);
}

// DONE?
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
