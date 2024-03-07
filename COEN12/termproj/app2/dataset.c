// Logan Calder, COEN12L R 9:15, 6/11/2023
/* dataset.c :
    Implements public functions to be used when creating a hash table, including adding, removing, & searching
    for an element, obtaining the max age range, and deleting a set. Implements hash table as data structure as it is most
    efficient when searching for one unique element in an unsorted list.

    Data structure also implements tracking flags to know if an element has been deleted, not added, or is in the table.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dataset.h"
#include <stdbool.h>

SET *createSet(int maxElts);
void addElement(SET *sp, int age, int id);
int search(SET *sp, int age);
void removeID(SET *sp, int id);
int maxAgeGap(SET *sp);
void destroySet(SET *sp);

#define EMPTY 0
#define FILLED 1
#define DELETED 2

// createSet O(n)
// ---------------------------------------------------------------------------------------
// Returns a pointer to a new set with a maximum capacity of maxElts
SET *createSet(int maxElts)
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->len = maxElts;
    assert(sp->students != NULL);

    // Fill flags w/ EMPTY
    sp->flags = malloc(sizeof(char) * maxElts);
    int i;
    for (i = 0; i < maxElts; i++) // O(n)
    {
        sp->flags[i] = EMPTY;
    }

    return (sp);
}

// hash O(1)
// ---------------------------------------------------------------------------------------
// Returns the hash value for a key elt
int hash(int elt)
{
    return (elt % 3001);
}

// addElement O(n)
// ---------------------------------------------------------------------------------------
// Adds an elt into a deleted or empty slot in hash table
void addElement(SET *sp, int age, int id)
{
    assert(sp != NULL);

    int index;
    index = hash(id);
    while (true)
    {
        if (sp->flags[index] == FILLED)
        {
            index = hash(index + 1);
            continue;
        }
        else
        {
            sp->flags[index] = FILLED;

            sp->students[index].age = age;
            sp->students[index].id = id;
            sp->count++; // Increment count
            break;
        }
    }
}

// search O(n)
// ---------------------------------------------------------------------------------------
// Searches for a matching elt given by parameter id. If found, returns index.
// If the elt is not found, returns -1.
int search(SET *sp, int id)
{
    assert(sp != NULL);
    int index;
    int indexTemp;
    bool found = false;

    index = hash(id);

    for (index = 0; index < sp->len; index++)
    {
        index = hash(index);
        if (sp->flags[index] == FILLED)
        {
            if (sp->students[index].id == id)
            {
                printf("AGE: %i\nID: %i\nSUCCESSFULLY FOUND\n", sp->students[index].age, sp->students[index].id);
                return (index);
            }
        }
        if (sp->flags[index] == DELETED)
        {
            if (!found)
            {
                indexTemp = index;
                found = true;
            }
        }
        if (sp->flags[index] == EMPTY)
        {
            if (found)
            {
                return indexTemp;
            }
            return index;
        }
    }
    printf("ID: %i\nUNSUCCESSFULLY FOUND\n", id);
    return (-1);
}

// removeID O(n)
// ---------------------------------------------------------------------------------------
// Uses search to find if elt exists in hash table. If so, replaces id and age w/
// empty char, then sets flag to deleted. If unsuccessful, prints not found.
void removeID(SET *sp, int id)
{
    assert(sp != NULL);
    int index;
    index = search(sp, id);
    if (index != -1)
    {
        sp->flags[index] = DELETED;
        sp->students[index].id = '\0';
        sp->students[index].age = '\0';
        printf("SUCCESSFULLY DELETED STUDENT WITH ID %i\n", id);
    }
    else
    {
        printf("UNSUCCESSFULLY DELETED: NO STUDENT FOUND WITH ID %i\n", id);
    }
}

// destroySet O(1)
// ---------------------------------------------------------------------------------------
// Frees set and the set flags array.
void destroySet(SET *sp)
{
    assert(sp != NULL);
    free(sp->flags);
    free(sp);
}